#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE 1024
#define MAX_LABELS 1000
#define MAX_INSTRUCTIONS 10000

typedef struct {
    char name[64];
    uint64_t address;
} Label;

typedef struct {
    char mnemonic[16];
    uint8_t opcode;
    char type; // 'R', 'I', 'J', 'M'
} OpcodeDef;

typedef struct {
    uint32_t instruction;
    uint64_t address;
    int line_number;
} Instruction;

// Label table
Label labels[MAX_LABELS];
int label_count = 0;

// Instruction buffer
Instruction instructions[MAX_INSTRUCTIONS];
int instruction_count = 0;

// Current address counter
uint64_t current_address = 0x0000000000001000;

// Opcode definitions
OpcodeDef opcodes[] = {
    {"NOP", 0x00, 'R'},
    {"HALT", 0x01, 'R'},
    {"ADD", 0x02, 'R'},
    {"ADDI", 0x03, 'I'},
    {"SUB", 0x04, 'R'},
    {"SUBI", 0x05, 'I'},
    {"MUL", 0x06, 'R'},
    {"MULI", 0x07, 'I'},
    {"DIV", 0x08, 'R'},
    {"DIVI", 0x09, 'I'},
    {"MOD", 0x0A, 'R'},
    {"MODI", 0x0B, 'I'},
    {"AND", 0x0C, 'R'},
    {"ANDI", 0x0D, 'I'},
    {"OR", 0x0E, 'R'},
    {"ORI", 0x0F, 'I'},
    {"XOR", 0x10, 'R'},
    {"XORI", 0x11, 'I'},
    {"NOT", 0x12, 'R'},
    {"SHL", 0x13, 'R'},
    {"SHLI", 0x14, 'I'},
    {"SHR", 0x15, 'R'},
    {"SHRI", 0x16, 'I'},
    {"SAR", 0x17, 'R'},
    {"SARI", 0x18, 'I'},
    {"CMP", 0x19, 'R'},
    {"CMPI", 0x1A, 'I'},
    {"TEST", 0x1B, 'R'},
    {"LOAD", 0x20, 'M'},
    {"STORE", 0x21, 'M'},
    {"LOADB", 0x22, 'M'},
    {"STOREB", 0x23, 'M'},
    {"LOADH", 0x24, 'M'},
    {"STOREH", 0x25, 'M'},
    {"LOADW", 0x26, 'M'},
    {"STOREW", 0x27, 'M'},
    {"PUSH", 0x28, 'M'},
    {"POP", 0x29, 'M'},
    {"JMP", 0x30, 'J'},
    {"JZ", 0x31, 'J'},
    {"JNZ", 0x32, 'J'},
    {"JC", 0x33, 'J'},
    {"JNC", 0x34, 'J'},
    {"JO", 0x35, 'J'},
    {"JNO", 0x36, 'J'},
    {"JN", 0x37, 'J'},
    {"JNN", 0x38, 'J'},
    {"CALL", 0x39, 'J'},
    {"RET", 0x3A, 'R'},
    {"JR", 0x3B, 'R'},
    {"MOV", 0x40, 'R'},
    {"MOVI", 0x41, 'I'},
    {"LUI", 0x42, 'I'},
    {"SYSCALL", 0x50, 'I'},
    {"", 0, 0}  // Sentinel
};

// Parse register (R0-R31)
int parse_register(const char *str) {
    if (str[0] == 'R' || str[0] == 'r') {
        int reg = atoi(str + 1);
        if (reg >= 0 && reg < 32) {
            return reg;
        }
    }
    return -1;
}

// Parse immediate value
int64_t parse_immediate(const char *str) {
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        return strtoll(str, NULL, 16);
    }
    return strtoll(str, NULL, 10);
}

// Find opcode definition
OpcodeDef* find_opcode(const char *mnemonic) {
    for (int i = 0; opcodes[i].mnemonic[0] != '\0'; i++) {
        if (strcasecmp(opcodes[i].mnemonic, mnemonic) == 0) {
            return &opcodes[i];
        }
    }
    return NULL;
}

// Add label
void add_label(const char *name, uint64_t address) {
    if (label_count < MAX_LABELS) {
        strncpy(labels[label_count].name, name, 63);
        labels[label_count].address = address;
        label_count++;
    }
}

// Find label address
int64_t find_label(const char *name) {
    for (int i = 0; i < label_count; i++) {
        if (strcmp(labels[i].name, name) == 0) {
            return labels[i].address;
        }
    }
    return -1;
}

// Trim whitespace
char* trim(char *str) {
    while (isspace(*str)) str++;
    if (*str == 0) return str;
    char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    *(end + 1) = 0;
    return str;
}

