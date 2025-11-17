# A1M 64-bit Custom CPU Project

<div align="center">

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![Language](https://img.shields.io/badge/language-Algo-orange.svg)]()
[![CPU](https://img.shields.io/badge/CPU-64--bit%20RISC-red.svg)]()
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)]()
[![Version](https://img.shields.io/badge/version-1.5.0-green.svg)]()

**A complete custom 64-bit RISC CPU architecture with Verilog hardware implementation, software emulator, assembler, Algo programming language, compiler, and interactive console IDE.**

*Developed by **Algo Science Lab***  
*International Islamic University Chittagong (IIUC)*  
*Kumira, Chittagong, Bangladesh*

**Cross-Platform Support**: Linux • macOS • Windows (MSYS2/MinGW64)

[🚀 Quick Start](#-quick-start) • [📚 Documentation](#-documentation) • [💡 Examples](#-examples) • [🔨 Building](#-building) • [🎓 About](#-about-algo-science-lab)

</div>

---

## 📑 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Architecture](#️-architecture)
- [Quick Start](#-quick-start)
- [Documentation](#-documentation)
- [Examples](#-examples)
- [Building](#-building)
- [Usage](#-usage)
- [VS Code Extension](#-vs-code-extension)
- [Contributing](#-contributing)
- [About Algo Science Lab](#-about-algo-science-lab)
- [License](#-license)
- [Authors & Acknowledgments](#-authors--acknowledgments)

---

## 🎯 Overview

The **A1M CPU Project** is a comprehensive educational and research platform that demonstrates the complete stack of modern computing systems—from transistor-level hardware design to high-level programming languages. Developed at **Algo Science Lab, International Islamic University Chittagong (IIUC)**, this project serves as both a teaching tool and a research platform for computer architecture and compiler design.

### What is A1M?

**A1M (Algo Machine)** is a fully functional 64-bit RISC processor with:
- Complete **Verilog HDL implementation** for FPGA deployment
- Cycle-accurate **software emulator** for development and testing
- Full **toolchain** (compiler, assembler, emulator)
- High-level **Algo programming language** with C-like syntax
- Interactive **console IDE** with colorful output and animations
- **VS Code extension** with syntax highlighting and IntelliSense

### Toolchain Flow

```
┌─────────────────────────────────────────────────────────────┐
│                     A1M TOOLCHAIN FLOW                      │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Algo Source Code (.algo)                                   │
│         ↓                                                   │
│  Algo Compiler (algo-compiler)                              │
│    • Lexical Analysis                                       │
│    • Syntax Parsing                                         │
│    • Semantic Analysis                                      │
│    • Code Generation                                        │
│         ↓                                                   │
│  A1M Assembly (.asm)                                        │
│         ↓                                                   │
│  A1M Assembler (a1m-asm)                                    │
│    • Instruction Encoding                                   │
│    • Label Resolution                                       │
│    • Binary Generation                                      │
│         ↓                                                   │
│  Machine Code (.bin)                                        │
│         ↓                                                   │
│  ┌────────────────────┬────────────────────┐                │
│  │   Software Path    │   Hardware Path    │                │
│  ├────────────────────┼────────────────────┤                │
│  │  A1M Emulator      │  Verilog CPU       │                │
│  │  (a1m-emu)         │  (FPGA/Simulation) │                │ 
│  └────────────────────┴────────────────────┘                │
│         ↓                       ↓                           │
│  Program Execution & Output                                 │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Educational Value

This project is designed to teach:
- **Computer Architecture**: RISC principles, pipelining, instruction encoding
- **Digital Logic**: Verilog HDL, FPGA design, hardware synthesis
- **Compiler Design**: Lexical analysis, parsing, code generation, optimization
- **Assembly Language**: Low-level programming, instruction sets
- **System Programming**: Emulators, virtual machines, binary formats
- **Software Engineering**: Cross-platform development, build systems, toolchains

---

## ✨ Features

### 🔧 Hardware Components

- ✅ **64-bit RISC Architecture** - Clean, modern instruction set design
- ✅ **32 General Purpose Registers** (R0-R31) - Extensive register file for optimization
- ✅ **64-bit Address Space** - Support for large memory configurations
- ✅ **Verilog HDL Implementation** - Complete, synthesizable FPGA-ready code
- ✅ **5-Stage Pipeline** - Fetch → Decode → Execute → Memory → Writeback
- ✅ **32-bit Fixed Instruction Format** - Simplified decoding and pipelining
- ✅ **Harvard Architecture** - Separate instruction and data memory
- ✅ **Configurable Clock** - Flexible timing for different FPGA platforms

### 💻 Software Toolchain

- ✅ **High-Performance Emulator** - Fast, cycle-accurate CPU simulation in C
- ✅ **Full-Featured Assembler** - Complete A1M assembly language support with macros
- ✅ **Optimizing Compiler** - Multi-pass Algo compiler with constant folding
- ✅ **Interactive Console IDE** - Beautiful colorful terminal interface with animations
- ✅ **Standard Library** - I/O functions, math operations, string handling
- ✅ **Debugger Support** - Step-through execution, breakpoints, register inspection
- ✅ **Cross-Platform** - Runs on Linux, macOS, and Windows (MSYS2)
- ✅ **VS Code Extension** - Professional IDE integration with IntelliSense

### 🎨 Algo Programming Language

- ✅ **Modern C-like Syntax** - Clean, readable, familiar to C/C++ developers
- ✅ **Strong Static Typing** - `int`, `float`, `double`, `string`, `bool`, `char`
- ✅ **First-Class Functions** - Function declarations with return types and parameters
- ✅ **Advanced Control Flow** - `if`/`else`, `while`, `for`, `do-while`, `switch`/`case`, `goto`
- ✅ **Rich Operator Set** - Arithmetic, logical, bitwise, `++`/`--`, compound assignments, ternary
- ✅ **Floating-Point Arithmetic** - Scaled integer representation with 3 decimal precision
- ✅ **Standard I/O Functions** - `print()`, `printInt()`, `printFloat()`, `input()`
- ✅ **Enumerations** - Compile-time constant definitions
- ✅ **Structures** - Composite data types
- ✅ **Arrays** - Fixed-size array support
- ✅ **Type Inference** - Automatic type deduction in variable declarations

### 🛠️ Development Tools

- ✅ **Syntax Highlighting** - Color-coded source code in console and VS Code
- ✅ **Real-time Error Detection** - Immediate feedback on syntax and semantic errors
- ✅ **Code Completion** - IntelliSense in VS Code extension
- ✅ **Build Automation** - Makefile-based build system for all components
- ✅ **Installation Scripts** - One-command global installation (`./install.sh`)
- ✅ **Quick Run Script** - Instant compile-assemble-run with `./algo-run.sh`
- ✅ **Documentation** - Comprehensive guides and API references

---

## 🏗️ Architecture

### CPU Specifications

| Component | Specification | Details |
|-----------|---------------|---------|
| **Architecture** | 64-bit RISC | Reduced Instruction Set Computing |
| **Data Width** | 64 bits | Full 64-bit data path |
| **Word Size** | 64 bits | Native 64-bit operations |
| **Registers** | 32 × 64-bit GPRs | R0-R31 general purpose registers |
| **Special Registers** | PC, SP, FLAGS, R31 (LR) | Program Counter, Stack Pointer, Flags, Link Register |
| **Instruction Size** | 32 bits (fixed) | Simplified fetch and decode |
| **Memory** | 64-bit addressing | Byte-addressable memory |
| **Address Space** | 64-bit (16 exabytes) | Theoretical maximum |
| **Emulator Memory** | 64MB (configurable) | Default emulation size |
| **Pipeline Stages** | 5 stages | Fetch, Decode, Execute, Memory, Writeback |
| **Clock** | Configurable | FPGA-dependent timing |
| **Endianness** | Little-endian | Standard byte ordering |

### Register File

| Register | Purpose | Usage |
|----------|---------|-------|
| **R0** | Zero register | Always reads as 0, writes ignored |
| **R1-R30** | General purpose | Free for programmer use |
| **R31** | Link register (LR) | Stores return address for function calls |
| **PC** | Program counter | Current instruction address |
| **SP** | Stack pointer | Top of stack address |
| **FLAGS** | Status flags | Zero, Carry, Overflow, Negative flags |

### Instruction Set Architecture (ISA)

#### Arithmetic Instructions
- **ADD** - Addition (Rd = Rs1 + Rs2)
- **SUB** - Subtraction (Rd = Rs1 - Rs2)
- **MUL** - Multiplication (Rd = Rs1 × Rs2)
- **DIV** - Division (Rd = Rs1 ÷ Rs2)
- **MOD** - Modulo (Rd = Rs1 % Rs2)
- **ADDI** - Add immediate (Rd = Rs + imm)

#### Logical Instructions
- **AND** - Bitwise AND
- **OR** - Bitwise OR
- **XOR** - Bitwise XOR
- **NOT** - Bitwise NOT (one's complement)

#### Shift Instructions
- **SHL** - Shift left logical
- **SHR** - Shift right logical
- **SAR** - Shift arithmetic right (sign-extend)

#### Memory Instructions
- **LOAD** - Load from memory (Rd = [Rs + offset])
- **STORE** - Store to memory ([Rd + offset] = Rs)
- **PUSH** - Push to stack
- **POP** - Pop from stack

#### Control Flow Instructions
- **JMP** - Unconditional jump
- **JZ** - Jump if zero
- **JNZ** - Jump if not zero
- **JLT** - Jump if less than
- **JGT** - Jump if greater than
- **JLE** - Jump if less than or equal
- **JGE** - Jump if greater than or equal
- **CALL** - Function call (saves PC to R31)
- **RET** - Return from function (jumps to R31)
- **JR** - Jump to register

#### System Instructions
- **SYSCALL** - System call interface
- **HALT** - Stop execution
- **NOP** - No operation

#### Immediate Instructions
- **MOVI** - Move immediate (14-bit signed)
- **LUI** - Load upper immediate (bits 50-63)

### Instruction Encoding Format

```
┌────────────────────────────────────────────────┐
│           32-bit Instruction Word              │
├───────────┬──────────┬──────────┬──────────────┤
│  Opcode   │   Rd     │   Rs1    │  Rs2/Imm14   │
│  8 bits   │  5 bits  │  5 bits  │   14 bits    │
└───────────┴──────────┴──────────┴──────────────┘
     31-24      23-19      18-14       13-0

R-Format: Register operations
I-Format: Immediate operations  
J-Format: Jump operations (24-bit address)
```

**📖 Complete ISA documentation**: See [docs/ISA.md](docs/ISA.md)

### Memory Architecture

```
┌────────────────────────────────────┐
│     64-bit Address Space           │
├────────────────────────────────────┤
│  0x0000000000000000                │
│  ┌─────────────────────────────┐   │
│  │   Code Segment (.text)      │   │ ← Program instructions
│  │   Start: 0x1000             │   │
│  └─────────────────────────────┘   │
│  ┌─────────────────────────────┐   │
│  │   Data Segment (.data)      │   │ ← Initialized data
│  └─────────────────────────────┘   │
│  ┌─────────────────────────────┐   │
│  │   BSS Segment (.bss)        │   │ ← Uninitialized data
│  └─────────────────────────────┘   │
│  ┌─────────────────────────────┐   │
│  │   Heap (↓ grows down)       │   │ ← Dynamic allocation
│  └─────────────────────────────┘   │
│           ...                      │
│  ┌─────────────────────────────┐   │
│  │   Stack (↑ grows up)        │   │ ← Function calls, locals
│  │   Top: 0xFFFFFFFF           │   │
│  └─────────────────────────────┘   │
│  0xFFFFFFFFFFFFFFFF                │
└────────────────────────────────────┘
```

### Pipeline Stages

1. **Fetch (IF)** - Fetch instruction from memory at PC address
2. **Decode (ID)** - Decode instruction, read registers
3. **Execute (EX)** - Perform ALU operation or address calculation
4. **Memory (MEM)** - Access data memory for loads/stores
5. **Writeback (WB)** - Write result back to register file

### Floating-Point Implementation

The A1M uses **scaled integer arithmetic** for floating-point operations:

- **Representation**: Integer × 1000 (scale factor)
- **Precision**: 3 decimal places (0.001 or 10⁻³)
- **Range**: ±9.22 × 10¹⁵
- **Operations**: 
  - Addition/Subtraction: Direct integer operations
  - Multiplication: Result ÷ 1000
  - Division: Dividend × 1000 before division

Example: `3.14` → stored as `3140`

---

## 🚀 Quick Start

### Prerequisites

#### Required Tools
```bash
# C Compiler
gcc (version 7.0+)

# Build System
make

# Shell
bash (Linux/macOS) or MSYS2/MinGW64 (Windows)
```

#### Optional Tools (for Hardware)
```bash
# Verilog Simulation
iverilog (Icarus Verilog)
gtkwave (waveform viewer)

# FPGA Synthesis
Xilinx Vivado / Intel Quartus / Lattice Diamond
```

### Installation

#### Option 1: Global Installation (Recommended)

Install all tools system-wide to `/usr/local/bin`:

```bash
# Clone the repository
git clone https://github.com/algoscienceacademy/A1MCPU.git
cd A1MCPU

# Global installation (requires sudo on Linux/macOS)
sudo ./install.sh

# Verify installation
algo-compiler --version
a1m-asm --version
a1m-emu --version
a1m-console --version
```

#### Option 2: Local Build

Build tools locally without system installation:

```bash
# Clone repository
git clone https://github.com/algoscienceacademy/A1MCPU.git
cd A1MCPU

# Build all components
./build.sh

# Tools will be in their respective directories:
# - compiler/algo-compiler
# - assembler/a1m-asm
# - emulator/a1m-emu
# - gui-console/a1m-console
```

#### Option 3: Build Individual Components

```bash
# Compiler
cd compiler && make && cd ..

# Assembler
cd assembler && make && cd ..

# Emulator
cd emulator && make && cd ..

# Console IDE
cd gui-console && make && cd ..
```

### Your First Algo Program

#### Step 1: Create a Program

Create a file named `hello.algo`:

```algo
// My first Algo program
func main() -> void {
    print("Hello from A1M CPU!\n");
    print("Developed by Algo Science Lab, IIUC\n");
}
```

#### Step 2: Run It

**Using the Quick Run Script** (easiest):
```bash
./algo-run.sh hello.algo
```

**Using the Interactive Console**:
```bash
./console.sh hello.algo
```

**Manual Compilation** (step-by-step):
```bash
# Compile to assembly
algo-compiler hello.algo -o hello.asm

# Assemble to binary
a1m-asm hello.asm -o hello.bin

# Run in emulator
a1m-emu hello.bin
```

#### Step 3: See the Output

```
Hello from A1M CPU!
Developed by Algo Science Lab, IIUC
```

### More Examples

#### Variables and Arithmetic
```algo
func main() -> void {
    let a: int = 15;
    let b: int = 7;
    
    let sum: int = a + b;
    let diff: int = a - b;
    let prod: int = a * b;
    let quot: int = a / b;
    
    print("Sum: ");
    printInt(sum);
    print("\n");
}
```

#### Floating-Point Numbers
```algo
func main() -> void {
    let pi: float = 3.14159f;
    let radius: float = 5.0f;
    let area: float = pi * radius * radius;
    
    print("Circle area: ");
    printFloat(area);
    print("\n");
}
```

#### Functions and Recursion
```algo
func fibonacci(n: int) -> int {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

func main() -> void {
    let result: int = fibonacci(10);
    print("Fibonacci(10) = ");
    printInt(result);
    print("\n");
}
```

### Uninstallation

To remove globally installed tools:

```bash
sudo ./uninstall.sh
```

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

### Supported Platforms

- **Linux** (Ubuntu, Debian, Arch, Fedora, etc.)
- **macOS** (10.15+, Intel & Apple Silicon)
- **Windows** (via MSYS2/MinGW64)

📚 **Detailed Build Guide**: See [BUILD_GUIDE.md](BUILD_GUIDE.md)

### Quick Build

#### Linux
```bash
./build.sh
```

#### macOS
```bash
chmod +x build-macos.sh
./build-macos.sh
```

#### Windows (MSYS2 MinGW64 Terminal)
```bash
./build-windows.bat
# Or use: ./build.sh
```

### Build Individual Components

All platforms can use these commands:

```bash
# Compiler
cd compiler
make
cd ..

# Assembler
cd assembler
make
cd ..

# Emulator
cd emulator
make
cd ..

# Console IDE
cd gui-console
make
cd ..
```

### Platform Detection
```bash
# See what platform was detected
cd compiler
make info
```

### Clean Build
```bash
make clean    # In each component directory
# or
./build.sh clean
```

---

## 📖 Usage

### Using the Interactive Console IDE

The colorful console IDE provides the easiest way to develop Algo programs:

```bash
# Launch console with a file
./console.sh myprogram.algo

# Or launch without a file (enter code interactively)
./console.sh
```

**Features:**
- 🎨 Colorful syntax highlighting
- ⚡ Auto-compilation on save
- 📊 Real-time error messages
- 🔍 Step-by-step execution view
- 📝 Built-in code editor

### Using Individual Tools

#### Compiler Only
```bash
algo-compiler program.algo -o program.asm
```

#### Assembler Only
```bash
a1m-asm program.asm -o program.bin
```

#### Emulator Only
```bash
a1m-emu program.bin
```

### Command-Line Options

```bash
# Compiler options
algo-compiler input.algo -o output.asm    # Specify output file
algo-compiler input.algo --verbose        # Verbose output
algo-compiler input.algo --debug          # Debug symbols

# Assembler options
a1m-asm input.asm -o output.bin          # Specify output file
a1m-asm input.asm --list listing.lst     # Generate listing file

# Emulator options
a1m-emu input.bin                        # Run program
a1m-emu input.bin --debug                # Debug mode
a1m-emu input.bin --trace                # Instruction trace
a1m-emu input.bin --limit 10000          # Execution limit
```

---

## 🎨 VS Code Extension

### Installation

The Algo Language extension provides professional IDE support in Visual Studio Code:

```bash
# Navigate to extension directory
cd vsextension

# Build and install
./install-extension.sh

# Or install manually
npm install
npm run compile
code --install-extension algo-language-1.5.0.vsix
```

### Features

- ✨ **Syntax Highlighting** - Color-coded keywords, types, operators
- 🔍 **Real-time Diagnostics** - Instant error detection as you type
- 💡 **IntelliSense** - Smart code completion and suggestions
- ▶️ **Run Button** - One-click program execution from `func main()`
- 📚 **Hover Documentation** - Type information and function signatures
- 🎯 **Go to Definition** - Navigate to function declarations
- 🔧 **Build Tasks** - Integrated compile, assemble, and run commands

### Usage in VS Code

1. Open any `.algo` file
2. Enjoy syntax highlighting automatically
3. Save to see real-time error diagnostics
4. Click the **▶ Run** button above `func main()` to execute
5. View output in the **Algo** output channel

**Configuration** (File > Preferences > Settings):
```json
{
  "algo.compilerPath": "algo-compiler",
  "algo.assemblerPath": "a1m-asm",
  "algo.emulatorPath": "a1m-emu",
  "algo.enableDiagnostics": true
}
```

---

## 🤝 Contributing

We welcome contributions from the community! Whether you're fixing bugs, adding features, improving documentation, or suggesting new ideas:

### How to Contribute

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Make** your changes
4. **Test** thoroughly on multiple platforms
5. **Commit** with clear messages (`git commit -m 'Add amazing feature'`)
6. **Push** to your branch (`git push origin feature/amazing-feature`)
7. **Open** a Pull Request with detailed description

### Development Guidelines

- Follow existing code style and conventions
- Add comments for complex logic
- Update documentation for new features
- Test on Linux, macOS, and Windows when possible
- Include example programs for new language features

### Areas for Contribution

- 🐛 **Bug Fixes** - Fix issues reported on GitHub
- ✨ **New Features** - Implement new Algo language features
- 📚 **Documentation** - Improve guides and tutorials
- 🎨 **VS Code Extension** - Enhance IDE integration
- 🔧 **Optimization** - Improve compiler and emulator performance
- 🧪 **Testing** - Add test cases and examples
- 🌍 **Platform Support** - Test and fix platform-specific issues

---

## 🎓 About Algo Science Lab

### Our Mission

**Algo Science Lab** is a research and educational initiative at the **International Islamic University Chittagong (IIUC)**, dedicated to advancing computer science education through hands-on learning and innovative research projects.

### What We Do

- 🔬 **Research & Development** - Cutting-edge computer architecture and compiler design
- 📚 **Education** - Creating accessible tools for learning system programming
- 🛠️ **Open Source** - Building free, high-quality educational software
- 🌟 **Innovation** - Exploring new approaches to processor design and language implementation

### The A1M Project

The A1M CPU is our flagship educational project, designed to provide students with:

1. **Complete System Understanding** - From transistors to applications
2. **Hands-on Learning** - Build, modify, and experiment with real hardware
3. **Modern Tools** - Professional development environment and IDE
4. **Research Platform** - Base for architecture and compiler research
5. **Career Preparation** - Skills directly applicable to industry

### Academic Context

This project supports courses in:
- Computer Architecture (CSE-3xx)
- Compiler Design (CSE-4xx)
- Digital Logic Design (EEE-2xx)
- System Programming (CSE-3xx)
- FPGA Design and HDL (EEE-4xx)

### Institution

**International Islamic University Chittagong (IIUC)**  
Department of Electrical & Electronics Engineering  
Kumira, Chittagong-4318  
Bangladesh

🌐 **Website**: [www.iiuc.ac.bd](https://www.iiuc.ac.bd)  
📧 **Contact**: sshahrearhossain@gmail.com 
📍 **Location**: Kumira, Chittagong, Bangladesh

 

---

## 📄 License

**MIT License**

Copyright (c) 2025 Algo Science Lab, International Islamic University Chittagong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## 👥 Authors & Acknowledgments

### Development Team

**Lead Developer & Architect:**
- **Shahrear Hossain Shawon** - System Design, Compiler, Emulator, Verilog Implementation
  - GitHub: [@algoscienceacademy](https://github.com/algoscienceacademy)
 

**Research Group:**
- **Algo Science Lab** - Research & Development
- **IIUC EEE Department** - Academic Support

### Special Thanks

- **IIUC Faculty** - For providing research facilities and guidance
- **EEE Students** - For testing and valuable feedback
- **Open Source Community** - For tools and libraries used in this project

### Acknowledgments

This project uses and builds upon:
- **GCC** - GNU Compiler Collection
- **Make** - GNU Build System
- **Icarus Verilog** - Verilog simulation
- **VS Code API** - Extension development framework

### Contact & Support

- 📧 **Email**: sshahrearhossain@gmail.com
- 🐛 **Issues**: [GitHub Issues](https://github.com/algoscienceacademy/A1MCPU/issues)
- 💬 **Discussions**: [GitHub Discussions](https://github.com/algoscienceacademy/A1MCPU/discussions)
- 📚 **Documentation**: [Project Wiki](https://github.com/algoscienceacademy/A1MCPU/wiki)

---

<div align="center">

### 🌟 Support the Project

If you find this project useful, please ⭐ star the repository!

**Made with ❤️ by Algo Science Lab**  
*International Islamic University Chittagong*

[🏠 Home](https://github.com/algoscienceacademy/A1MCPU) • [📖 Docs](docs/) • [💡 Examples](examples/) • [🐛 Issues](https://github.com/algoscienceacademy/A1MCPU/issues) • [🤝 Contribute](#-contributing)

---

*Empowering the next generation of computer scientists through innovative education*

</div>
