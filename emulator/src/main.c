#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a1m_cpu.h"

void print_usage(const char *program) {
    printf("A1M CPU Emulator\n");
    printf("Usage: %s [options] <program.bin>\n", program);
    printf("Options:\n");
    printf("  -d, --debug      Enable debug mode\n");
    printf("  -s, --step       Single-step execution\n");
    printf("  -r, --registers  Dump registers after execution\n");
    printf("  -m, --memory     Dump memory after execution\n");
    printf("  -h, --help       Show this help message\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    bool debug_mode = false;
    bool step_mode = false;
    bool dump_regs = false;
    bool dump_mem = false;
    const char *program_file = NULL;
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            debug_mode = true;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--step") == 0) {
            step_mode = true;
        } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--registers") == 0) {
            dump_regs = true;
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--memory") == 0) {
            dump_mem = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else {
            program_file = argv[i];
        }
    }
    
    if (!program_file) {
        fprintf(stderr, "Error: No program file specified\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Create CPU
    CPU *cpu = cpu_create();
    if (!cpu) {
        return 1;
    }
    
    // Load program
    if (cpu_load_program(cpu, program_file) != 0) {
        cpu_destroy(cpu);
        return 1;
    }
    
    cpu->debug_mode = debug_mode;

    // Disable stdout buffering so emulator prints appear immediately in terminals
    // This helps avoid missing output on some Linux terminals when the program
    // exits immediately after printing.
    setbuf(stdout, NULL);
    
    // Only show startup info in debug mode
    if (debug_mode) {
        printf("\nA1M CPU Emulator Starting...\n");
        printf("Program: %s\n", program_file);
        printf("Initial PC: 0x%016llx\n\n", (unsigned long long)cpu->pc);
    }
    
    // Execute
    if (step_mode) {
        printf("Step mode enabled. Press Enter to step, 'q' to quit, 'r' to run\n");
        char input[10];
        while (!cpu->halted) {
            cpu_dump_registers(cpu);
            printf("\nPress Enter to step: ");
            if (fgets(input, sizeof(input), stdin)) {
                if (input[0] == 'q') {
                    break;
                } else if (input[0] == 'r') {
                    cpu_run(cpu);
                    break;
                }
            }
            cpu_step(cpu);
        }
    } else {
        cpu_run(cpu);
    }
    
    // Only show register results if dump_regs is enabled or in debug mode
    if (dump_regs || debug_mode) {
        printf("\n");
        printf("╔════════════════════════════════════════════════════════════════╗\n");
        printf("║                       EXECUTION RESULTS                        ║\n");
        printf("╚════════════════════════════════════════════════════════════════╝\n\n");
        
        printf("Result Registers:\n");
    
    // Helper function to show ASCII if printable
    char ascii_str[20];
    
    // R1
    if (cpu->registers[1] >= 32 && cpu->registers[1] <= 126) {
        snprintf(ascii_str, sizeof(ascii_str), " ['%c']", (char)cpu->registers[1]);
    } else {
        ascii_str[0] = '\0';
    }
    printf("  R1 = %lld (0x%llx)%s\n", (long long)cpu->registers[1], 
           (unsigned long long)cpu->registers[1], ascii_str);
    
    // R2
    if (cpu->registers[2] != 0) {
        if (cpu->registers[2] >= 32 && cpu->registers[2] <= 126) {
            snprintf(ascii_str, sizeof(ascii_str), " ['%c']", (char)cpu->registers[2]);
        } else {
            ascii_str[0] = '\0';
        }
        printf("  R2 = %lld (0x%llx)%s\n", (long long)cpu->registers[2], 
               (unsigned long long)cpu->registers[2], ascii_str);
    }
    
    // R3
    if (cpu->registers[3] != 0) {
        if (cpu->registers[3] >= 32 && cpu->registers[3] <= 126) {
            snprintf(ascii_str, sizeof(ascii_str), " ['%c']", (char)cpu->registers[3]);
        } else {
            ascii_str[0] = '\0';
        }
        printf("  R3 = %lld (0x%llx)%s\n", (long long)cpu->registers[3], 
               (unsigned long long)cpu->registers[3], ascii_str);
    }
    
    // R4
    if (cpu->registers[4] != 0) {
        if (cpu->registers[4] >= 32 && cpu->registers[4] <= 126) {
            snprintf(ascii_str, sizeof(ascii_str), " ['%c']", (char)cpu->registers[4]);
        } else {
            ascii_str[0] = '\0';
        }
        printf("  R4 = %lld (0x%llx)%s\n", (long long)cpu->registers[4], 
               (unsigned long long)cpu->registers[4], ascii_str);
    }
    
    // R5
    if (cpu->registers[5] != 0) {
        if (cpu->registers[5] >= 32 && cpu->registers[5] <= 126) {
            snprintf(ascii_str, sizeof(ascii_str), " ['%c']", (char)cpu->registers[5]);
        } else {
            ascii_str[0] = '\0';
        }
        printf("  R5 = %lld (0x%llx)%s\n", (long long)cpu->registers[5], 
               (unsigned long long)cpu->registers[5], ascii_str);
    }
    
    // Try to construct a string from R1-R5 if they look like ASCII
    bool all_ascii = true;
    for (int i = 1; i <= 5; i++) {
        if (cpu->registers[i] != 0 && (cpu->registers[i] < 32 || cpu->registers[i] > 126)) {
            all_ascii = false;
            break;
        }
    }
    
    if (all_ascii && cpu->registers[1] != 0) {
        printf("\n  ASCII Text: \"");
        for (int i = 1; i <= 5; i++) {
            if (cpu->registers[i] != 0) {
                printf("%c", (char)cpu->registers[i]);
            }
        }
        printf("\"\n");
    }
    
    printf("\n");
    }  // End of dump_regs || debug_mode condition
    
    // Dump state if requested
    if (dump_regs) {
        cpu_dump_registers(cpu);
    }
    
    if (dump_mem) {
        cpu_dump_memory(cpu, RESET_VECTOR, 256);
    }
    
    // Cleanup
    cpu_destroy(cpu);
    
    return 0;
}