// Encode R-type instruction
uint32_t encode_r_type(uint8_t opcode, uint8_t rd, uint8_t rs1, uint8_t rs2) {
    return ((uint32_t)opcode << 24) | 
           ((uint32_t)(rd & 0x1F) << 19) |
           ((uint32_t)(rs1 & 0x1F) << 14) |
           ((uint32_t)(rs2 & 0x1F) << 9);
}

// Encode I-type instruction
uint32_t encode_i_type(uint8_t opcode, uint8_t rd, uint8_t rs1, int16_t imm) {
    return ((uint32_t)opcode << 24) |
           ((uint32_t)(rd & 0x1F) << 19) |
           ((uint32_t)(rs1 & 0x1F) << 14) |
           ((uint32_t)(imm & 0x3FFF));
}

// Encode J-type instruction
uint32_t encode_j_type(uint8_t opcode, int32_t addr) {
    return ((uint32_t)opcode << 24) |
           ((uint32_t)(addr & 0xFFFFFF));
}

// Parse and assemble one line (first pass - collect labels)
void first_pass_line(char *line, int line_number) {
    (void)line_number;  // Mark as intentionally unused
    line = trim(line);
    
    // Skip empty lines and comments
    if (line[0] == 0 || line[0] == ';') {
        return;
    }
    
    // Check for label
    char *colon = strchr(line, ':');
    if (colon) {
        *colon = 0;
        char *label = trim(line);
        add_label(label, current_address);
        line = trim(colon + 1);
        if (line[0] == 0) {
            return;
        }
    }
    
    // Check for directives
    if (line[0] == '.') {
        if (strncmp(line, ".text", 5) == 0) {
            current_address = 0x0000000000001000;
        } else if (strncmp(line, ".data", 5) == 0) {
            current_address = 0x0000000000100000;
        }
        return;
    }
    
    // It's an instruction
    current_address += 4;
}

// Parse and assemble one line (second pass - generate code)
void second_pass_line(char *line, int line_number, uint64_t *addr) {
    line = trim(line);
    
    // Skip empty lines and comments
    if (line[0] == 0 || line[0] == ';') {
        return;
    }
    
    // Skip labels
    char *colon = strchr(line, ':');
    if (colon) {
        line = trim(colon + 1);
        if (line[0] == 0) {
            return;
        }
    }
    
    // Skip directives
    if (line[0] == '.') {
        return;
    }
    
    // Parse instruction
    char mnemonic[16];
    sscanf(line, "%15s", mnemonic);
    
    OpcodeDef *op = find_opcode(mnemonic);
    if (!op) {
        fprintf(stderr, "Error at line %d: Unknown mnemonic '%s'\n", 
                line_number, mnemonic);
        return;
    }
    
    char *args = strchr(line, ' ');
    if (args) {
        args = trim(args);
    }
    
    uint32_t instruction = 0;
    
    switch (op->type) {
        case 'R': {
            if (op->opcode == 0x00 || op->opcode == 0x01 || op->opcode == 0x3A) {
                // NOP, HALT, RET - no operands
                instruction = encode_r_type(op->opcode, 0, 0, 0);
            } else if (op->opcode == 0x12 || op->opcode == 0x3B) {
                // NOT rd, rs1 or JR rs1
                int rd, rs1;
                if (sscanf(args, "R%d, R%d", &rd, &rs1) == 2 ||
                    sscanf(args, "r%d, r%d", &rd, &rs1) == 2) {
                    instruction = encode_r_type(op->opcode, rd, rs1, 0);
                } else if (sscanf(args, "R%d", &rd) == 1 || 
                          sscanf(args, "r%d", &rd) == 1) {
                    instruction = encode_r_type(op->opcode, 0, rd, 0);
                }
            } else if (op->opcode == 0x19 || op->opcode == 0x1B) {
                // CMP rs1, rs2 or TEST rs1, rs2 - compare instructions with no destination
                int rs1, rs2;
                if (sscanf(args, "R%d, R%d", &rs1, &rs2) == 2 ||
                    sscanf(args, "r%d, r%d", &rs1, &rs2) == 2) {
                    instruction = encode_r_type(op->opcode, 0, rs1, rs2);
                }
            } else {
                // Normal R-type: rd, rs1, rs2
                int rd, rs1, rs2;
                if (sscanf(args, "R%d, R%d, R%d", &rd, &rs1, &rs2) == 3 ||
                    sscanf(args, "r%d, r%d, r%d", &rd, &rs1, &rs2) == 3) {
                    instruction = encode_r_type(op->opcode, rd, rs1, rs2);
                }
            }
            break;
        }
        
        case 'I': {
            int rd, rs1;
            int64_t imm;
            char imm_str[64];
            
            // Special handling for SYSCALL - just immediate, no registers
            if (op->opcode == 0x50) {  // SYSCALL
                if (sscanf(args, "%s", imm_str) == 1) {
                    imm = parse_immediate(imm_str);
                    instruction = encode_i_type(op->opcode, 0, 0, (int16_t)imm);
                }
            } else if (sscanf(args, "R%d, R%d, %s", &rd, &rs1, imm_str) == 3 ||
                sscanf(args, "r%d, r%d, %s", &rd, &rs1, imm_str) == 3) {
                imm = parse_immediate(imm_str);
                instruction = encode_i_type(op->opcode, rd, rs1, (int16_t)imm);
            } else if (sscanf(args, "R%d, %s", &rd, imm_str) == 2 ||
                      sscanf(args, "r%d, %s", &rd, imm_str) == 2) {
                imm = parse_immediate(imm_str);
                instruction = encode_i_type(op->opcode, rd, 0, (int16_t)imm);
            }
            break;
        }
        
        case 'J': {
            char label[64];
            if (sscanf(args, "%63s", label) == 1) {
                int64_t target_addr = find_label(label);
                if (target_addr != -1) {
                    int64_t offset = (target_addr - *addr) >> 2;
                    instruction = encode_j_type(op->opcode, (int32_t)offset);
                } else {
                    fprintf(stderr, "Error at line %d: Undefined label '%s'\n",
                           line_number, label);
                    instruction = encode_j_type(op->opcode, 0);
                }
            }
            break;
        }
        
        case 'M': {
            // LOAD rd, offset(rs1) or STORE rd, offset(rs1)
            int rd, rs1;
            int64_t offset;
            if (sscanf(args, "R%d, %ld(R%d)", &rd, &offset, &rs1) == 3 ||
                sscanf(args, "r%d, %ld(r%d)", &rd, &offset, &rs1) == 3) {
                instruction = encode_i_type(op->opcode, rd, rs1, (int16_t)offset);
            } else if (sscanf(args, "R%d, (R%d)", &rd, &rs1) == 2 ||
                      sscanf(args, "r%d, (r%d)", &rd, &rs1) == 2) {
                instruction = encode_i_type(op->opcode, rd, rs1, 0);
            } else if (sscanf(args, "R%d", &rd) == 1 || 
                      sscanf(args, "r%d", &rd) == 1) {
                // PUSH/POP
                instruction = encode_i_type(op->opcode, rd, 0, 0);
            }
            break;
        }
    }
    
    if (instruction_count < MAX_INSTRUCTIONS) {
        instructions[instruction_count].instruction = instruction;
        instructions[instruction_count].address = *addr;
        instructions[instruction_count].line_number = line_number;
        instruction_count++;
    }
    
    *addr += 4;
}

