#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "a1m_cpu.h"

// Create a new CPU instance
CPU* cpu_create(void) {
    CPU *cpu = (CPU*)malloc(sizeof(CPU));
    if (!cpu) {
        fprintf(stderr, "Error: Failed to allocate CPU\n");
        return NULL;
    }
    
    cpu->memory = (uint8_t*)calloc(MEMORY_SIZE, sizeof(uint8_t));
    if (!cpu->memory) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        free(cpu);
        return NULL;
    }
    
    cpu_reset(cpu);
    return cpu;
}

// Destroy CPU instance
void cpu_destroy(CPU *cpu) {
    if (cpu) {
        if (cpu->memory) {
            free(cpu->memory);
        }
        free(cpu);
    }
}

// Reset CPU to initial state
void cpu_reset(CPU *cpu) {
    memset(cpu->registers, 0, sizeof(cpu->registers));
    cpu->pc = RESET_VECTOR;
    cpu->sp = 0x7FFFFFFFFFFFFFF0ULL;  // Stack starts at top
    cpu->flags = 0;
    cpu->halted = false;
    cpu->instruction_count = 0;
    cpu->debug_mode = false;
}

// Sign extension helpers
int64_t sign_extend_14(int16_t value) {
    if (value & 0x2000) {  // Check sign bit
        return value | 0xFFFFFFFFFFFFC000LL;
    }
    return value;
}

int64_t sign_extend_24(int32_t value) {
    if (value & 0x800000) {  // Check sign bit
        return value | 0xFFFFFFFFFF000000LL;
    }
    return value;
}

// Memory read functions (little-endian)
uint64_t cpu_read_memory_64(CPU *cpu, uint64_t addr) {
    if (addr >= MEMORY_SIZE - 7) {
        fprintf(stderr, "Error: Memory read out of bounds at 0x%016llx\n", 
                (unsigned long long)addr);
        return 0;
    }
    return (uint64_t)cpu->memory[addr] |
           ((uint64_t)cpu->memory[addr + 1] << 8) |
           ((uint64_t)cpu->memory[addr + 2] << 16) |
           ((uint64_t)cpu->memory[addr + 3] << 24) |
           ((uint64_t)cpu->memory[addr + 4] << 32) |
           ((uint64_t)cpu->memory[addr + 5] << 40) |
           ((uint64_t)cpu->memory[addr + 6] << 48) |
           ((uint64_t)cpu->memory[addr + 7] << 56);
}

uint32_t cpu_read_memory_32(CPU *cpu, uint64_t addr) {
    if (addr >= MEMORY_SIZE - 3) {
        fprintf(stderr, "Error: Memory read out of bounds at 0x%016llx\n", 
                (unsigned long long)addr);
        return 0;
    }
    return (uint32_t)cpu->memory[addr] |
           ((uint32_t)cpu->memory[addr + 1] << 8) |
           ((uint32_t)cpu->memory[addr + 2] << 16) |
           ((uint32_t)cpu->memory[addr + 3] << 24);
}

uint16_t cpu_read_memory_16(CPU *cpu, uint64_t addr) {
    if (addr >= MEMORY_SIZE - 1) {
        fprintf(stderr, "Error: Memory read out of bounds at 0x%016llx\n", 
                (unsigned long long)addr);
        return 0;
    }
    return (uint16_t)cpu->memory[addr] |
           ((uint16_t)cpu->memory[addr + 1] << 8);
}

uint8_t cpu_read_memory_8(CPU *cpu, uint64_t addr) {
    if (addr >= MEMORY_SIZE) {
        fprintf(stderr, "Error: Memory read out of bounds at 0x%016llx\n", 
                (unsigned long long)addr);
        return 0;
    }
    return cpu->memory[addr];
}

// Memory write functions (little-endian)
void cpu_write_memory_64(CPU *cpu, uint64_t addr, uint64_t value) {
    if (addr >= MEMORY_SIZE - 7) {
        fprintf(stderr, "Error: Memory write out of bounds at 0x%016llx\n", 
                (unsigned long long)addr);
        return;
    }
    cpu->memory[addr] = value & 0xFF;
    cpu->memory[addr + 1] = (value >> 8) & 0xFF;
    cpu->memory[addr + 2] = (value >> 16) & 0xFF;
    cpu->memory[addr + 3] = (value >> 24) & 0xFF;
    cpu->memory[addr + 4] = (value >> 32) & 0xFF;
    cpu->memory[addr + 5] = (value >> 40) & 0xFF;
    cpu->memory[addr + 6] = (value >> 48) & 0xFF;
    cpu->memory[addr + 7] = (value >> 56) & 0xFF;
}

