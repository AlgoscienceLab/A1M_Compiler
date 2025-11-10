#ifndef A1M_CPU_H
#define A1M_CPU_H

#include <stdint.h>
#include <stdbool.h>

// Memory size (16MB for emulator)
#define MEMORY_SIZE (16 * 1024 * 1024)

// Reset vector
#define RESET_VECTOR 0x0000000000001000ULL

// Register count
#define NUM_REGISTERS 32

// Instruction opcodes
typedef enum {
    OP_NOP    = 0x00,
    OP_HALT   = 0x01,
    OP_ADD    = 0x02,
    OP_ADDI   = 0x03,
    OP_SUB    = 0x04,
    OP_SUBI   = 0x05,
    OP_MUL    = 0x06,
    OP_MULI   = 0x07,
    OP_DIV    = 0x08,
    OP_DIVI   = 0x09,
    OP_MOD    = 0x0A,
    OP_MODI   = 0x0B,
    OP_AND    = 0x0C,
    OP_ANDI   = 0x0D,
    OP_OR     = 0x0E,
    OP_ORI    = 0x0F,
    OP_XOR    = 0x10,
    OP_XORI   = 0x11,
    OP_NOT    = 0x12,
    OP_SHL    = 0x13,
    OP_SHLI   = 0x14,
    OP_SHR    = 0x15,
    OP_SHRI   = 0x16,
    OP_SAR    = 0x17,
    OP_SARI   = 0x18,
    OP_CMP    = 0x19,
    OP_CMPI   = 0x1A,
    OP_TEST   = 0x1B,
    OP_LOAD   = 0x20,
    OP_STORE  = 0x21,
    OP_LOADB  = 0x22,
    OP_STOREB = 0x23,
    OP_LOADH  = 0x24,
    OP_STOREH = 0x25,
    OP_LOADW  = 0x26,
    OP_STOREW = 0x27,
    OP_PUSH   = 0x28,
    OP_POP    = 0x29,
    OP_JMP    = 0x30,
    OP_JZ     = 0x31,
    OP_JNZ    = 0x32,
    OP_JC     = 0x33,
    OP_JNC    = 0x34,
    OP_JO     = 0x35,
    OP_JNO    = 0x36,
    OP_JN     = 0x37,
    OP_JNN    = 0x38,
    OP_CALL   = 0x39,
    OP_RET    = 0x3A,
    OP_JR     = 0x3B,
    OP_MOV    = 0x40,
    OP_MOVI   = 0x41,
    OP_LUI    = 0x42,
    OP_SYSCALL = 0x50
} Opcode;

// Flag bits
#define FLAG_ZERO     (1ULL << 0)
#define FLAG_CARRY    (1ULL << 1)
#define FLAG_OVERFLOW (1ULL << 2)
#define FLAG_NEGATIVE (1ULL << 3)

// Instruction structure
typedef struct {
    uint8_t opcode;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    int16_t immediate;
    int32_t jump_addr;
} Instruction;

// CPU state
typedef struct {
    uint64_t registers[NUM_REGISTERS];  // General purpose registers
    uint64_t pc;                        // Program counter
    uint64_t sp;                        // Stack pointer
    uint64_t flags;                     // Status flags
    uint8_t *memory;                    // Memory
    bool halted;                        // Halt flag
    uint64_t instruction_count;         // Instruction counter
    bool debug_mode;                    // Debug mode flag
} CPU;

// Function prototypes
CPU* cpu_create(void);
void cpu_destroy(CPU *cpu);
void cpu_reset(CPU *cpu);
int cpu_load_program(CPU *cpu, const char *filename);
void cpu_step(CPU *cpu);
void cpu_run(CPU *cpu);
void cpu_dump_registers(CPU *cpu);
void cpu_dump_memory(CPU *cpu, uint64_t start, uint64_t length);
Instruction cpu_decode(uint32_t instruction);
void cpu_execute(CPU *cpu, Instruction inst);

// Helper functions
uint64_t cpu_read_memory_64(CPU *cpu, uint64_t addr);
uint32_t cpu_read_memory_32(CPU *cpu, uint64_t addr);
uint16_t cpu_read_memory_16(CPU *cpu, uint64_t addr);
uint8_t cpu_read_memory_8(CPU *cpu, uint64_t addr);
void cpu_write_memory_64(CPU *cpu, uint64_t addr, uint64_t value);
void cpu_write_memory_32(CPU *cpu, uint64_t addr, uint32_t value);
void cpu_write_memory_16(CPU *cpu, uint64_t addr, uint16_t value);
void cpu_write_memory_8(CPU *cpu, uint64_t addr, uint8_t value);

// Sign extension
int64_t sign_extend_14(int16_t value);
int64_t sign_extend_24(int32_t value);

#endif // A1M_CPU_H
