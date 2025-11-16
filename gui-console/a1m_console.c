/*
 * A1M CPU Console - Interactive terminal console for A1M CPU Emulator
 * Runs Algo language programs on the custom A1M emulator
 * Pure C implementation - no external dependencies
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CODE 10000

// ANSI Color codes
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define BG_BLACK      "\033[40m"
#define BG_BLUE       "\033[44m"
#define BG_GREEN      "\033[42m"
#define BG_RED        "\033[41m"

void clear_screen() {
    printf("\033[2J\033[H");
}

void print_header() {
    printf("\n");
    printf(COLOR_CYAN "╔════════════════════════════════════════════════════════════════════╗\n" COLOR_RESET);
    printf(COLOR_CYAN "║" COLOR_RESET COLOR_BOLD COLOR_YELLOW "           A1M CPU Console - Algo Development Environment          " COLOR_RESET COLOR_CYAN "║\n" COLOR_RESET);
    printf(COLOR_CYAN "║" COLOR_RESET COLOR_GREEN "                    Custom 64-bit CPU Emulator                      " COLOR_RESET COLOR_CYAN "║\n" COLOR_RESET);
    printf(COLOR_CYAN "╚════════════════════════════════════════════════════════════════════╝\n" COLOR_RESET);
    printf("\n");
}

void print_box(const char *title, const char *content, const char *color) {
    int title_len = strlen(title);
    int content_len = strlen(content);
    int width = (title_len > content_len) ? title_len : content_len;
    if (width < 60) width = 60;
    
    printf("%s┌", color);
    for (int i = 0; i < width + 4; i++) printf("─");
    printf("┐\n");
    
    printf("│ %s%-*s%s │\n", COLOR_BOLD, width, title, color);
    
    printf("├");
    for (int i = 0; i < width + 4; i++) printf("─");
    printf("┤\n");
    
    printf("│  %-*s │\n", width, content);
    
    printf("└");
    for (int i = 0; i < width + 4; i++) printf("─");
    printf("┘%s\n", COLOR_RESET);
}

void print_progress_bar(const char *label, int percent) {
    int bar_width = 40;
    int filled = (bar_width * percent) / 100;
    
    printf("%s[", COLOR_CYAN);
    for (int i = 0; i < bar_width; i++) {
        if (i < filled) {
            printf(COLOR_GREEN "█" COLOR_CYAN);
        } else {
            printf("░");
        }
    }
    printf("] %s%d%%%s %s\n", COLOR_YELLOW, percent, COLOR_CYAN, label);
    printf(COLOR_RESET);
}

void animate_dots(const char *message, int count) {
    printf("\r%s%s%s", COLOR_YELLOW, message, COLOR_RESET);
    for (int i = 0; i < count; i++) {
        printf(".");
        fflush(stdout);
        usleep(150000); // 150ms
    }
    printf("\n");
}

void print_menu() {
    printf("\n");
    printf(COLOR_CYAN "┌────────────────────────────────────────────────────────────────────┐\n" COLOR_RESET);
    printf(COLOR_CYAN "│ " COLOR_BOLD COLOR_GREEN "[1]" COLOR_RESET COLOR_WHITE " Run Algo Program    " COLOR_RESET);
    printf(COLOR_BOLD COLOR_GREEN "[2]" COLOR_RESET COLOR_WHITE " Run Assembly    " COLOR_RESET);
    printf(COLOR_BOLD COLOR_GREEN "[3]" COLOR_RESET COLOR_WHITE " Run Binary         " COLOR_RESET COLOR_CYAN "│\n" COLOR_RESET);
    printf(COLOR_CYAN "│ " COLOR_BOLD COLOR_YELLOW "[4]" COLOR_RESET COLOR_WHITE " View Last Output    " COLOR_RESET);
    printf(COLOR_BOLD COLOR_YELLOW "[5]" COLOR_RESET COLOR_WHITE " Help            " COLOR_RESET);
    printf(COLOR_BOLD COLOR_RED "[6]" COLOR_RESET COLOR_WHITE " Exit               " COLOR_RESET COLOR_CYAN "│\n" COLOR_RESET);
    printf(COLOR_CYAN "└────────────────────────────────────────────────────────────────────┘\n" COLOR_RESET);
    printf("\n" COLOR_BOLD COLOR_MAGENTA "Your choice: " COLOR_RESET);
}

int run_command_silent(const char *cmd) {
    int ret = system(cmd);
#ifdef _WIN32
    // On Windows, system() returns the exit code directly
    return ret;
#else
    // On Unix, use WEXITSTATUS macro
    return WEXITSTATUS(ret);
#endif
}

void run_algo_program() {
    char filename[512];
    
    printf("\n");
    printf(COLOR_CYAN "════════════════════════════════════════════════════════════════\n" COLOR_RESET);
    printf(COLOR_BOLD COLOR_YELLOW "  📝 Algo Program Execution\n" COLOR_RESET);
    printf(COLOR_CYAN "════════════════════════════════════════════════════════════════\n" COLOR_RESET);
    printf("\n");
    
    printf(COLOR_BOLD "Enter .algo filename: " COLOR_RESET);
    if (!fgets(filename, sizeof(filename), stdin)) {
        return;
    }
    filename[strcspn(filename, "\n")] = 0;
    
    // Check if file exists
    if (access(filename, R_OK) != 0) {
        printf("\n" COLOR_RED "❌ Error: Cannot read file '%s'\n" COLOR_RESET, filename);
        printf("\n" COLOR_YELLOW "Press Enter to continue..." COLOR_RESET);
        getchar();
        return;
    }
    
    printf("\n");
    animate_dots("Initializing compiler", 3);
    
    printf("\n" COLOR_BOLD COLOR_BLUE "📝 Step 1: Compiling Algo → Assembly" COLOR_RESET "\n");
    printf(COLOR_CYAN "────────────────────────────────────────────────────────────────\n" COLOR_RESET);
    print_progress_bar("Lexical Analysis", 33);
    
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "./compiler/algo-compiler \"%s\" -o /tmp/a1m_temp.asm", filename);
    
    int ret = system(cmd);
    
    if (ret != 0) {
        printf("\n" COLOR_RED "❌ Compilation failed!\n" COLOR_RESET);
        printf(COLOR_YELLOW "\nPress Enter to continue..." COLOR_RESET);
        getchar();
        return;
    }
    
    print_progress_bar("Parsing Complete", 66);
    print_progress_bar("Code Generation", 100);
    printf(COLOR_GREEN "✓ Compilation successful\n" COLOR_RESET);
    usleep(300000);
    
    printf("\n" COLOR_BOLD COLOR_BLUE "⚙️  Step 2: Assembling Assembly → Binary" COLOR_RESET "\n");
    printf(COLOR_CYAN "────────────────────────────────────────────────────────────────\n" COLOR_RESET);
    print_progress_bar("First Pass - Labels", 50);
    
    ret = system("./assembler/a1m-asm /tmp/a1m_temp.asm -o /tmp/a1m_temp.bin");
    
    if (ret != 0) {
        printf("\n" COLOR_RED "❌ Assembly failed!\n" COLOR_RESET);
        printf(COLOR_YELLOW "\nPress Enter to continue..." COLOR_RESET);
        getchar();
        return;
    }
    
    print_progress_bar("Second Pass - Code Gen", 100);
    printf(COLOR_GREEN "✓ Assembly successful\n" COLOR_RESET);
    usleep(300000);
    
    printf("\n" COLOR_BOLD COLOR_MAGENTA "🚀 Step 3: Running on A1M CPU Emulator" COLOR_RESET "\n");
    printf(COLOR_CYAN "════════════════════════════════════════════════════════════════\n" COLOR_RESET);
    printf("\n");
    
    ret = system("./emulator/a1m-emu /tmp/a1m_temp.bin | tee /tmp/a1m_last_output.txt");
    
    printf("\n" COLOR_CYAN "════════════════════════════════════════════════════════════════\n" COLOR_RESET);
    
    if (ret == 0) {
        printf(COLOR_GREEN "✓ Execution complete\n" COLOR_RESET);
    } else {
#ifdef _WIN32
        printf(COLOR_YELLOW "⚠ Execution finished with exit code %d\n" COLOR_RESET, ret);
#else
        printf(COLOR_YELLOW "⚠ Execution finished with exit code %d\n" COLOR_RESET, WEXITSTATUS(ret));
#endif
    }
    
    printf(COLOR_YELLOW "\nPress Enter to continue..." COLOR_RESET);
    getchar();
}

void run_assembly_program() {
    char filename[512];
    
    printf("\n");
    printf(COLOR_CYAN "════════════════════════════════════════════════════════════════\n" COLOR_RESET);
    printf(COLOR_BOLD COLOR_YELLOW "  ⚙️  Assembly Program Execution\n" COLOR_RESET);
    printf(COLOR_CYAN "════════════════════════════════════════════════════════════════\n" COLOR_RESET);
    printf("\n");
    
    printf(COLOR_BOLD "Enter .asm filename: " COLOR_RESET);
    if (!fgets(filename, sizeof(filename), stdin)) {
        return;
    }
    filename[strcspn(filename, "\n")] = 0;
    
    if (access(filename, R_OK) != 0) {
        printf("\n" COLOR_RED "❌ Error: Cannot read file '%s'\n" COLOR_RESET, filename);
        printf(COLOR_YELLOW "\nPress Enter to continue..." COLOR_RESET);
        getchar();
        return;
    }
    
    printf("\n");
    animate_dots("Loading assembler", 3);
    
    printf("\n" COLOR_BOLD COLOR_BLUE "⚙️  Assembling Assembly → Binary" COLOR_RESET "\n");
    printf(COLOR_CYAN "────────────────────────────────────────────────────────────────\n" COLOR_RESET);
    print_progress_bar("First Pass", 50);
    
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "./assembler/a1m-asm \"%s\" -o /tmp/a1m_temp.bin", filename);
    
    int ret = system(cmd);
    
    if (ret != 0) {
        printf("\n" COLOR_RED "❌ Assembly failed!\n" COLOR_RESET);
        printf(COLOR_YELLOW "\nPress Enter to continue..." COLOR_RESET);
        getchar();
        return;
    }
    
    print_progress_bar("Second Pass", 100);
    printf(COLOR_GREEN "✓ Assembly successful\n" COLOR_RESET);
    usleep(300000);
    
    printf("\n" COLOR_BOLD COLOR_MAGENTA "🚀 Running on A1M CPU Emulator" COLOR_RESET "\n");
    printf(COLOR_CYAN "════════════════════════════════════════════════════════════════\n" COLOR_RESET);
    printf("\n");
    
    ret = system("./emulator/a1m-emu /tmp/a1m_temp.bin | tee /tmp/a1m_last_output.txt");
    
    printf("\n" COLOR_CYAN "════════════════════════════════════════════════════════════════\n" COLOR_RESET);
    
    if (ret == 0) {
        printf(COLOR_GREEN "✓ Execution complete\n" COLOR_RESET);
    } else {
#ifdef _WIN32
        printf(COLOR_YELLOW "⚠ Execution finished with exit code %d\n" COLOR_RESET, ret);
#else
        printf(COLOR_YELLOW "⚠ Execution finished with exit code %d\n" COLOR_RESET, WEXITSTATUS(ret));
#endif
    }
    
    printf(COLOR_YELLOW "\nPress Enter to continue..." COLOR_RESET);
    getchar();
}

void run_binary_program() {
    char filename[512];
    
    printf("\n");
    printf("════════════════════════════════════════════════════════════════\n");
    printf("  Binary Program Execution\n");
    printf("════════════════════════════════════════════════════════════════\n\n");
    
    printf("Enter .bin filename: ");
    if (!fgets(filename, sizeof(filename), stdin)) {
        return;
    }
    filename[strcspn(filename, "\n")] = 0;
    
    if (access(filename, R_OK) != 0) {
        printf("\n❌ Error: Cannot read file '%s'\n", filename);
        printf("\nPress Enter to continue...");
        getchar();
        return;
    }
    
    printf("\n🚀 Running on A1M CPU Emulator...\n");
    printf("────────────────────────────────────────────────────────────────\n\n");
    
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "./emulator/a1m-emu \"%s\" | tee /tmp/a1m_last_output.txt", filename);
    
    int ret = system(cmd);
    
    printf("\n────────────────────────────────────────────────────────────────\n");
    
    if (ret == 0) {
        printf("✓ Execution complete\n");
    } else {
#ifdef _WIN32
        printf("⚠ Execution finished with exit code %d\n", ret);
#else
        printf("⚠ Execution finished with exit code %d\n", WEXITSTATUS(ret));
#endif
    }
    
    printf("\nPress Enter to continue...");
    getchar();
}

void view_last_output() {
    printf("\n");
    printf("════════════════════════════════════════════════════════════════\n");
    printf("  Last Execution Output\n");
    printf("════════════════════════════════════════════════════════════════\n\n");
    
    if (access("/tmp/a1m_last_output.txt", R_OK) == 0) {
        int ret = system("cat /tmp/a1m_last_output.txt");
        (void)ret; // Suppress unused warning
    } else {
        printf("No previous output available.\n");
    }
    
    printf("\n════════════════════════════════════════════════════════════════\n");
    printf("\nPress Enter to continue...");
    getchar();
}

void show_help() {
    clear_screen();
    print_header();
    
    printf("════════════════════════════════════════════════════════════════\n");
    printf("  HELP - A1M CPU Console\n");
    printf("════════════════════════════════════════════════════════════════\n\n");
    
    printf("What is A1M?\n");
    printf("─────────────\n");
    printf("A1M is a custom 64-bit RISC CPU with:\n");
    printf("  • 32 general-purpose registers (R0-R31)\n");
    printf("  • 5-stage pipeline architecture\n");
    printf("  • 50+ custom instructions\n");
    printf("  • Full Verilog implementation for FPGA\n\n");
    
    printf("What is Algo?\n");
    printf("──────────────\n");
    printf("Algo is a high-level programming language designed specifically\n");
    printf("for the A1M CPU. Algo code (.algo files) compiles directly to\n");
    printf("A1M assembly language.\n\n");
    
    printf("Workflow:\n");
    printf("──────────\n");
    printf("  1. Write Algo code (.algo file)\n");
    printf("  2. Compiler converts .algo → .asm (A1M assembly)\n");
    printf("  3. Assembler converts .asm → .bin (A1M machine code)\n");
    printf("  4. Emulator runs .bin on virtual A1M CPU\n\n");
    
    printf("Menu Options:\n");
    printf("──────────────\n");
    printf("  [1] Run Algo Program\n");
    printf("      Automatically compile, assemble, and run a .algo file\n\n");
    
    printf("  [2] Run Assembly\n");
    printf("      Assemble and run a .asm file directly\n\n");
    
    printf("  [3] Run Binary\n");
    printf("      Run a pre-assembled .bin file\n\n");
    
    printf("  [4] View Last Output\n");
    printf("      Display output from the last program execution\n\n");
    
    printf("  [5] Help\n");
    printf("      Display this help screen\n\n");
    
    printf("  [6] Exit\n");
    printf("      Close the console\n\n");
    
    printf("Example Files:\n");
    printf("───────────────\n");
    printf("  examples/asm/hello.asm      - Simple assembly program\n");
    printf("  examples/asm/fibonacci.asm  - Fibonacci calculator\n");
    printf("  examples/algo/hello.algo    - Algo hello world\n\n");
    
    printf("Command Line Usage:\n");
    printf("────────────────────\n");
    printf("  ./console.sh                    - Interactive mode\n");
    printf("  ./console.sh <file.algo>        - Quick run mode\n\n");
    
    printf("════════════════════════════════════════════════════════════════\n");
    printf("\nPress Enter to return to menu...");
    getchar();
}

int main(int argc, char *argv[]) {
    int ret; // For system() return values
    
    // Check if required tools exist
    if (access("./emulator/a1m-emu", X_OK) != 0) {
        printf("Error: A1M emulator not found!\n");
        printf("Please run ./build.sh first to build all components.\n");
        return 1;
    }
    
    if (access("./assembler/a1m-asm", X_OK) != 0) {
        printf("Error: A1M assembler not found!\n");
        printf("Please run ./build.sh first.\n");
        return 1;
    }
    
    if (access("./compiler/algo-compiler", X_OK) != 0) {
        printf("Error: Algo compiler not found!\n");
        printf("Please run ./build.sh first.\n");
        return 1;
    }
    
    // Quick run mode if file provided
    if (argc > 1) {
        char *filename = argv[1];
        char *ext = strrchr(filename, '.');
        
        if (!ext) {
            printf("Error: Unknown file type\n");
            return 1;
        }
        
        clear_screen();
        print_header();
        
        if (strcmp(ext, ".algo") == 0) {
            // Run algo file directly
            printf("Quick Run Mode: %s\n\n", filename);
            
            printf("📝 Compiling...\n");
            char cmd[1024];
            snprintf(cmd, sizeof(cmd), "./compiler/algo-compiler \"%s\" -o /tmp/a1m_temp.asm", filename);
            if (system(cmd) != 0) {
                printf("❌ Compilation failed\n");
                return 1;
            }
            
            printf("⚙️  Assembling...\n");
            if (system("./assembler/a1m-asm /tmp/a1m_temp.asm -o /tmp/a1m_temp.bin") != 0) {
                printf("❌ Assembly failed\n");
                return 1;
            }
            
            printf("🚀 Running...\n\n");
            printf("════════════════════════════════════════════════════════════════\n");
            ret = system("./emulator/a1m-emu /tmp/a1m_temp.bin");
            (void)ret; // Suppress unused warning
            printf("════════════════════════════════════════════════════════════════\n");
            
        } else if (strcmp(ext, ".asm") == 0) {
            printf("Quick Run Mode: %s\n\n", filename);
            
            printf("⚙️  Assembling...\n");
            char cmd[1024];
            snprintf(cmd, sizeof(cmd), "./assembler/a1m-asm \"%s\" -o /tmp/a1m_temp.bin", filename);
            if (system(cmd) != 0) {
                printf("❌ Assembly failed\n");
                return 1;
            }
            
            printf("🚀 Running...\n\n");
            printf("════════════════════════════════════════════════════════════════\n");
            ret = system("./emulator/a1m-emu /tmp/a1m_temp.bin");
            (void)ret; // Suppress unused warning
            printf("════════════════════════════════════════════════════════════════\n");
            
        } else if (strcmp(ext, ".bin") == 0) {
            printf("Quick Run Mode: %s\n\n", filename);
            printf("🚀 Running...\n\n");
            printf("════════════════════════════════════════════════════════════════\n");
            char cmd[1024];
            snprintf(cmd, sizeof(cmd), "./emulator/a1m-emu \"%s\"", filename);
            ret = system(cmd);
            (void)ret; // Suppress unused warning
            printf("════════════════════════════════════════════════════════════════\n");
            
        } else {
            printf("Error: Unknown file extension '%s'\n", ext);
            printf("Supported: .algo, .asm, .bin\n");
            return 1;
        }
        
        return 0;
    }
    
    // Interactive mode
    int running = 1;
    while (running) {
        clear_screen();
        print_header();
        print_menu();
        
        char choice[10];
        if (!fgets(choice, sizeof(choice), stdin)) {
            break;
        }
        
        switch (choice[0]) {
            case '1':
                run_algo_program();
                break;
                
            case '2':
                run_assembly_program();
                break;
                
            case '3':
                run_binary_program();
                break;
                
            case '4':
                view_last_output();
                break;
                
            case '5':
                show_help();
                break;
                
            case '6':
                running = 0;
                break;
                
            default:
                printf("\nInvalid choice. Press Enter to continue...");
                getchar();
                break;
        }
    }
    
    clear_screen();
    printf("A1M CPU Console closed.\n");
    printf("Thank you for using the A1M development environment!\n\n");
    
    return 0;
}