void cpu_write_memory_32(CPU *cpu, uint64_t addr, uint32_t value) {
    if (addr >= MEMORY_SIZE - 3) {
        fprintf(stderr, "Error: Memory write out of bounds at 0x%016llx\n", 
                (unsigned long long)addr);
        return;
    }
    cpu->memory[addr] = value & 0xFF;
    cpu->memory[addr + 1] = (value >> 8) & 0xFF;
    cpu->memory[addr + 2] = (value >> 16) & 0xFF;
    cpu->memory[addr + 3] = (value >> 24) & 0xFF;
}

void cpu_write_memory_16(CPU *cpu, uint64_t addr, uint16_t value) {
    if (addr >= MEMORY_SIZE - 1) {
        fprintf(stderr, "Error: Memory write out of bounds at 0x%016llx\n", 
                (unsigned long long)addr);
        return;
    }
    cpu->memory[addr] = value & 0xFF;
    cpu->memory[addr + 1] = (value >> 8) & 0xFF;
}

void cpu_write_memory_8(CPU *cpu, uint64_t addr, uint8_t value) {
    if (addr >= MEMORY_SIZE) {
        fprintf(stderr, "Error: Memory write out of bounds at 0x%016llx\n", 
                (unsigned long long)addr);
        return;
    }
    cpu->memory[addr] = value;
}

// Decode instruction
Instruction cpu_decode(uint32_t instruction) {
    Instruction inst;
    inst.opcode = (instruction >> 24) & 0xFF;
    inst.rd = (instruction >> 19) & 0x1F;
    inst.rs1 = (instruction >> 14) & 0x1F;
    inst.rs2 = (instruction >> 9) & 0x1F;
    inst.immediate = instruction & 0x3FFF;  // 14-bit immediate
    inst.jump_addr = instruction & 0xFFFFFF; // 24-bit jump address
    return inst;
}

// Load program from binary file
int cpu_load_program(CPU *cpu, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return -1;
    }
    
    // Read file into memory starting at reset vector
    size_t bytes_read = fread(cpu->memory + RESET_VECTOR, 1, 
                             MEMORY_SIZE - RESET_VECTOR, file);
    fclose(file);
    
    if (cpu->debug_mode) {
        printf("Loaded %zu bytes into memory at 0x%016llx\n", 
               bytes_read, (unsigned long long)RESET_VECTOR);
    }
    return 0;
}

// Update flags based on result
void cpu_update_flags(CPU *cpu, uint64_t result, bool carry, bool overflow) {
    cpu->flags = 0;
    if (result == 0) {
        cpu->flags |= FLAG_ZERO;
    }
    if (result & (1ULL << 63)) {
        cpu->flags |= FLAG_NEGATIVE;
    }
    if (carry) {
        cpu->flags |= FLAG_CARRY;
    }
    if (overflow) {
        cpu->flags |= FLAG_OVERFLOW;
    }
}