// Assemble file
int assemble_file(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    if (!in) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", input_file);
        return -1;
    }
    
    char line[MAX_LINE];
    int line_number = 0;
    
    // First pass - collect labels
    printf("First pass: collecting labels...\n");
    current_address = 0x0000000000001000;
    while (fgets(line, sizeof(line), in)) {
        line_number++;
        first_pass_line(line, line_number);
    }
    
    printf("Found %d labels\n", label_count);
    
    // Second pass - generate code
    printf("Second pass: generating code...\n");
    rewind(in);
    line_number = 0;
    uint64_t addr = 0x0000000000001000;
    
    while (fgets(line, sizeof(line), in)) {
        line_number++;
        second_pass_line(line, line_number, &addr);
    }
    
    fclose(in);
    
    printf("Generated %d instructions\n", instruction_count);
    
    // Write output
    FILE *out = fopen(output_file, "wb");
    if (!out) {
        fprintf(stderr, "Error: Cannot open output file '%s'\n", output_file);
        return -1;
    }
    
    // Write instructions to binary file
    for (int i = 0; i < instruction_count; i++) {
        uint32_t inst = instructions[i].instruction;
        // Write as little-endian
        fputc(inst & 0xFF, out);
        fputc((inst >> 8) & 0xFF, out);
        fputc((inst >> 16) & 0xFF, out);
        fputc((inst >> 24) & 0xFF, out);
    }
    
    fclose(out);
    
    printf("Assembly complete: %s -> %s\n", input_file, output_file);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("A1M Assembler\n");
        printf("Usage: %s <input.asm> [-o <output.bin>]\n", argv[0]);
        return 1;
    }
    
    const char *input_file = argv[1];
    const char *output_file = "a.out";
    
    // Parse output file option
    for (int i = 2; i < argc - 1; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            output_file = argv[i + 1];
            break;
        }
    }
    
    return assemble_file(input_file, output_file);
}
