# A1M CPU Getting Started Guide

## Introduction

Welcome to the A1M CPU project! This guide will help you get started with building, using, and programming the A1M 64-bit CPU.

## Prerequisites

### Required
- GCC compiler (4.8 or later)
- Make
- Linux/Unix environment (or WSL on Windows)

### Optional
- Icarus Verilog (for Verilog simulation)
- GTK 3 development libraries (for GUI)
- GTKWave (for waveform viewing)

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install iverilog gtkwave  # For Verilog
sudo apt-get install libgtk-3-dev      # For GUI
```

**Fedora:**
```bash
sudo dnf install gcc make
sudo dnf install iverilog gtkwave
sudo dnf install gtk3-devel
```

**Arch Linux:**
```bash
sudo pacman -S base-devel
sudo pacman -S iverilog gtkwave
sudo pacman -S gtk3
```

## Building the Project

1. **Clone or navigate to the project directory:**
```bash
cd A1MCPU
```

2. **Make build script executable:**
```bash
chmod +x build.sh test.sh
```

3. **Build all components:**
```bash
./build.sh
```

This will build:
- CPU Emulator (`emulator/a1m-emu`)
- Assembler (`assembler/a1m-asm`)
- Compiler (`compiler/algo-compiler`)
- GUI (if GTK is available)

## Quick Start Tutorial

### 1. Writing Your First Assembly Program

Create a file `hello.asm`:
```asm
; Hello World in A1M Assembly
.text
main:
    MOVI R1, 72      ; 'H'
    SYSCALL 0x02     ; print_char
    MOVI R1, 105     ; 'i'
    SYSCALL 0x02
    MOVI R1, 10      ; '\n'
    SYSCALL 0x02
    
    MOVI R1, 0
    SYSCALL 0x00     ; exit
    HALT
```

### 2. Assemble the Program

```bash
./assembler/a1m-asm hello.asm -o hello.bin
```

### 3. Run in Emulator

```bash
./emulator/a1m-emu hello.bin
```

### 4. Debug Mode

Run with register dump:
```bash
./emulator/a1m-emu hello.bin -r
```

Run in debug mode (shows each instruction):
```bash
./emulator/a1m-emu hello.bin -d
```

Step through execution:
```bash
./emulator/a1m-emu hello.bin -s
```

## Writing Algo Programs

### 1. Create an Algo Program

Create `factorial.algo`:
```algo
func factorial(n: int) -> int {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

func main() -> int {
    let result = factorial(5);
    print(result);
    return 0;
}
```

### 2. Compile to Assembly

```bash
./compiler/algo-compiler factorial.algo -o factorial.asm
```

### 3. Assemble and Run

```bash
./assembler/a1m-asm factorial.asm -o factorial.bin
./emulator/a1m-emu factorial.bin
```

## Using the GUI

If GTK is installed:

```bash
./gui/a1m-gui
```

Features:
- Code editor with syntax highlighting
- CPU register visualization
- Memory viewer
- Step-by-step execution
- Breakpoint support

## Verilog Simulation

### 1. Navigate to Verilog directory

```bash
cd verilog
```

### 2. Create a test program hex file

```bash
cd ../assembler
./a1m-asm ../examples/asm/hello.asm -o program.bin
# Convert to hex format (you'll need a bin2hex utility)
cd ../verilog
```

### 3. Run simulation

```bash
iverilog -o sim testbench/a1m_testbench.v top.v cpu/*.v memory/*.v
vvp sim
```

### 4. View waveforms

```bash
gtkwave a1m_cpu.vcd
```

## Example Programs

The `examples/` directory contains:

### Assembly Examples
- `hello.asm` - Hello World
- `fibonacci.asm` - Recursive Fibonacci
- `array_sum.asm` - Array summation

### Algo Examples
- `hello.algo` - Hello World
- `fibonacci.algo` - Fibonacci sequence
- `factorial.algo` - Factorial calculator

## Common Operations

### Arithmetic
```asm
ADD R1, R2, R3      ; R1 = R2 + R3
ADDI R1, R2, 100    ; R1 = R2 + 100
SUB R1, R2, R3      ; R1 = R2 - R3
MUL R1, R2, R3      ; R1 = R2 * R3
DIV R1, R2, R3      ; R1 = R2 / R3
```

### Memory Operations
```asm
LOAD R1, 0(R2)      ; R1 = memory[R2 + 0]
STORE R1, 8(R2)     ; memory[R2 + 8] = R1
PUSH R1             ; Push R1 to stack
POP R1              ; Pop from stack to R1
```

### Control Flow
```asm
JMP label           ; Jump to label
JZ label            ; Jump if zero flag set
CALL function       ; Call subroutine
RET                 ; Return from subroutine
```

### System Calls
```asm
SYSCALL 0x00        ; exit(R1)
SYSCALL 0x01        ; print_int(R1)
SYSCALL 0x02        ; print_char(R1)
SYSCALL 0x03        ; read_int() -> R1
```

## Troubleshooting

### Build Errors

**Problem:** `make: command not found`
**Solution:** Install build-essential or development tools

**Problem:** GTK headers not found
**Solution:** Install libgtk-3-dev or skip GUI build

### Runtime Errors

**Problem:** Segmentation fault
**Solution:** Check memory addresses are within bounds

**Problem:** Invalid opcode
**Solution:** Verify assembly syntax and opcodes

### Assembly Errors

**Problem:** Undefined label
**Solution:** Ensure all labels are defined before use

**Problem:** Register out of range
**Solution:** Use R0-R31 only

## Performance Tips

1. **Use immediate instructions** when possible (faster than loading from memory)
2. **Minimize memory access** - keep frequently used values in registers
3. **Avoid deep recursion** - use iteration when possible
4. **Use appropriate data types** - LOADB for bytes, LOAD for words

## Next Steps

1. Read the full [ISA documentation](docs/ISA.md)
2. Study the [Architecture guide](docs/ARCHITECTURE.md)
3. Learn [Algo language syntax](docs/ALGO_SPEC.md)
4. Explore example programs in `examples/`
5. Write your own programs!

## Getting Help

- Check the documentation in `docs/`
- Review example programs in `examples/`
- Examine the emulator source code for implementation details

## Contributing

This is an educational project. Feel free to:
- Add new instructions
- Improve the compiler
- Enhance the GUI
- Write more example programs
- Optimize the emulator

Happy coding with A1M!