// Execute instruction
void cpu_execute(CPU *cpu, Instruction inst) {
    uint64_t result;
    int64_t signed_a, signed_b;
    bool carry = false, overflow = false;
    
    // R0 is always zero
    cpu->registers[0] = 0;
    
    switch (inst.opcode) {
        case OP_NOP:
            break;
            
        case OP_HALT:
            cpu->halted = true;
            break;
            
        case OP_ADD:
            result = cpu->registers[inst.rs1] + cpu->registers[inst.rs2];
            carry = (result < cpu->registers[inst.rs1]);
            overflow = ((cpu->registers[inst.rs1] & (1ULL << 63)) == 
                       (cpu->registers[inst.rs2] & (1ULL << 63))) &&
                      ((result & (1ULL << 63)) != 
                       (cpu->registers[inst.rs1] & (1ULL << 63)));
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, carry, overflow);
            break;
            
        case OP_ADDI:
            result = cpu->registers[inst.rs1] + sign_extend_14(inst.immediate);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_SUB:
            result = cpu->registers[inst.rs1] - cpu->registers[inst.rs2];
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_SUBI:
            result = cpu->registers[inst.rs1] - sign_extend_14(inst.immediate);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_MUL:
            result = cpu->registers[inst.rs1] * cpu->registers[inst.rs2];
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_MULI:
            result = cpu->registers[inst.rs1] * sign_extend_14(inst.immediate);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_DIV:
            if (cpu->registers[inst.rs2] != 0) {
                signed_a = (int64_t)cpu->registers[inst.rs1];
                signed_b = (int64_t)cpu->registers[inst.rs2];
                result = signed_a / signed_b;
                cpu->registers[inst.rd] = result;
            } else {
                fprintf(stderr, "Error: Division by zero at PC=0x%016llx\n", 
                       (unsigned long long)cpu->pc);
                cpu->registers[inst.rd] = 0;
            }
            break;
            
        case OP_DIVI:
            if (inst.immediate != 0) {
                signed_a = (int64_t)cpu->registers[inst.rs1];
                signed_b = sign_extend_14(inst.immediate);
                result = signed_a / signed_b;
                cpu->registers[inst.rd] = result;
            } else {
                fprintf(stderr, "Error: Division by zero at PC=0x%016llx\n", 
                       (unsigned long long)cpu->pc);
                cpu->registers[inst.rd] = 0;
            }
            break;
            
        case OP_MOD:
            if (cpu->registers[inst.rs2] != 0) {
                signed_a = (int64_t)cpu->registers[inst.rs1];
                signed_b = (int64_t)cpu->registers[inst.rs2];
                result = signed_a % signed_b;
                cpu->registers[inst.rd] = result;
            } else {
                cpu->registers[inst.rd] = 0;
            }
            break;
            
        case OP_AND:
            result = cpu->registers[inst.rs1] & cpu->registers[inst.rs2];
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_ANDI:
            result = cpu->registers[inst.rs1] & sign_extend_14(inst.immediate);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_OR:
            result = cpu->registers[inst.rs1] | cpu->registers[inst.rs2];
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_ORI:
            result = cpu->registers[inst.rs1] | sign_extend_14(inst.immediate);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_XOR:
            result = cpu->registers[inst.rs1] ^ cpu->registers[inst.rs2];
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_XORI:
            result = cpu->registers[inst.rs1] ^ sign_extend_14(inst.immediate);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_NOT:
            result = ~cpu->registers[inst.rs1];
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_SHL:
            result = cpu->registers[inst.rs1] << (cpu->registers[inst.rs2] & 0x3F);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_SHLI:
            result = cpu->registers[inst.rs1] << (inst.immediate & 0x3F);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_SHR:
            result = cpu->registers[inst.rs1] >> (cpu->registers[inst.rs2] & 0x3F);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_SHRI:
            result = cpu->registers[inst.rs1] >> (inst.immediate & 0x3F);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_SAR:
            signed_a = (int64_t)cpu->registers[inst.rs1];
            result = signed_a >> (cpu->registers[inst.rs2] & 0x3F);
            cpu->registers[inst.rd] = result;
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_CMP:
            result = cpu->registers[inst.rs1] - cpu->registers[inst.rs2];
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_CMPI:
            result = cpu->registers[inst.rs1] - sign_extend_14(inst.immediate);
            cpu_update_flags(cpu, result, false, false);
            break;
            
        case OP_LOAD:
            result = cpu_read_memory_64(cpu, cpu->registers[inst.rs1] + 
                                       sign_extend_14(inst.immediate));
            cpu->registers[inst.rd] = result;
            break;
            
        case OP_STORE:
            cpu_write_memory_64(cpu, cpu->registers[inst.rs1] + 
                               sign_extend_14(inst.immediate),
                               cpu->registers[inst.rd]);
            break;
            
        case OP_LOADB:
            result = cpu_read_memory_8(cpu, cpu->registers[inst.rs1] + 
                                      sign_extend_14(inst.immediate));
            cpu->registers[inst.rd] = result;
            break;
            
        case OP_STOREB:
            cpu_write_memory_8(cpu, cpu->registers[inst.rs1] + 
                              sign_extend_14(inst.immediate),
                              cpu->registers[inst.rd] & 0xFF);
            break;
            
        case OP_PUSH:
            cpu->sp -= 8;
            cpu_write_memory_64(cpu, cpu->sp, cpu->registers[inst.rs1]);
            break;
            
        case OP_POP:
            cpu->registers[inst.rd] = cpu_read_memory_64(cpu, cpu->sp);
            cpu->sp += 8;
            break;
            
        case OP_JMP:
            cpu->pc += (sign_extend_24(inst.jump_addr) << 2);
            return;  // Don't increment PC
            
        case OP_JZ:
            if (cpu->flags & FLAG_ZERO) {
                cpu->pc += (sign_extend_24(inst.jump_addr) << 2);
                return;
            }
            break;
            
        case OP_JNZ:
            if (!(cpu->flags & FLAG_ZERO)) {
                cpu->pc += (sign_extend_24(inst.jump_addr) << 2);
                return;
            }
            break;
            
        case OP_JC:
            if (cpu->flags & FLAG_CARRY) {
                cpu->pc += (sign_extend_24(inst.jump_addr) << 2);
                return;
            }
            break;
            
        case OP_JN:
            if (cpu->flags & FLAG_NEGATIVE) {
                cpu->pc += (sign_extend_24(inst.jump_addr) << 2);
                return;
            }
            break;
            
        case OP_CALL:
            cpu->registers[31] = cpu->pc + 4;
            cpu->pc += (sign_extend_24(inst.jump_addr) << 2);
            return;
            
        case OP_RET:
            cpu->pc = cpu->registers[31];
            return;
            
        case OP_JR:
            cpu->pc = cpu->registers[inst.rs1];
            return;
            
        case OP_MOV:
            cpu->registers[inst.rd] = cpu->registers[inst.rs1];
            break;
            
        case OP_MOVI:
            cpu->registers[inst.rd] = sign_extend_14(inst.immediate);
            break;
            
        case OP_LUI:
            cpu->registers[inst.rd] = (uint64_t)inst.immediate << 50;
            break;
            
        case OP_SYSCALL:
            // System call implementation
            switch (inst.immediate & 0xFF) {
                case 0x00:  // exit
                    cpu->halted = true;
                    break;
                case 0x01:  // print_int
                    printf("%lld", (long long)cpu->registers[1]);
                    fflush(stdout);
                    break;
                case 0x02:  // print_char
                    printf("%c", (char)cpu->registers[1]);
                    fflush(stdout);
                    break;
                case 0x03:  // read_int
                    if (scanf("%lld", (long long*)&cpu->registers[1]) != 1) {
                        cpu->registers[1] = 0;  // Default to 0 on error
                    }
                    break;
                case 0x04:  // print_string
                    {
                        uint64_t str_addr = cpu->registers[1];
                        if (str_addr < MEMORY_SIZE) {
                            // Read string from memory until null terminator
                            while (str_addr < MEMORY_SIZE) {
                                char c = cpu->memory[str_addr];
                                if (c == '\0') break;
                                printf("%c", c);
                                str_addr++;
                            }
                            fflush(stdout);
                        }
                    }
                    break;
                default:
                    fprintf(stderr, "Unknown syscall: 0x%x\n", inst.immediate);
                    break;
            }
            break;
            
        default:
            fprintf(stderr, "Unknown opcode: 0x%02x at PC=0x%016llx\n", 
                   inst.opcode, (unsigned long long)cpu->pc);
            break;
    }
    
    cpu->pc += 4;  // Move to next instruction
}

