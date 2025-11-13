# A1M 64-bit Custom CPU Project

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![Language](https://img.shields.io/badge/language-Algo-orange.svg)]()
[![CPU](https://img.shields.io/badge/CPU-64--bit%20RISC-red.svg)]()

A complete custom 64-bit RISC CPU architecture with **Verilog hardware implementation**, **software emulator**, **assembler**, **Algo programming language**, **compiler**, and **interactive console IDE**.

---

## � Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Quick Start](#quick-start)
- [Documentation](#documentation)
- [Examples](#examples)
- [Building](#building)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

---

## 🎯 Overview

The **A1M CPU Project** is a complete computing system from hardware to high-level programming:

```
┌─────────────────────────────────────────────────────────────┐
│                     A1M TOOLCHAIN FLOW                       │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  Algo Source (.algo)                                        │
│         ↓                                                    │
│  Compiler (algo-compiler)                                   │
│         ↓                                                    │
│  Assembly (.asm)                                            │
│         ↓                                                    │
│  Assembler (a1m-asm)                                        │
│         ↓                                                    │
│  Machine Code (.bin)                                        │
│         ↓                                                    │
│  Emulator (a1m-emu) or Verilog CPU                         │
│         ↓                                                    │
│  Execution & Output                                         │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

---

## ✨ Features

### Hardware
- ✅ **64-bit RISC Architecture** - Custom instruction set
- ✅ **32 General Purpose Registers** (R0-R31)
- ✅ **16MB Address Space** - Expandable memory
- ✅ **Verilog Implementation** - FPGA-ready HDL code
- ✅ **Pipeline Design** - 5-stage pipeline (Fetch, Decode, Execute, Memory, Writeback)

### Software
- ✅ **C-Based Emulator** - Fast, accurate CPU simulation
- ✅ **Assembler** - Full A1M assembly language support
- ✅ **Algo Compiler** - High-level language with C-like syntax
- ✅ **Interactive Console** - Colorful IDE with animations
- ✅ **Standard Library** - I/O, math, string functions
- ✅ **Debugger** - Step-through execution, register inspection

### Language (Algo)
- ✅ **Modern Syntax** - Clean, readable C-like syntax
- ✅ **Static Typing** - int, float, double, string, bool types
- ✅ **Functions** - First-class function support
- ✅ **Control Flow** - if/else, while, for, do-while, switch/case, goto loops
- ✅ **Operators** - Arithmetic, logical, bitwise, ++/--, compound assignments, ternary
- ✅ **Standard I/O** - print(), input() functions
- ✅ **Enums** - Compile-time constants

---

## 🏗️ Architecture

### CPU Specifications

| Component | Specification |
|-----------|---------------|
| **Architecture** | 64-bit RISC |
| **Word Size** | 64 bits |
| **Registers** | 32 × 64-bit GPRs |
| **Instruction Size** | 32 bits (fixed) |
| **Memory** | 16MB (expandable) |
| **Addressing** | 64-bit address space |
| **Pipeline** | 5 stages |
| **Clock** | Configurable (FPGA) |

### Instruction Set

- **Arithmetic**: ADD, SUB, MUL, DIV, MOD
- **Logical**: AND, OR, XOR, NOT
- **Shift**: SHL, SHR, SAR
- **Memory**: LOAD, STORE, PUSH, POP
- **Control**: JMP, JZ, JNZ, CALL, RET
- **System**: SYSCALL, HALT
- **Immediate**: MOVI, ADDI, LUI

**📖 See [docs/ISA.md](docs/ISA.md) for complete instruction set**

---

## 🚀 Quick Start

### Prerequisites
```bash
# Required
gcc (C compiler)
make
bash

# Optional (for Verilog)
iverilog (Icarus Verilog)
gtkwave (waveform viewer)
```

### Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/A1MCPU.git
cd A1MCPU

# Build everything
./build.sh

# Or build individually
cd emulator && make
cd ../assembler && make
cd ../compiler && make
cd ../gui-console && make
```

### Your First Program

1. **Create a file** `hello.algo`:
```algo
func main() -> int {
    print("Hello, A1M CPU!");
    return 0;
}
```

2. **Run it**:
```bash
./console.sh hello.algo
```

Output:
```
Hello, A1M CPU!
```

That's it! The console automatically compiles, assembles, and runs your code.

---

## 📚 Documentation

| Document | Description |
|----------|-------------|
| [LANGUAGE_SPEC.md](docs/LANGUAGE_SPEC.md) | Complete Algo language specification |
| [COMPILER_DESIGN.md](docs/COMPILER_DESIGN.md) | Compiler architecture and design |
| [ISA.md](docs/ISA.md) | Instruction Set Architecture |
| [ARCHITECTURE.md](docs/ARCHITECTURE.md) | CPU hardware design |
| [API_REFERENCE.md](docs/API_REFERENCE.md) | Standard library API |
| [GETTING_STARTED.md](GETTING_STARTED.md) | Tutorial for beginners |
| [FLOW_GUIDE.md](FLOW_GUIDE.md) | Complete toolchain flow |

---

## 💡 Examples

### Hello World
```algo
func main() -> int {
    print("Hello, World!");
    return 0;
}
```

### Variables and Math
```algo
func main() -> int {
    let a = 10;
    let b = 20;
    let sum = a + b;
    
    print("Sum: ");
    print(sum);
    return 0;
}
```

### Conditionals
```algo
func main() -> int {
    let age = 18;
    
    if (age >= 18) {
        print("Adult");
    } else {
        print("Minor");
    }
    
    return 0;
}
```

### Loops
```algo
func main() -> int {
    for (let i = 1; i <= 10; i = i + 1) {
        print(i);
    }
    return 0;
}
```

### Functions
```algo
func factorial(n: int) -> int {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

func main() -> int {
    let result = factorial(5);
    print("5! = ");
    print(result);  // Output: 120
    return 0;
}
```

**📁 More examples in [examples/algo/](examples/algo/)**

---

## 🔨 Building

### Build All Components
```bash
./build.sh
```

### Build Individual Components

```bash
# Emulator
cd emulator
make
./a1m-emu program.bin

# Assembler
cd assembler
make
./a1m-asm source.asm output.bin

# Compiler
cd compiler
make
./algo-compiler source.algo output.asm

# Console IDE
cd gui-console
make
./a1m-console
```

### Clean Build
```bash
make clean    # In each component directory
# or
./build.sh clean
```

---

## 📖 Usage

### Console IDE (Recommended)
├── assembler/             # A1M assembler
│   ├── src/               # Assembler source
│   └── Makefile
├── compiler/              # Algo language compiler
│   ├── src/               # Compiler source
│   ├── include/           # Headers
│   └── Makefile
├── gui/                   # GUI emulator
│   ├── src/               # GUI source
│   └── Makefile
├── examples/              # Example programs
│   ├── asm/               # Assembly examples
│   └── algo/              # Algo examples
└── tests/                 # Test suite
```

## Quick Start

### Build the Emulator
```bash
cd emulator
make
./a1m-emu
```

### Build the Assembler
```bash
cd assembler
make
./a1m-asm input.asm -o output.bin
```

### Build the Compiler
```bash
cd compiler
make
./algo-compiler program.algo -o program.asm
```

### Build the GUI
```bash
cd gui
make
./a1m-gui
```

## A1M CPU Architecture

- **Data Width**: 64-bit
- **Registers**: 32 general-purpose registers (R0-R31)
- **Special Registers**: PC, SP, FLAGS, LR
- **Memory**: 64-bit addressing, byte-addressable
- **Instruction Format**: Fixed 32-bit instructions
- **Pipeline**: 5-stage (Fetch, Decode, Execute, Memory, Writeback)

## Instruction Set

The A1M ISA includes:
- Arithmetic: ADD, SUB, MUL, DIV, MOD
- Logical: AND, OR, XOR, NOT, SHL, SHR
- Memory: LOAD, STORE, PUSH, POP
- Control: JMP, JZ, JNZ, CALL, RET
- Comparison: CMP, TEST
- Special: NOP, HALT, SYSCALL

## Algo Language

Algo is a high-level, C-like language that compiles to A1M assembly:

```algo
func fibonacci(n: int) -> int {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

func main() -> int {
    let result = fibonacci(10);
    print(result);
    return 0;
}
```

## License

MIT License - See LICENSE file for details

## Author

Created as a comprehensive CPU design and implementation project.
