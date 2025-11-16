# Algo Language Support for VS Code

<div align="center">

![Algo Language](https://img.shields.io/badge/Language-Algo-blue.svg)
![Platform](https://img.shields.io/badge/Platform-A1M%20CPU-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)
![Version](https://img.shields.io/badge/Version-1.5.0-orange.svg)

**Professional language support for the A1M Algo programming language**

*Developed by Algo Science Lab*  
*International Islamic University Chittagong (IIUC)*  
*Kumira, Chittagong, Bangladesh*

</div>

---

## 📖 About

This extension provides comprehensive development tools for **Algo**, a modern C-like programming language designed for the **A1M 64-bit RISC processor architecture**. Developed as part of cutting-edge research in computer architecture and compiler design at **Algo Science Lab, IIUC**, this extension delivers a professional development experience with real-time diagnostics, intelligent code completion, and seamless execution integration.

The A1M processor and Algo language serve as educational and research platforms for studying:
- Custom processor architecture design
- Compiler construction and optimization
- Instruction set architecture (ISA) principles
- Floating-point arithmetic implementation
- System-level programming concepts

## ✨ Features

### 🎨 Syntax Highlighting
- Keywords: `func`, `let`, `if`, `else`, `while`, `for`, `return`, `enum`, `struct`, etc.
- Types: `void`, `int`, `char`, `bool`, `float`, `double`, `i64`, `u64`
- Floating-point literals: `3.14f`, `2.718`, `1.23e10f`, `4.56e-5`
- Operators, strings, numbers, and comments
- Preprocessor directives (`#include`)

### 🔍 Real-time Error Detection
- Compile-on-save for instant error feedback
- Real-time diagnostics as you type
- Error messages displayed inline with red squiggles

### 💡 IntelliSense & Code Completion
- Keyword completion
- Type suggestions
- Built-in function completion (`print`, `printInt`, `exit`)
- Function and main templates
- Hover documentation

### ▶️ Run Button
- Click the **▶ Run** button above `func main()` to execute your program
- Automatically compiles, assembles, and runs
- Output displayed in the **Algo** output channel

### 🛠️ Build Commands
- **Run Algo Program**: Compile, assemble, and execute
- **Compile Algo Program**: Just compile and assemble

## Requirements

This extension requires the A1M toolchain:
- `compiler/algo-compiler` - Algo compiler
- `assembler/a1m-asm` - A1M assembler
- `emulator/a1m-emu` - A1M emulator

## Extension Settings

Configure paths in VS Code settings:

* `algo.compilerPath`: Path to algo-compiler (default: `compiler/algo-compiler`)
* `algo.assemblerPath`: Path to a1m-asm (default: `assembler/a1m-asm`)
* `algo.emulatorPath`: Path to a1m-emu (default: `emulator/a1m-emu`)

## Usage

1. Open or create a `.algo` file
2. Write your Algo code
3. Click the **▶ Run** button above `func main()` or use Command Palette: `Run Algo Program`
4. View output in the **Algo** output channel

### Example

```algo
func main() -> void {
    print("Hello, Algo!\n");
    
    let x: int = 42;
    let pi: float = 3.14159f;
    let e: double = 2.718281828459045;
    
    print("Integer: ");
    print(x);
    print("\n");
}
```

### 🎨 Advanced Syntax Highlighting
- **Keywords**: `func`, `let`, `if`, `else`, `while`, `for`, `return`, `enum`, `struct`, `switch`, `case`, `break`, `continue`
- **Data Types**: `void`, `int`, `char`, `bool`, `float`, `double`, `i64`, `u64`, `string`
- **Floating-point Literals**: 
  - Standard notation: `3.14f`, `2.718`, `0.001`
  - Scientific notation: `1.23e10f`, `4.56e-5`, `6.022e23`
  - Type suffixes: `f`/`F` (float), `d`/`D` (double)
- **Operators**: Arithmetic (`+`, `-`, `*`, `/`, `%`), logical (`&&`, `||`, `!`), bitwise (`&`, `|`, `^`, `~`, `<<`, `>>`)
- **Preprocessor Directives**: `#include`, `#define`, `#ifdef`
- **String Literals** and **Comments** (single-line `//`, multi-line `/* */`)

### 🔍 Real-time Intelligent Diagnostics
- **Compile-on-save**: Instant error detection when you save your file
- **Live Diagnostics**: Real-time syntax and semantic error checking
- **Inline Error Display**: Error messages with red squiggles directly in the editor
- **Error Navigation**: Click errors in the Problems panel to jump to the issue
- **Detailed Messages**: Comprehensive error descriptions from the Algo compiler

### 💡 IntelliSense & Smart Code Completion
- **Context-aware Keyword Completion**: Intelligent suggestions based on cursor position
- **Type System Support**: Auto-completion for all built-in and custom types
- **Built-in Function Library**:
  - `print(string)` - Output text to console
  - `printInt(int)` - Print integer values
  - `printFloat(float)` - Print floating-point numbers with decimal precision
  - `exit(int)` - Terminate program execution
- **Code Templates**:
  - `func` - Function declaration template
  - `main` - Main function boilerplate
  - `if`, `while`, `for` - Control flow templates
- **Hover Documentation**: View type information and function signatures on hover

### ▶️ Integrated Run System
- **One-Click Execution**: Click the **▶ Run** button above `func main()` to execute instantly
- **Automated Build Pipeline**: Automatically compiles → assembles → executes your program
- **Dedicated Output Channel**: View program output in the **Algo** output panel
- **Build Commands** via Command Palette:
  - `Algo: Run Program` (Ctrl+Shift+R) - Full compilation and execution
  - `Algo: Compile Program` (Ctrl+Shift+B) - Compile and assemble only
  - `Algo: Clean Build` - Remove generated files

### 🛠️ Advanced Editor Features
- **Code Folding**: Collapse functions, control structures, and comment blocks
- **Bracket Matching**: Automatic matching and highlighting of braces, parentheses, brackets
- **Auto-indentation**: Smart indentation based on language context
- **Comment Toggling**: Quickly comment/uncomment lines with Ctrl+/
- **Symbol Navigation**: Jump to function definitions and declarations

## 📋 Requirements

### A1M Toolchain Components

This extension requires the complete **A1M CPU Toolchain** to be installed:

1. **Algo Compiler** (`algo-compiler`)
   - Translates Algo source code to A1M assembly
   - Performs type checking and semantic analysis
   - Generates optimized assembly code

2. **A1M Assembler** (`a1m-asm`)
   - Converts assembly to binary machine code
   - Handles instruction encoding and linking
   - Produces executable binaries

3. **A1M Emulator** (`a1m-emu`)
   - Cycle-accurate processor simulation
   - Executes A1M binary programs
   - Provides I/O and system call interface

### Installation

#### Global Installation (Recommended)
```bash
cd /path/to/A1MCPU
sudo ./install.sh
```

This installs all toolchain components to `/usr/local/bin`.

#### Manual Build
```bash
# Build compiler
cd compiler && make && sudo make install

# Build assembler
cd ../assembler && make && sudo make install

# Build emulator
cd ../emulator && make && sudo make install
```

### System Requirements
- **Operating System**: Linux, macOS, or Windows (MSYS2/MinGW64)
- **VS Code**: Version 1.60.0 or higher
- **GCC**: Version 7.0 or higher (for building toolchain)
- **Disk Space**: ~50 MB for toolchain and extension

## ⚙️ Extension Settings

Configure the extension through VS Code settings (`File > Preferences > Settings`):

### Toolchain Paths
```json
{
  "algo.compilerPath": "algo-compiler",
  "algo.assemblerPath": "a1m-asm",
  "algo.emulatorPath": "a1m-emu"
}
```

**Note**: If installed globally via `install.sh`, use just the command names. For local installations, provide full paths:
```json
{
  "algo.compilerPath": "/home/user/A1MCPU/compiler/algo-compiler",
  "algo.assemblerPath": "/home/user/A1MCPU/assembler/a1m-asm",
  "algo.emulatorPath": "/home/user/A1MCPU/emulator/a1m-emu"
}
```

### Diagnostic Settings
```json
{
  "algo.enableDiagnostics": true,
  "algo.compileOnSave": true,
  "algo.maxProblems": 100
}
```

## 🚀 Usage Guide

### Getting Started

1. **Create a new Algo file**: Create a file with `.algo` extension
2. **Write your code**: Use IntelliSense for auto-completion
3. **Save to see diagnostics**: Errors appear automatically
4. **Run your program**: Click ▶ Run button or press Ctrl+Shift+R
5. **View output**: Check the **Algo** output channel

### Example Programs

#### Hello World
```algo
func main() -> void {
    print("Hello from Algo Science Lab!\n");
    print("International Islamic University Chittagong\n");
}
```

#### Floating-Point Arithmetic
```algo
func main() -> void {
    let pi: float = 3.14159f;
    let e: double = 2.718281828459045;
    let radius: float = 5.0f;
    
    let area: float = pi * radius * radius;
    
    print("Circle area: ");
    printFloat(area);
    print("\n");
}
```

#### Control Flow and Functions
```algo
func factorial(n: int) -> int {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

func main() -> void {
    let result: int = factorial(10);
    
    print("10! = ");
    printInt(result);
    print("\n");
}
```

#### Structures and Arrays
```algo
struct Point {
    x: float;
    y: float;
}

func distance(p1: Point, p2: Point) -> float {
    let dx: float = p2.x - p1.x;
    let dy: float = p2.y - p1.y;
    return dx * dx + dy * dy;  // Squared distance
}

func main() -> void {
    let origin: Point;
    origin.x = 0.0f;
    origin.y = 0.0f;
    
    let point: Point;
    point.x = 3.0f;
    point.y = 4.0f;
    
    let dist: float = distance(origin, point);
    printFloat(dist);  // Outputs: 25.000
}
```

## 📚 Language Features

### Type System
- **Primitive Types**: `int` (64-bit), `char` (8-bit), `bool`, `float` (scaled integer), `double`
- **Sized Integers**: `i64` (signed), `u64` (unsigned)
- **Composite Types**: `struct`, arrays
- **Type Inference**: Automatic in some contexts

### Floating-Point Support
The A1M architecture implements floating-point arithmetic using **scaled integer representation**:
- **Scale Factor**: 1000 (provides 3 decimal places)
- **Precision**: 0.001 (10⁻³)
- **Range**: ±9.22 × 10¹⁵
- **Operations**: Addition, subtraction, multiplication, division

### Control Structures
- `if-else` - Conditional execution
- `while` - Pre-test loops
- `for` - Iteration with initialization, condition, increment
- `switch-case` - Multi-way branching
- `break`, `continue` - Loop control

### Functions
- Function declarations with typed parameters
- Return type specification
- Recursive function support
- Call-by-value parameter passing

## 🎓 Educational Resources

### About Algo Science Lab

**Algo Science Lab** is a research and development laboratory at the **International Islamic University Chittagong (IIUC)**, located in Kumira, Chittagong, Bangladesh. The lab focuses on:

- **Computer Architecture Research**: Custom processor design and optimization
- **Compiler Development**: Advanced compilation techniques and code generation
- **Educational Tools**: Creating accessible platforms for computer science education
- **System Programming**: Low-level software development and operating systems

### A1M Processor Architecture

The **A1M (Algo Machine)** is a 64-bit RISC processor designed for educational and research purposes:

- **Architecture**: Load-store RISC design
- **Registers**: 32 general-purpose 64-bit registers
- **Instruction Set**: 80+ instructions with 32-bit fixed encoding
- **Memory Model**: 64-bit addressing, 64MB emulated space
- **Floating-Point**: Software-based scaled integer arithmetic

### Learning Path

1. **Basic Syntax**: Start with simple programs (hello world, arithmetic)
2. **Control Flow**: Learn conditionals and loops
3. **Functions**: Master function declaration and recursion
4. **Data Structures**: Work with structs and arrays
5. **Advanced Topics**: Floating-point arithmetic, optimization

### Documentation & Support

- **Official Repository**: [github.com/algoscienceacademy/A1M_Compiler](https://github.com/algoscienceacademy/A1M_Compiler)
- **Issue Tracker**: Report bugs and request features on GitHub
- **Academic Papers**: Research publications on A1M architecture
- **Contact**: Algo Science Lab, IIUC, Kumira, Chittagong

## 📝 Release Notes

### Version 1.5.0 (Latest)
**Enhanced Professional Features:**
- ✨ Improved code completion with context awareness
- 🔧 Enhanced error diagnostics with better messages
- 📊 Added support for struct and array syntax
- 🎨 Refined syntax highlighting for all language constructs
- 📖 Updated documentation with comprehensive examples
- 🏫 Added institutional branding and academic context

### Version 1.2.0
**Float and Double Support:**
- Added `float` and `double` type keywords
- Support for floating-point literals with suffixes (`f`, `F`, `d`, `D`)
- Scientific notation support (`1.23e10`, `4.56e-5`)
- Enhanced number pattern recognition
- Full compiler integration for scaled integer representation
- `printFloat()` built-in function for decimal output

### Version 1.1.0
**Code Lens Integration:**
- Added ▶ Run button above `func main()`
- One-click program execution
- Automated compile-assemble-run pipeline

### Version 1.0.0
**Initial Release:**
- Syntax highlighting for Algo language
- Real-time error detection and diagnostics
- IntelliSense code completion
- Hover documentation
- Build system integration

## 🤝 Contributing

We welcome contributions from the community! Whether you're fixing bugs, adding features, or improving documentation:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### Development Setup
```bash
cd vsextension
npm install
npm run compile
```

Press F5 in VS Code to launch Extension Development Host for testing.

## 📄 License

**MIT License**

Copyright (c) 2025 Algo Science Lab, International Islamic University Chittagong

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## 👥 Authors & Acknowledgments

**Development Team:**
- **Shahrear Hossain Shawon** - Lead Developer
- **Lecturer Riazul Islam** - Technical Advisor
- **Algo Science Lab** - Research & Development

**Institution:**
- **International Islamic University Chittagong (IIUC)**
- Department of Computer Science & Engineering
- Kumira, Chittagong-4318, Bangladesh

**Special Thanks:**
- IIUC Faculty and Research Community
- Students who tested and provided feedback
- Open-source community for tools and libraries

---

<div align="center">

**Made with ❤️ by Algo Science Lab**

*Empowering education through innovative technology*

[🌐 Visit IIUC](https://www.iiuc.ac.bd) | [📧 Contact Us](mailto:algosciencelab@iiuc.ac.bd) | [📚 Documentation](https://github.com/algoscienceacademy/A1M_Compiler)

</div>