// Execute one instruction
void cpu_step(CPU *cpu) {
    if (cpu->halted) {
        return;
    }
    
    uint32_t instruction = cpu_read_memory_32(cpu, cpu->pc);
    Instruction inst = cpu_decode(instruction);
    
    if (cpu->debug_mode) {
        printf("PC=0x%016llx  Inst=0x%08x  OP=0x%02x\n", 
               (unsigned long long)cpu->pc, instruction, inst.opcode);
    }
    
    cpu_execute(cpu, inst);
    cpu->instruction_count++;
}

// Run CPU until halt
void cpu_run(CPU *cpu) {
    while (!cpu->halted) {
        cpu_step(cpu);
        
        // Safety limit
        if (cpu->instruction_count > 1000000) {
            fprintf(stderr, "Warning: Execution limit reached\n");
            break;
        }
    }
    
    if (cpu->debug_mode) {
        printf("\nExecution complete. Instructions executed: %llu\n", 
               (unsigned long long)cpu->instruction_count);
    }
}

// Dump register contents
void cpu_dump_registers(CPU *cpu) {
    printf("\n=== Register Dump ===\n");
    for (int i = 0; i < NUM_REGISTERS; i += 4) {
        printf("R%-2d: 0x%016llx  R%-2d: 0x%016llx  R%-2d: 0x%016llx  R%-2d: 0x%016llx\n",
               i, (unsigned long long)cpu->registers[i],
               i+1, (unsigned long long)cpu->registers[i+1],
               i+2, (unsigned long long)cpu->registers[i+2],
               i+3, (unsigned long long)cpu->registers[i+3]);
    }
    printf("PC:  0x%016llx\n", (unsigned long long)cpu->pc);
    printf("SP:  0x%016llx\n", (unsigned long long)cpu->sp);
    printf("FLAGS: 0x%016llx [", (unsigned long long)cpu->flags);
    if (cpu->flags & FLAG_ZERO) printf("Z ");
    if (cpu->flags & FLAG_CARRY) printf("C ");
    if (cpu->flags & FLAG_OVERFLOW) printf("O ");
    if (cpu->flags & FLAG_NEGATIVE) printf("N ");
    printf("]\n");
}

// Dump memory contents
void cpu_dump_memory(CPU *cpu, uint64_t start, uint64_t length) {
    printf("\n=== Memory Dump (0x%016llx - 0x%016llx) ===\n", 
           (unsigned long long)start, (unsigned long long)(start + length));
    
    for (uint64_t i = 0; i < length; i += 16) {
        printf("0x%016llx: ", (unsigned long long)(start + i));
        for (int j = 0; j < 16 && (i + j) < length; j++) {
            printf("%02x ", cpu->memory[start + i + j]);
        }
        printf("\n");
    }
}
