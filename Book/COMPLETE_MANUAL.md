# A1M CPU Architecture and Algo Programming Language
## Complete Technical Reference Manual

**A Comprehensive Guide to RISC Architecture, Assembly Language, and Compiler Design**

---

**Author:** Shahrear Hossain Shawon  
**Institution:** International Islamic University Chittagong  
**Research Laboratory:** Algo Science Lab  
**Project:** A1M RISC CPU and Algo Compiler Toolchain  
**Version:** 1.0  
**Date:** November 2025

---

## Copyright and License

**Copyright © 2025 Shahrear Hossain Shawon**  
**International Islamic University Chittagong**  
**Algo Science Lab**

Permission is hereby granted, free of charge, to any person obtaining a copy of this documentation and associated software files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

---

## Abstract

This comprehensive technical manual presents the complete design, implementation, and operation of the A1M CPU architecture and the Algo programming language ecosystem. The A1M is a 64-bit RISC (Reduced Instruction Set Computer) processor featuring 32 general-purpose registers, a fixed 32-bit instruction encoding scheme, and a sophisticated 5-stage pipeline architecture implemented in Verilog HDL.

The project encompasses a complete computing system from hardware to high-level programming:

1. **Hardware Architecture**: Verilog HDL implementation of a RISC CPU with modular design including register file, ALU, control unit, and memory subsystem
2. **Assembly Language**: Comprehensive instruction set with 60+ operations supporting arithmetic, logical, memory, and control flow instructions
3. **High-Level Language**: Algo programming language with modern syntax, type system, and control structures
4. **Compilation Toolchain**: Full compiler implementation including lexical analysis, parsing, semantic analysis, and code generation
5. **Development Environment**: Assembler, emulator, and integrated development tools

This document serves as both a reference manual and educational resource, providing step-by-step explanations with complete code implementations, making it suitable for students, researchers, and practitioners in computer architecture and compiler design.

**Keywords:** RISC Architecture, 64-bit Processor, Verilog HDL, Assembly Language, Compiler Design, Lexical Analysis, Syntax Parsing, Code Generation, Register Allocation, Computer Architecture, Programming Language Design

---

## Table of Contents

### PART I: HARDWARE ARCHITECTURE

#### Chapter 1: Introduction to A1M Architecture
- 1.1 Overview and Design Philosophy
- 1.2 RISC vs CISC Architecture
- 1.3 Project Motivation and Goals
- 1.4 System Architecture Overview
- 1.5 Key Features and Specifications

#### Chapter 2: Register Architecture
- 2.1 Register Set Overview
- 2.2 The 32 General-Purpose Registers (R0-R31)
- 2.3 Special-Purpose Registers
- 2.4 Register Usage Conventions
- 2.5 Verilog Implementation of Register File

#### Chapter 3: Instruction Set Architecture (ISA)
- 3.1 Instruction Format Design
- 3.2 Instruction Encoding Schemes
- 3.3 Instruction Categories
- 3.4 Complete Instruction Reference
- 3.5 Opcode Assignment Table

#### Chapter 4: Arithmetic Logic Unit (ALU)
- 4.1 ALU Architecture
- 4.2 Arithmetic Operations
- 4.3 Logical Operations
- 4.4 Shift Operations
- 4.5 Flag Generation Logic
- 4.6 Verilog Implementation

#### Chapter 5: Control Unit
- 5.1 Control Signal Generation
- 5.2 Instruction Decoding Logic
- 5.3 Pipeline Control
- 5.4 Hazard Detection and Resolution
- 5.5 Verilog Implementation

#### Chapter 6: Memory Organization
- 6.1 Memory Architecture
- 6.2 Address Space Layout
- 6.3 Memory Access Instructions
- 6.4 Cache Organization (Future)
- 6.5 Verilog Memory Module

#### Chapter 7: Pipeline Architecture
- 7.1 5-Stage Pipeline Overview
- 7.2 Instruction Fetch (IF)
- 7.3 Instruction Decode (ID)
- 7.4 Execute (EX)
- 7.5 Memory Access (MEM)
- 7.6 Write Back (WB)
- 7.7 Pipeline Hazards and Solutions

### PART II: ASSEMBLY LANGUAGE

#### Chapter 8: A1M Assembly Language Fundamentals
- 8.1 Assembly Language Basics
- 8.2 Syntax and Structure
- 8.3 Assembler Directives
- 8.4 Labels and Symbols
- 8.5 Comments and Documentation

#### Chapter 9: Data Movement Instructions
- 9.1 Register-to-Register Transfers
- 9.2 Immediate Value Loading
- 9.3 Memory Load Operations
- 9.4 Memory Store Operations
- 9.5 Code Examples

#### Chapter 10: Arithmetic Instructions
- 10.1 Addition and Subtraction
- 10.2 Multiplication and Division
- 10.3 Modulo Operation
- 10.4 Immediate Arithmetic
- 10.5 Practical Examples

#### Chapter 11: Logical and Bitwise Instructions
- 11.1 AND, OR, XOR Operations
- 11.2 NOT Operation
- 11.3 Shift Operations
- 11.4 Bit Manipulation Techniques
- 11.5 Practical Applications

#### Chapter 12: Control Flow Instructions
- 12.1 Unconditional Jumps
- 12.2 Conditional Branches
- 12.3 Function Calls and Returns
- 12.4 System Calls
- 12.5 Control Flow Examples

#### Chapter 13: The Assembler Implementation
- 13.1 Assembler Architecture
- 13.2 Two-Pass Assembly Algorithm
- 13.3 Symbol Table Management
- 13.4 Instruction Encoding
- 13.5 Binary Output Generation
- 13.6 Complete C Implementation

### PART III: EMULATOR AND RUNTIME

#### Chapter 14: CPU Emulator
- 14.1 Emulator Architecture
- 14.2 Instruction Execution Cycle
- 14.3 Memory Management
- 14.4 Register State Tracking
- 14.5 System Call Interface
- 14.6 Complete Implementation

#### Chapter 15: System Calls and I/O
- 15.1 System Call Mechanism
- 15.2 I/O Operations
- 15.3 Standard Input/Output
- 15.4 File Operations
- 15.5 Implementation Details

### PART IV: ALGO PROGRAMMING LANGUAGE

#### Chapter 16: Introduction to Algo Language
- 16.1 Language Design Philosophy
- 16.2 Syntax Overview
- 16.3 Type System
- 16.4 Program Structure
- 16.5 Hello World Example

#### Chapter 17: Lexical Analysis
- 17.1 Tokenization Process
- 17.2 Token Types and Categories
- 17.3 Keyword Recognition
- 17.4 Identifier Scanning
- 17.5 Literal Processing
- 17.6 Comment Handling
- 17.7 Lexer Implementation in C

#### Chapter 18: Syntax Analysis (Parsing)
- 18.1 Grammar Definition
- 18.2 Recursive Descent Parsing
- 18.3 Expression Parsing
- 18.4 Statement Parsing
- 18.5 Abstract Syntax Tree (AST)
- 18.6 Parser Implementation

#### Chapter 19: Data Types and Variables
- 19.1 Primitive Types (int, bool, char)
- 19.2 Type Modifiers
- 19.3 Variable Declaration
- 19.4 Constants
- 19.5 Type Inference
- 19.6 sizeof Operator

#### Chapter 20: Operators and Expressions
- 20.1 Arithmetic Operators
- 20.2 Comparison Operators
- 20.3 Logical Operators
- 20.4 Bitwise Operators
- 20.5 Assignment Operators
- 20.6 Ternary Operator
- 20.7 Operator Precedence

#### Chapter 21: Control Structures
- 21.1 if-else Statements
- 21.2 while Loops
- 21.3 for Loops
- 21.4 do-while Loops
- 21.5 switch-case Statements
- 21.6 break and continue
- 21.7 goto Statements

#### Chapter 22: Functions
- 22.1 Function Declaration
- 22.2 Function Parameters
- 22.3 Return Values
- 22.4 Function Calls
- 22.5 Recursion
- 22.6 Function Examples

#### Chapter 23: Advanced Features
- 23.1 Enumerations
- 23.2 Structures (Simulated)
- 23.3 File Inclusion (#include)
- 23.4 Code Organization
- 23.5 Modular Programming

### PART V: COMPILER IMPLEMENTATION

#### Chapter 24: Compiler Architecture
- 24.1 Compilation Pipeline
- 24.2 Frontend vs Backend
- 24.3 Symbol Table Design
- 24.4 Error Handling Strategy
- 24.5 Optimization Opportunities

#### Chapter 25: Lexical Analyzer Implementation
- 25.1 Lexer Data Structures
- 25.2 State Machine Design
- 25.3 Token Generation
- 25.4 Error Recovery
- 25.5 Complete Source Code

#### Chapter 26: Parser Implementation
- 26.1 Parser Data Structures
- 26.2 AST Node Types
- 26.3 Parsing Functions
- 26.4 Expression Parsing
- 26.5 Statement Parsing
- 26.6 Error Handling
- 26.7 Complete Source Code

#### Chapter 27: Semantic Analysis
- 27.1 Symbol Table Implementation
- 27.2 Scope Management
- 27.3 Type Checking
- 27.4 Constant Evaluation
- 27.5 Semantic Error Detection

#### Chapter 28: Code Generation
- 28.1 Code Generation Strategy
- 28.2 Register Allocation Algorithm
- 28.3 Expression Code Generation
- 28.4 Statement Translation
- 28.5 Function Prologue/Epilogue
- 28.6 Complete Implementation

#### Chapter 29: Register Allocation
- 29.1 Register Allocation Strategy
- 29.2 Register Spilling
- 29.3 Register Usage Tracking
- 29.4 Optimization Techniques
- 29.5 Implementation Details

#### Chapter 30: Function Call Convention
- 30.1 Calling Convention Design
- 30.2 Parameter Passing
- 30.3 Return Value Handling
- 30.4 Stack Management
- 30.5 Implementation

### PART VI: COMPLETE COMPILATION PROCESS

#### Chapter 31: Preprocessing
- 31.1 File Inclusion System
- 31.2 Macro Expansion (Future)
- 31.3 Conditional Compilation (Future)
- 31.4 Implementation

#### Chapter 32: Complete Compilation Flow
- 32.1 Source to Assembly
- 32.2 Assembly to Binary
- 32.3 Binary Execution
- 32.4 Step-by-Step Example
- 32.5 Compilation Scripts

#### Chapter 33: Development Tools
- 33.1 Command-Line Compiler
- 33.2 Assembler Tool
- 33.3 Emulator
- 33.4 VS Code Extension
- 33.5 Global Installation

### PART VII: PRACTICAL EXAMPLES

#### Chapter 34: Basic Programs
- 34.1 Hello World
- 34.2 Variable Operations
- 34.3 Arithmetic Calculations
- 34.4 Input/Output

#### Chapter 35: Control Flow Examples
- 35.1 Conditional Execution
- 35.2 Loop Constructs
- 35.3 Pattern Generation
- 35.4 Number Processing

#### Chapter 36: Functions and Recursion
- 36.1 Simple Functions
- 36.2 Parameter Passing
- 36.3 Factorial Calculation
- 36.4 Fibonacci Numbers
- 36.5 GCD and LCM

#### Chapter 37: Data Structures
- 37.1 Arrays (Simulated)
- 37.2 Struct Simulation
- 37.3 Enumerations
- 37.4 Complex Data Management

#### Chapter 38: Advanced Programs
- 38.1 Prime Number Checker
- 38.2 Sorting Algorithms
- 38.3 String Processing
- 38.4 Mathematical Computations

### PART VIII: TESTING AND VERIFICATION

#### Chapter 39: Testing Methodology
- 39.1 Unit Testing
- 39.2 Integration Testing
- 39.3 Test Suite Organization
- 39.4 Automated Testing Scripts

#### Chapter 40: Performance Analysis
- 40.1 Instruction Cycle Counting
- 40.2 Benchmark Programs
- 40.3 Optimization Impact
- 40.4 Performance Metrics

### APPENDICES

#### Appendix A: Complete Instruction Set Reference
#### Appendix B: Assembly Language Quick Reference
#### Appendix C: Algo Language Grammar (BNF)
#### Appendix D: System Call Reference
#### Appendix E: Error Messages Catalog
#### Appendix F: Installation and Setup Guide
#### Appendix G: Troubleshooting Guide
#### Appendix H: Source Code Repository Structure

---

# PART I: HARDWARE ARCHITECTURE

---

## Chapter 1: Introduction to A1M Architecture

### 1.1 Overview and Design Philosophy

The A1M CPU is a 64-bit RISC (Reduced Instruction Set Computer) processor designed with the following principles:

**Design Goals:**
- Simplicity: Easy to understand and implement
- Efficiency: Optimal performance with minimal hardware
- Modularity: Clean separation of functional units
- Scalability: Easy to extend and enhance

**Key Characteristics:**
- 64-bit data path
- 32 general-purpose registers
- Fixed 32-bit instruction encoding
- 5-stage pipeline architecture
- Load-store architecture
- Orthogonal instruction set

### 1.2 RISC vs CISC Architecture

**RISC (Reduced Instruction Set Computer):**
- Simple, uniform instructions
- Fixed instruction length (32 bits)
- Register-to-register operations
- Load/store memory access
- Hardware simplicity
- Pipeline-friendly design

**A1M follows RISC principles:**
```
Traditional CISC:  ADD [memory], register    // Complex, variable length
A1M RISC:         LOAD R1, [memory]         // Simple, fixed length
                  ADD R2, R2, R1
                  STORE R2, [memory]
```

### 1.3 Project Motivation and Goals

**Educational Purpose:**
- Teach computer architecture fundamentals
- Demonstrate compiler design principles
- Provide hands-on learning experience

**Technical Goals:**
- Complete toolchain from hardware to high-level language
- Verilog implementation for FPGA synthesis
- C-based software tools for portability
- Modern language features in Algo

### 1.4 System Architecture Overview

```
┌─────────────────────────────────────────────────────┐
│                  A1M CPU SYSTEM                     │
├─────────────────────────────────────────────────────┤
│                                                     │
│  ┌──────────────┐         ┌──────────────┐        │
│  │  Instruction │────────▶│   Control    │        │
│  │    Fetch     │         │     Unit     │        │
│  └──────────────┘         └──────────────┘        │
│         │                        │                 │
│         ▼                        ▼                 │
│  ┌──────────────┐         ┌──────────────┐        │
│  │   Decode     │────────▶│  Register    │        │
│  │              │         │     File     │        │
│  └──────────────┘         └──────────────┘        │
│         │                        │                 │
│         ▼                        ▼                 │
│  ┌──────────────┐         ┌──────────────┐        │
│  │   Execute    │────────▶│     ALU      │        │
│  │              │         │              │        │
│  └──────────────┘         └──────────────┘        │
│         │                        │                 │
│         ▼                        ▼                 │
│  ┌──────────────┐         ┌──────────────┐        │
│  │    Memory    │────────▶│    Memory    │        │
│  │    Access    │         │    System    │        │
│  └──────────────┘         └──────────────┘        │
│         │                                          │
│         ▼                                          │
│  ┌──────────────┐                                 │
│  │  Write Back  │                                 │
│  └──────────────┘                                 │
│                                                     │
└─────────────────────────────────────────────────────┘
```

### 1.5 Key Features and Specifications

**Processor Specifications:**
```
Architecture:        64-bit RISC
Registers:           32 × 64-bit general purpose
                     R0: Always zero
                     R1-R2: Syscall/return values
                     R3: Stack pointer
                     R4-R30: General purpose
                     R31: Link register

Instruction Format:  32-bit fixed length
Memory Addressing:   64-bit address space
Pipeline Stages:     5 (IF, ID, EX, MEM, WB)
Instruction Set:     60+ instructions
Instruction Types:   R-type, I-type, J-type, M-type
```

**Supported Operations:**
- Arithmetic: ADD, SUB, MUL, DIV, MOD
- Logical: AND, OR, XOR, NOT
- Shift: SHL, SHR, SAR
- Memory: LOAD, STORE (byte, half, word, double)
- Control: JMP, conditional branches, CALL, RET
- System: SYSCALL, HALT

---

## Chapter 2: Register Architecture

### 2.1 Register Set Overview

The A1M CPU features 32 general-purpose registers, each 64 bits wide. This provides:
- Ample register space for computations
- Reduced memory traffic
- Efficient parameter passing
- Fast context switching

**Register Naming Convention:**
```
R0  - R31    (Numeric notation)
```

### 2.2 The 32 General-Purpose Registers (R0-R31)

**Register Layout:**
```
┌─────────┬──────────────────────────────────────────────┐
│ Register│ Purpose                                      │
├─────────┼──────────────────────────────────────────────┤
│ R0      │ Always zero (hardwired)                      │
│ R1      │ Syscall argument / Return value 1            │
│ R2      │ Syscall result / Return value 2              │
│ R3      │ Stack pointer (SP)                           │
│ R4-R30  │ General purpose / Temporary registers        │
│ R31     │ Link register (return address)               │
└─────────┴──────────────────────────────────────────────┘
```

**Register Properties:**
- Width: 64 bits
- Access: Read/Write (except R0)
- Reset Value: 0x0000000000000000
- R0 Hardware: Hardwired to zero

### 2.3 Special-Purpose Registers

**R0 - Zero Register:**
```verilog
// R0 always reads as zero, writes are ignored
if (read_addr1 == 5'h0)
    read_data1 = 64'h0;
```

**R1 - Syscall Argument Register:**
- Used for passing values to system calls
- Returns integer values from syscalls

**R2 - Function Return Value:**
- Stores function return values
- Used in function calling convention

**R3 - Stack Pointer:**
- Points to top of stack
- Managed by PUSH/POP operations
- Critical for function calls

**R31 - Link Register:**
- Stores return address for CALL instruction
- Used by RET to return from functions

### 2.4 Register Usage Conventions

**Compiler Register Allocation:**
```c
// From compiler/src/codegen.c
static int allocate_register(CodeGen* gen) {
    // Use R1-R30 for temporaries (30 registers)
    // R0 = always zero
    // R1 = syscall argument/return (can be reused when not in syscall)
    // R2 = function return value (can be reused when not returning)
    // R3 = stack pointer (RESERVED - never allocated)
    // R31 = link register (managed by CALL/RET)
    
    for (int i = 1; i <= 30; i++) {
        if (i == 3) continue; // Skip R3 (stack pointer)
        if (!gen->reg_in_use[i]) {
            gen->reg_in_use[i] = true;
            return i;
        }
    }
    
    fprintf(stderr, "Error: Out of registers\n");
    exit(1);
}
```

**Function Calling Convention:**
```
Parameters:     R1, R2, R4, R5, ... (first params in R1-R2, rest in R4+)
Return Value:   R2
Preserved:      Caller-saved (none preserved across calls)
Link Register:  R31 (set by CALL, used by RET)
Stack Pointer:  R3 (maintained across calls)
```

### 2.5 Verilog Implementation of Register File

**Complete Register File Module:**
```verilog
// File: verilog/cpu/register_file.v
// A1M Register File
// 32 64-bit general purpose registers
// R0 is hardwired to zero

module register_file (
    input wire clk,                 // Clock
    input wire reset,               // Reset signal
    input wire write_enable,        // Write enable
    input wire [4:0] read_addr1,    // Read address 1
    input wire [4:0] read_addr2,    // Read address 2
    input wire [4:0] write_addr,    // Write address
    input wire [63:0] write_data,   // Write data
    output reg [63:0] read_data1,   // Read data 1
    output reg [63:0] read_data2    // Read data 2
);

// 32 64-bit registers
reg [63:0] registers [0:31];

integer i;

// Initialize registers
initial begin
    for (i = 0; i < 32; i = i + 1) begin
        registers[i] = 64'h0;
    end
end

// Write logic (synchronous)
always @(posedge clk or posedge reset) begin
    if (reset) begin
        // Reset all registers to zero
        for (i = 0; i < 32; i = i + 1) begin
            registers[i] <= 64'h0;
        end
    end else if (write_enable && write_addr != 5'h0) begin
        // R0 is hardwired to zero, cannot be written
        registers[write_addr] <= write_data;
    end
end

// Read logic (asynchronous, combinational)
always @(*) begin
    // R0 always returns zero
    if (read_addr1 == 5'h0)
        read_data1 = 64'h0;
    else
        read_data1 = registers[read_addr1];
        
    if (read_addr2 == 5'h0)
        read_data2 = 64'h0;
    else
        read_data2 = registers[read_addr2];
end

endmodule
```

**Key Implementation Details:**

1. **Dual-Port Read:** Two independent read ports for operand fetch
2. **Single-Port Write:** One write port for result writeback
3. **R0 Enforcement:** Hardware ensures R0 always reads zero
4. **Synchronous Write:** Writes occur on clock edge
5. **Asynchronous Read:** Reads are combinational for pipeline efficiency

**Usage Example:**
```verilog
// Instantiation in CPU
register_file rf (
    .clk(clk),
    .reset(reset),
    .write_enable(reg_write_enable),
    .read_addr1(rs1),
    .read_addr2(rs2),
    .write_addr(rd),
    .write_data(write_data),
    .read_data1(operand_a),
    .read_data2(operand_b)
);
```

**Register Access Timing:**
```
Clock Cycle:  0      1      2      3      4
             ┌──┐  ┌──┐  ┌──┐  ┌──┐  ┌──┐
CLK          ┘  └──┘  └──┘  └──┘  └──┘  └──

Read Addr    ──X══════════════════════X────
Read Data    ────X════════════════════X────  (Combinational)

Write Addr   ──────X══════════════════X────
Write Data   ──────X══════════════════X────
Write Enable ──────┌───────────────────┐──
Register[rd] ────────X════════════════X────  (Synchronous)
```

---

## Chapter 3: Instruction Set Architecture (ISA)

### 3.1 Instruction Format Design

The A1M ISA uses fixed 32-bit instruction encoding with four format types:

**Instruction Formats:**

```
R-Type (Register operations):
┌────────┬─────┬─────┬─────┬──────────┐
│ Opcode │ RD  │ RS1 │ RS2 │ Reserved │
│ 8 bits │5bits│5bits│5bits│  9 bits  │
└────────┴─────┴─────┴─────┴──────────┘
31    24 23  19 18 14 13  9  8       0

I-Type (Immediate operations):
┌────────┬─────┬─────┬──────────────────┐
│ Opcode │ RD  │ RS1 │    Immediate     │
│ 8 bits │5bits│5bits│     14 bits      │
└────────┴─────┴─────┴──────────────────┘
31    24 23  19 18 14 13              0

J-Type (Jump operations):
┌────────┬────────────────────────────┐
│ Opcode │      Jump Address          │
│ 8 bits │        24 bits             │
└────────┴────────────────────────────┘
31    24 23                         0

M-Type (Memory operations):
┌────────┬─────┬─────┬──────────────────┐
│ Opcode │ RD  │ Base│     Offset       │
│ 8 bits │5bits│5bits│     14 bits      │
└────────┴─────┴─────┴──────────────────┘
31    24 23  19 18 14 13              0
```

### 3.2 Instruction Encoding Schemes

**Field Descriptions:**

| Field      | Bits  | Description                           |
|------------|-------|---------------------------------------|
| Opcode     | 8     | Operation code (256 possible opcodes) |
| RD         | 5     | Destination register (0-31)           |
| RS1        | 5     | Source register 1 (0-31)              |
| RS2        | 5     | Source register 2 (0-31)              |
| Immediate  | 14    | Immediate value (-8192 to 8191)       |
| Jump Addr  | 24    | Jump address offset                   |
| Reserved   | 9     | Reserved for future use               |

**Sign Extension:**
```c
// 14-bit immediate sign extension to 64 bits
int64_t sign_extend_14(uint16_t value) {
    if (value & 0x2000) {  // Check bit 13 (sign bit)
        return (int64_t)(value | 0xFFFFFFFFFFFFC000ULL);
    }
    return (int64_t)value;
}

// 24-bit jump address sign extension
int64_t sign_extend_24(uint32_t value) {
    if (value & 0x800000) {  // Check bit 23
        return (int64_t)(value | 0xFFFFFFFFFF000000ULL);
    }
    return (int64_t)value;
}
```

### 3.3 Instruction Categories

**1. Arithmetic Instructions:**
- ADD, ADDI - Addition
- SUB, SUBI - Subtraction  
- MUL, MULI - Multiplication
- DIV, DIVI - Division
- MOD, MODI - Modulo

**2. Logical Instructions:**
- AND, ANDI - Bitwise AND
- OR, ORI - Bitwise OR
- XOR, XORI - Bitwise XOR
- NOT - Bitwise NOT

**3. Shift Instructions:**
- SHL, SHLI - Shift left logical
- SHR, SHRI - Shift right logical
- SAR, SARI - Shift right arithmetic

**4. Comparison Instructions:**
- CMP, CMPI - Compare
- TEST - Bitwise test

**5. Memory Instructions:**
- LOAD - Load doubleword
- STORE - Store doubleword
- LOADB, STOREB - Byte operations
- LOADH, STOREH - Halfword operations
- LOADW, STOREW - Word operations

**6. Control Flow Instructions:**
- JMP - Unconditional jump
- JZ, JNZ - Jump if zero/not zero
- JC, JNC - Jump if carry/not carry
- JO, JNO - Jump if overflow/not overflow
- JN - Jump if negative
- CALL - Function call
- RET - Return from function
- JR - Jump register

**7. Data Movement:**
- MOV - Register to register
- MOVI - Load immediate
- LUI - Load upper immediate
- PUSH, POP - Stack operations

**8. System Instructions:**
- SYSCALL - System call
- HALT - Stop execution
- NOP - No operation

### 3.4 Complete Instruction Reference

**Arithmetic Operations:**

```assembly
# ADD - Add two registers
ADD RD, RS1, RS2        # RD = RS1 + RS2
Encoding: 0x02 [RD] [RS1] [RS2] [0000000000]
Example:  ADD R1, R2, R3  # R1 = R2 + R3

# ADDI - Add immediate
ADDI RD, RS1, IMM       # RD = RS1 + IMM
Encoding: 0x03 [RD] [RS1] [Immediate]
Example:  ADDI R1, R2, 100  # R1 = R2 + 100

# SUB - Subtract
SUB RD, RS1, RS2        # RD = RS1 - RS2
Encoding: 0x04 [RD] [RS1] [RS2] [0000000000]
Example:  SUB R1, R2, R3  # R1 = R2 - R3

# MUL - Multiply
MUL RD, RS1, RS2        # RD = RS1 * RS2
Encoding: 0x06 [RD] [RS1] [RS2] [0000000000]
Example:  MUL R1, R2, R3  # R1 = R2 * R3

# DIV - Divide
DIV RD, RS1, RS2        # RD = RS1 / RS2
Encoding: 0x08 [RD] [RS1] [RS2] [0000000000]
Example:  DIV R1, R2, R3  # R1 = R2 / R3

# MOD - Modulo
MOD RD, RS1, RS2        # RD = RS1 % RS2
Encoding: 0x0A [RD] [RS1] [RS2] [0000000000]
Example:  MOD R1, R2, R3  # R1 = R2 % R3
```

**Logical Operations:**

```assembly
# AND - Bitwise AND
AND RD, RS1, RS2        # RD = RS1 & RS2
Encoding: 0x0C [RD] [RS1] [RS2] [0000000000]

# OR - Bitwise OR
OR RD, RS1, RS2         # RD = RS1 | RS2
Encoding: 0x0E [RD] [RS1] [RS2] [0000000000]

# XOR - Bitwise XOR
XOR RD, RS1, RS2        # RD = RS1 ^ RS2
Encoding: 0x10 [RD] [RS1] [RS2] [0000000000]

# NOT - Bitwise NOT
NOT RD, RS1             # RD = ~RS1
Encoding: 0x12 [RD] [RS1] [00000] [0000000000]
```

**Memory Operations:**

```assembly
# LOAD - Load 64-bit value from memory
LOAD RD, Offset(Base)   # RD = Memory[Base + Offset]
Encoding: 0x20 [RD] [Base] [Offset]
Example:  LOAD R1, 0(R2)  # R1 = Memory[R2 + 0]

# STORE - Store 64-bit value to memory
STORE RS, Offset(Base)  # Memory[Base + Offset] = RS
Encoding: 0x21 [RS] [Base] [Offset]
Example:  STORE R1, 0(R2)  # Memory[R2] = R1

# LOADB - Load byte (8-bit, zero-extended)
LOADB RD, Offset(Base)  # RD = (uint8_t)Memory[Base + Offset]
Encoding: 0x22 [RD] [Base] [Offset]

# STOREB - Store byte
STOREB RS, Offset(Base) # Memory[Base + Offset] = (uint8_t)RS
Encoding: 0x23 [RS] [Base] [Offset]
```

**Control Flow:**

```assembly
# JMP - Unconditional jump
JMP Label               # PC = PC + (Label << 2)
Encoding: 0x30 [Jump Address]

# JZ - Jump if zero
JZ Label                # if (ZF == 1) PC = PC + (Label << 2)
Encoding: 0x31 [Jump Address]

# CALL - Function call
CALL Label              # R31 = PC + 4; PC = PC + (Label << 2)
Encoding: 0x39 [Jump Address]

# RET - Return from function
RET                     # PC = R31
Encoding: 0x3A [000000000000000000000000]

# SYSCALL - System call
SYSCALL Num             # Invoke system call Num
Encoding: 0x50 [00000] [00000] [Syscall Number]
```

### 3.5 Opcode Assignment Table

**Complete Opcode Map:**

| Opcode | Mnemonic | Type | Description                |
|--------|----------|------|----------------------------|
| 0x00   | NOP      | R    | No operation               |
| 0x01   | HALT     | R    | Halt execution             |
| 0x02   | ADD      | R    | Add registers              |
| 0x03   | ADDI     | I    | Add immediate              |
| 0x04   | SUB      | R    | Subtract registers         |
| 0x05   | SUBI     | I    | Subtract immediate         |
| 0x06   | MUL      | R    | Multiply registers         |
| 0x07   | MULI     | I    | Multiply immediate         |
| 0x08   | DIV      | R    | Divide registers           |
| 0x09   | DIVI     | I    | Divide immediate           |
| 0x0A   | MOD      | R    | Modulo registers           |
| 0x0B   | MODI     | I    | Modulo immediate           |
| 0x0C   | AND      | R    | Bitwise AND                |
| 0x0D   | ANDI     | I    | Bitwise AND immediate      |
| 0x0E   | OR       | R    | Bitwise OR                 |
| 0x0F   | ORI      | I    | Bitwise OR immediate       |
| 0x10   | XOR      | R    | Bitwise XOR                |
| 0x11   | XORI     | I    | Bitwise XOR immediate      |
| 0x12   | NOT      | R    | Bitwise NOT                |
| 0x13   | SHL      | R    | Shift left logical         |
| 0x14   | SHLI     | I    | Shift left logical imm     |
| 0x15   | SHR      | R    | Shift right logical        |
| 0x16   | SHRI     | I    | Shift right logical imm    |
| 0x17   | SAR      | R    | Shift right arithmetic     |
| 0x18   | SARI     | I    | Shift right arithmetic imm |
| 0x19   | CMP      | R    | Compare registers          |
| 0x1A   | CMPI     | I    | Compare with immediate     |
| 0x1B   | TEST     | R    | Bitwise test               |
| 0x20   | LOAD     | M    | Load doubleword            |
| 0x21   | STORE    | M    | Store doubleword           |
| 0x22   | LOADB    | M    | Load byte                  |
| 0x23   | STOREB   | M    | Store byte                 |
| 0x24   | LOADH    | M    | Load halfword              |
| 0x25   | STOREH   | M    | Store halfword             |
| 0x26   | LOADW    | M    | Load word                  |
| 0x27   | STOREW   | M    | Store word                 |
| 0x28   | PUSH     | M    | Push to stack              |
| 0x29   | POP      | M    | Pop from stack             |
| 0x30   | JMP      | J    | Unconditional jump         |
| 0x31   | JZ       | J    | Jump if zero               |
| 0x32   | JNZ      | J    | Jump if not zero           |
| 0x33   | JC       | J    | Jump if carry              |
| 0x34   | JNC      | J    | Jump if not carry          |
| 0x35   | JO       | J    | Jump if overflow           |
| 0x36   | JNO      | J    | Jump if not overflow       |
| 0x37   | JN       | J    | Jump if negative           |
| 0x38   | JNN      | J    | Jump if not negative       |
| 0x39   | CALL     | J    | Call function              |
| 0x3A   | RET      | R    | Return from function       |
| 0x3B   | JR       | R    | Jump register              |
| 0x40   | MOV      | R    | Move register              |
| 0x41   | MOVI     | I    | Move immediate             |
| 0x42   | LUI      | I    | Load upper immediate       |
| 0x50   | SYSCALL  | I    | System call                |

---

## Chapter 4: Arithmetic Logic Unit (ALU)

### 4.1 ALU Architecture

The ALU is the computational heart of the A1M CPU, performing:
- Arithmetic operations (add, subtract, multiply, divide)
- Logical operations (and, or, xor, not)
- Shift operations (logical and arithmetic)
- Comparison operations
- Flag generation

**ALU Block Diagram:**
```
                    ┌─────────────────────┐
    Operand A ─────▶│                     │
    (64-bit)        │                     │
                    │      A1M ALU        │
    Operand B ─────▶│                     │─────▶ Result (64-bit)
    (64-bit)        │                     │
                    │                     │
    ALU Op ────────▶│                     │─────▶ Zero Flag
    (4-bit)         │                     │─────▶ Carry Flag
                    │                     │─────▶ Overflow Flag
                    └─────────────────────┘─────▶ Negative Flag
```

### 4.2 Arithmetic Operations

**Addition with Overflow Detection:**
```verilog
wire [64:0] add_result;
assign add_result = {1'b0, operand_a} + {1'b0, operand_b};

ALU_ADD: begin
    result = add_result[63:0];
    carry_flag = add_result[64];  // Bit 64 is carry out
    // Overflow occurs when:
    // - Adding two positive numbers gives negative result
    // - Adding two negative numbers gives positive result
    overflow_flag = (operand_a[63] == operand_b[63]) && 
                    (result[63] != operand_a[63]);
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
end
```

**Subtraction:**
```verilog
wire [64:0] sub_result;
assign sub_result = {1'b0, operand_a} - {1'b0, operand_b};

ALU_SUB: begin
    result = sub_result[63:0];
    carry_flag = sub_result[64];
    overflow_flag = (operand_a[63] != operand_b[63]) && 
                    (result[63] != operand_a[63]);
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
end
```

**Multiplication:**
```verilog
ALU_MUL: begin
    result = operand_a * operand_b;
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
    carry_flag = 1'b0;
    overflow_flag = 1'b0;  // Could check for overflow
end
```

**Division:**
```verilog
ALU_DIV: begin
    if (operand_b == 64'h0) begin
        result = 64'hFFFFFFFFFFFFFFFF;  // Division by zero
        overflow_flag = 1'b1;
    end else begin
        result = operand_a / operand_b;
        overflow_flag = 1'b0;
    end
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
    carry_flag = 1'b0;
end
```

### 4.3 Logical Operations

```verilog
ALU_AND: begin
    result = operand_a & operand_b;
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
    carry_flag = 1'b0;
    overflow_flag = 1'b0;
end

ALU_OR: begin
    result = operand_a | operand_b;
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
    carry_flag = 1'b0;
    overflow_flag = 1'b0;
end

ALU_XOR: begin
    result = operand_a ^ operand_b;
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
    carry_flag = 1'b0;
    overflow_flag = 1'b0;
end

ALU_NOT: begin
    result = ~operand_a;
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
    carry_flag = 1'b0;
    overflow_flag = 1'b0;
end
```

### 4.4 Shift Operations

**Logical Shift Left:**
```verilog
ALU_SHL: begin
    result = operand_a << operand_b[5:0];  // Use lower 6 bits of operand_b
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
    // Carry is last bit shifted out
    if (operand_b[5:0] <= 64)
        carry_flag = operand_a[64 - operand_b[5:0]];
    else
        carry_flag = 1'b0;
    overflow_flag = 1'b0;
end
```

**Logical Shift Right:**
```verilog
ALU_SHR: begin
    result = operand_a >> operand_b[5:0];
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
    if (operand_b[5:0] > 0 && operand_b[5:0] <= 64)
        carry_flag = operand_a[operand_b[5:0] - 1];
    else
        carry_flag = 1'b0;
    overflow_flag = 1'b0;
end
```

**Arithmetic Shift Right (preserves sign):**
```verilog
ALU_SAR: begin
    result = $signed(operand_a) >>> operand_b[5:0];
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
    if (operand_b[5:0] > 0 && operand_b[5:0] <= 64)
        carry_flag = operand_a[operand_b[5:0] - 1];
    else
        carry_flag = 1'b0;
    overflow_flag = 1'b0;
end
```

### 4.5 Flag Generation Logic

**Flag Summary:**
```
Zero Flag (ZF):     Set when result is zero
Carry Flag (CF):    Set when operation produces carry/borrow
Overflow Flag (OF): Set when signed arithmetic overflows
Negative Flag (NF): Set when result is negative (bit 63 = 1)
```

**Comparison Operation:**
```verilog
ALU_CMP: begin
    // Compare by subtraction
    result = operand_a - operand_b;
    zero_flag = (result == 64'h0);        // Equal
    negative_flag = result[63];            // Less than (signed)
    carry_flag = (operand_a < operand_b);  // Less than (unsigned)
    overflow_flag = (operand_a[63] != operand_b[63]) && 
                    (result[63] != operand_a[63]);
end
```

### 4.6 Complete Verilog Implementation

```verilog
// File: verilog/cpu/alu.v
// A1M ALU - Arithmetic Logic Unit
// 64-bit operations with flag generation

module alu (
    input wire [63:0] operand_a,    // First operand
    input wire [63:0] operand_b,    // Second operand
    input wire [3:0] alu_op,        // ALU operation code
    output reg [63:0] result,       // Result
    output reg zero_flag,           // Zero flag
    output reg carry_flag,          // Carry flag
    output reg overflow_flag,       // Overflow flag
    output reg negative_flag        // Negative flag
);

// ALU operation codes
localparam ALU_ADD  = 4'h0;
localparam ALU_SUB  = 4'h1;
localparam ALU_MUL  = 4'h2;
localparam ALU_DIV  = 4'h3;
localparam ALU_MOD  = 4'h4;
localparam ALU_AND  = 4'h5;
localparam ALU_OR   = 4'h6;
localparam ALU_XOR  = 4'h7;
localparam ALU_NOT  = 4'h8;
localparam ALU_SHL  = 4'h9;
localparam ALU_SHR  = 4'hA;
localparam ALU_SAR  = 4'hB;
localparam ALU_CMP  = 4'hC;

// Internal signals for overflow detection
wire [64:0] add_result;
wire [64:0] sub_result;
wire signed [63:0] signed_a, signed_b;

assign signed_a = operand_a;
assign signed_b = operand_b;
assign add_result = {1'b0, operand_a} + {1'b0, operand_b};
assign sub_result = {1'b0, operand_a} - {1'b0, operand_b};

always @(*) begin
    // Default flag values
    zero_flag = 1'b0;
    carry_flag = 1'b0;
    overflow_flag = 1'b0;
    negative_flag = 1'b0;
    result = 64'h0;
    
    case (alu_op)
        ALU_ADD: begin
            result = add_result[63:0];
            carry_flag = add_result[64];
            overflow_flag = (operand_a[63] == operand_b[63]) && 
                           (result[63] != operand_a[63]);
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_SUB: begin
            result = sub_result[63:0];
            carry_flag = sub_result[64];
            overflow_flag = (operand_a[63] != operand_b[63]) && 
                           (result[63] != operand_a[63]);
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_MUL: begin
            result = operand_a * operand_b;
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_DIV: begin
            if (operand_b == 64'h0) begin
                result = 64'hFFFFFFFFFFFFFFFF;
                overflow_flag = 1'b1;
            end else begin
                result = operand_a / operand_b;
            end
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_MOD: begin
            if (operand_b == 64'h0) begin
                result = 64'h0;
                overflow_flag = 1'b1;
            end else begin
                result = operand_a % operand_b;
            end
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_AND: begin
            result = operand_a & operand_b;
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_OR: begin
            result = operand_a | operand_b;
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_XOR: begin
            result = operand_a ^ operand_b;
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_NOT: begin
            result = ~operand_a;
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_SHL: begin
            result = operand_a << operand_b[5:0];
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_SHR: begin
            result = operand_a >> operand_b[5:0];
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_SAR: begin
            result = signed_a >>> operand_b[5:0];
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
        end
        
        ALU_CMP: begin
            result = sub_result[63:0];
            zero_flag = (result == 64'h0);
            negative_flag = result[63];
            carry_flag = (operand_a < operand_b);
            overflow_flag = (operand_a[63] != operand_b[63]) && 
                           (result[63] != operand_a[63]);
        end
        
        default: begin
            result = 64'h0;
            zero_flag = 1'b1;
        end
    endcase
end

endmodule
```

**ALU Usage Example:**
```verilog
// In CPU execute stage
alu main_alu (
    .operand_a(alu_operand_a),
    .operand_b(alu_operand_b),
    .alu_op(alu_operation),
    .result(alu_result),
    .zero_flag(alu_zero),
    .carry_flag(alu_carry),
    .overflow_flag(alu_overflow),
    .negative_flag(alu_negative)
);
```

---

## Chapter 5: Control Unit

### 5.1 Control Signal Generation

The control unit decodes instructions and generates control signals for:
- Register file access
- ALU operation selection
- Memory read/write
- Program counter updates
- Pipeline control

**Control Signals:**
```verilog
// Control signals
wire reg_write;      // Enable register writeback
wire mem_read;       // Memory read enable
wire mem_write;      // Memory write enable
wire [3:0] alu_op;   // ALU operation code
wire alu_src;        // ALU operand B source (0=register, 1=immediate)
wire reg_dst;        // Register destination select
wire branch;         // Branch instruction
wire jump;           // Jump instruction
wire [1:0] mem_to_reg; // Writeback data source
```

### 5.2 Instruction Decoding Logic

**Opcode Decoder:**
```verilog
// Decode opcode to control signals
always @(*) begin
    // Default values
    reg_write = 1'b0;
    mem_read = 1'b0;
    mem_write = 1'b0;
    alu_op = 4'h0;
    alu_src = 1'b0;
    branch = 1'b0;
    jump = 1'b0;
    mem_to_reg = 2'b00;
    
    case (opcode)
        8'h02: begin // ADD
            reg_write = 1'b1;
            alu_op = 4'h0;  // ALU_ADD
            alu_src = 1'b0; // Use register
        end
        
        8'h03: begin // ADDI
            reg_write = 1'b1;
            alu_op = 4'h0;  // ALU_ADD
            alu_src = 1'b1; // Use immediate
        end
        
        8'h04: begin // SUB
            reg_write = 1'b1;
            alu_op = 4'h1;  // ALU_SUB
            alu_src = 1'b0;
        end
        
        8'h20: begin // LOAD
            reg_write = 1'b1;
            mem_read = 1'b1;
            alu_op = 4'h0;  // ADD for address calculation
            alu_src = 1'b1; // Use offset
            mem_to_reg = 2'b01; // Write memory data to register
        end
        
        8'h21: begin // STORE
            mem_write = 1'b1;
            alu_op = 4'h0;  // ADD for address calculation
            alu_src = 1'b1; // Use offset
        end
        
        8'h30: begin // JMP
            jump = 1'b1;
        end
        
        8'h31: begin // JZ
            branch = 1'b1;
        end
        
        8'h39: begin // CALL
            reg_write = 1'b1;  // Write return address to R31
            jump = 1'b1;
        end
        
        // Add more opcodes...
    endcase
end
```

### 5.3 Pipeline Control

**Pipeline Stages Control:**
```verilog
// IF Stage Control
assign imem_read = ~halt_flag & ~syscall_pending;
assign imem_addr = pc;

// ID Stage Control
assign reg_read_addr1 = if_id_instruction[18:14];  // RS1
assign reg_read_addr2 = if_id_instruction[13:9];   // RS2

// EX Stage Control
assign alu_operand_a = id_ex_reg_data1;
assign alu_operand_b = id_ex_alu_src ? 
                       {{50{id_ex_immediate[13]}}, id_ex_immediate} : 
                       id_ex_reg_data2;

// MEM Stage Control
assign dmem_addr = ex_mem_alu_result;
assign dmem_write_data = ex_mem_reg_data2;
assign dmem_read = ex_mem_mem_read;
assign dmem_write = ex_mem_mem_write;

// WB Stage Control
assign reg_write_enable = mem_wb_reg_write;
assign reg_write_addr = mem_wb_rd;
always @(*) begin
    case (mem_wb_mem_to_reg)
        2'b00: reg_write_data = mem_wb_alu_result;
        2'b01: reg_write_data = mem_wb_mem_data;
        2'b10: reg_write_data = mem_wb_pc + 4;
        default: reg_write_data = 64'h0;
    endcase
end
```

### 5.4 Hazard Detection and Resolution

**Data Hazards:**
```verilog
// Detect data hazards
wire data_hazard;
assign data_hazard = (id_ex_reg_write && 
                     (id_ex_rd == if_id_rs1 || id_ex_rd == if_id_rs2)) ||
                     (ex_mem_reg_write && 
                     (ex_mem_rd == if_id_rs1 || ex_mem_rd == if_id_rs2));

// Forwarding logic
always @(*) begin
    forward_a = 2'b00;  // No forwarding
    forward_b = 2'b00;
    
    // EX hazard
    if (ex_mem_reg_write && ex_mem_rd != 0) begin
        if (ex_mem_rd == id_ex_rs1)
            forward_a = 2'b10;  // Forward from MEM stage
        if (ex_mem_rd == id_ex_rs2)
            forward_b = 2'b10;
    end
    
    // MEM hazard
    if (mem_wb_reg_write && mem_wb_rd != 0) begin
        if (mem_wb_rd == id_ex_rs1 && forward_a != 2'b10)
            forward_a = 2'b01;  // Forward from WB stage
        if (mem_wb_rd == id_ex_rs2 && forward_b != 2'b10)
            forward_b = 2'b01;
    end
end
```

### 5.5 Verilog Implementation

**Complete Control Unit:**
```verilog
module control_unit (
    input wire [7:0] opcode,
    output reg reg_write,
    output reg mem_read,
    output reg mem_write,
    output reg [3:0] alu_op,
    output reg alu_src,
    output reg branch,
    output reg jump,
    output reg [1:0] mem_to_reg,
    output reg halt
);

always @(*) begin
    // Defaults
    reg_write = 1'b0;
    mem_read = 1'b0;
    mem_write = 1'b0;
    alu_op = 4'h0;
    alu_src = 1'b0;
    branch = 1'b0;
    jump = 1'b0;
    mem_to_reg = 2'b00;
    halt = 1'b0;
    
    case (opcode)
        8'h00: halt = 1'b0;  // NOP
        8'h01: halt = 1'b1;  // HALT
        
        // Arithmetic R-type
        8'h02, 8'h04, 8'h06, 8'h08, 8'h0A: begin
            reg_write = 1'b1;
            alu_op = opcode[3:0];
        end
        
        // Arithmetic I-type
        8'h03, 8'h05, 8'h07, 8'h09, 8'h0B: begin
            reg_write = 1'b1;
            alu_src = 1'b1;
            alu_op = opcode[3:0];
        end
        
        // Logical operations
        8'h0C: begin // AND
            reg_write = 1'b1;
            alu_op = 4'h5;
        end
        
        8'h0E: begin // OR
            reg_write = 1'b1;
            alu_op = 4'h6;
        end
        
        8'h10: begin // XOR
            reg_write = 1'b1;
            alu_op = 4'h7;
        end
        
        // Memory operations
        8'h20: begin // LOAD
            reg_write = 1'b1;
            mem_read = 1'b1;
            alu_src = 1'b1;
            mem_to_reg = 2'b01;
        end
        
        8'h21: begin // STORE
            mem_write = 1'b1;
            alu_src = 1'b1;
        end
        
        // Control flow
        8'h30: jump = 1'b1;      // JMP
        8'h31: branch = 1'b1;    // JZ
        8'h39: begin             // CALL
            reg_write = 1'b1;
            jump = 1'b1;
            mem_to_reg = 2'b10;  // PC + 4
        end
        
        default: halt = 1'b0;
    endcase
end

endmodule
```

---

## Chapter 6: Memory Organization

### 6.1 Memory Architecture

The A1M memory system uses a Harvard architecture variant with:
- Separate instruction and data memory interfaces
- 64-bit addressing (theoretically 16 exabytes)
- Byte-addressable memory
- Support for byte, halfword, word, and doubleword access

**Memory Layout:**
```
Address Range                   Purpose
───────────────────────────────────────────────────────
0x0000000000000000              Reserved (null pointer)
0x0000000000001000              Code segment (.text)
0x0000000000100000              Data segment (.data)
0x0000000000200000              Heap (dynamic allocation)
...
0x7FFFFFFFFFFFFFFF              Stack (grows downward)
0x8000000000000000              I/O mapped devices
0xFFFFFFFFFFFFFFFF              End of address space
```

### 6.2 Address Space Layout

**Typical Program Memory Map:**
```
┌─────────────────────┐  0xFFFFFFFFFFFFFFFF
│   Stack             │  (grows downward)
│        ↓            │
├─────────────────────┤  0x7FFFFFFFFFFF0000
│                     │
│   Free Space        │
│                     │
├─────────────────────┤  0x0000000000300000
│   Heap              │  (grows upward)
│        ↑            │
├─────────────────────┤  0x0000000000200000
│   .bss              │  (uninitialized data)
├─────────────────────┤  0x0000000000180000
│   .data             │  (initialized data)
├─────────────────────┤  0x0000000000100000
│   .text             │  (code)
├─────────────────────┤  0x0000000000001000
│   Reserved          │
└─────────────────────┘  0x0000000000000000
```

### 6.3 Memory Access Instructions

**Load Operations:**
```assembly
# LOAD - Load 64-bit doubleword
LOAD R1, 0(R2)          # R1 = Memory[R2 + 0]
LOAD R3, 100(R4)        # R3 = Memory[R4 + 100]

# LOADB - Load byte (zero-extended to 64 bits)
LOADB R1, 0(R2)         # R1 = (uint64_t)Memory[R2] (1 byte)

# LOADH - Load halfword (16 bits, zero-extended)
LOADH R1, 0(R2)         # R1 = (uint64_t)Memory[R2] (2 bytes)

# LOADW - Load word (32 bits, zero-extended)
LOADW R1, 0(R2)         # R1 = (uint64_t)Memory[R2] (4 bytes)
```

**Store Operations:**
```assembly
# STORE - Store 64-bit doubleword
STORE R1, 0(R2)         # Memory[R2 + 0] = R1

# STOREB - Store byte
STOREB R1, 0(R2)        # Memory[R2] = R1[7:0]

# STOREH - Store halfword
STOREH R1, 0(R2)        # Memory[R2:R2+1] = R1[15:0]

# STOREW - Store word
STOREW R1, 0(R2)        # Memory[R2:R2+3] = R1[31:0]
```

### 6.4 Cache Organization (Future)

**Planned Cache Hierarchy:**
```
┌────────────────┐
│      CPU       │
│     Core       │
└───────┬────────┘
        │
    ┌───▼───┐
    │  L1   │  32 KB, 2-way set associative
    │ Cache │  64-byte cache line
    └───┬───┘
        │
    ┌───▼───┐
    │  L2   │  256 KB, 4-way set associative
    │ Cache │  64-byte cache line
    └───┬───┘
        │
    ┌───▼────┐
    │  Main  │  Up to 16 MB (emulator)
    │ Memory │  Unlimited (hardware)
    └────────┘
```

### 6.5 Verilog Memory Module

**Simple Memory Module:**
```verilog
module memory (
    input wire clk,
    input wire reset,
    
    // Instruction port
    input wire [63:0] imem_addr,
    output reg [31:0] imem_data,
    input wire imem_read,
    
    // Data port
    input wire [63:0] dmem_addr,
    input wire [63:0] dmem_write_data,
    output reg [63:0] dmem_read_data,
    input wire dmem_read,
    input wire dmem_write
);

// Memory array (16 MB)
parameter MEM_SIZE = 16 * 1024 * 1024;  // 16 MB
reg [7:0] memory [0:MEM_SIZE-1];

integer i;

// Initialize memory
initial begin
    for (i = 0; i < MEM_SIZE; i = i + 1) begin
        memory[i] = 8'h0;
    end
end

// Instruction fetch (word-aligned)
always @(*) begin
    if (imem_read && imem_addr < MEM_SIZE - 3) begin
        imem_data = {memory[imem_addr + 3],
                     memory[imem_addr + 2],
                     memory[imem_addr + 1],
                     memory[imem_addr + 0]};
    end else begin
        imem_data = 32'h0;
    end
end

// Data memory read
always @(*) begin
    if (dmem_read && dmem_addr < MEM_SIZE - 7) begin
        dmem_read_data = {memory[dmem_addr + 7],
                          memory[dmem_addr + 6],
                          memory[dmem_addr + 5],
                          memory[dmem_addr + 4],
                          memory[dmem_addr + 3],
                          memory[dmem_addr + 2],
                          memory[dmem_addr + 1],
                          memory[dmem_addr + 0]};
    end else begin
        dmem_read_data = 64'h0;
    end
end

// Data memory write (synchronous)
always @(posedge clk) begin
    if (dmem_write && dmem_addr < MEM_SIZE - 7) begin
        memory[dmem_addr + 0] <= dmem_write_data[7:0];
        memory[dmem_addr + 1] <= dmem_write_data[15:8];
        memory[dmem_addr + 2] <= dmem_write_data[23:16];
        memory[dmem_addr + 3] <= dmem_write_data[31:24];
        memory[dmem_addr + 4] <= dmem_write_data[39:32];
        memory[dmem_addr + 5] <= dmem_write_data[47:40];
        memory[dmem_addr + 6] <= dmem_write_data[55:48];
        memory[dmem_addr + 7] <= dmem_write_data[63:56];
    end
end

endmodule
```

---

## Chapter 7: Pipeline Architecture

### 7.1 5-Stage Pipeline Overview

The A1M CPU implements a classic 5-stage RISC pipeline:

**Pipeline Stages:**
1. **IF** - Instruction Fetch
2. **ID** - Instruction Decode
3. **EX** - Execute
4. **MEM** - Memory Access
5. **WB** - Write Back

**Pipeline Diagram:**
```
Cycle:  1    2    3    4    5    6    7    8
───────────────────────────────────────────────
Inst1:  IF   ID   EX   MEM  WB
Inst2:       IF   ID   EX   MEM  WB
Inst3:            IF   ID   EX   MEM  WB
Inst4:                 IF   ID   EX   MEM  WB
```

**Benefits:**
- Instruction throughput: 1 instruction per cycle (ideally)
- Multiple instructions in flight simultaneously
- Better hardware utilization
- Higher overall performance

### 7.2 Instruction Fetch (IF)

**IF Stage Operations:**
1. Read instruction from memory at PC address
2. Increment PC by 4
3. Pass instruction and PC to ID stage

**Verilog Implementation:**
```verilog
// Instruction Fetch stage
always @(posedge clk or posedge reset) begin
    if (reset) begin
        pc <= RESET_VECTOR;
        if_id_instruction <= 32'h0;
        if_id_pc <= 64'h0;
    end else if (!halt_flag && !syscall_pending) begin
        // Fetch instruction
        if_id_instruction <= imem_data;
        if_id_pc <= pc;
        
        // Update PC
        if (jump_taken) begin
            pc <= jump_target;
        end else if (branch_taken) begin
            pc <= branch_target;
        end else begin
            pc <= pc + 4;
        end
    end
end
```

### 7.3 Instruction Decode (ID)

**ID Stage Operations:**
1. Decode instruction fields (opcode, rd, rs1, rs2, immediate)
2. Read source registers from register file
3. Generate control signals
4. Pass all to EX stage

**Verilog Implementation:**
```verilog
// Instruction Decode stage
always @(posedge clk or posedge reset) begin
    if (reset) begin
        id_ex_opcode <= 8'h0;
        id_ex_rd <= 5'h0;
        id_ex_rs1 <= 5'h0;
        id_ex_rs2 <= 5'h0;
        id_ex_immediate <= 14'h0;
        id_ex_reg_data1 <= 64'h0;
        id_ex_reg_data2 <= 64'h0;
        id_ex_pc <= 64'h0;
        id_ex_reg_write <= 1'b0;
        id_ex_mem_read <= 1'b0;
        id_ex_mem_write <= 1'b0;
        id_ex_alu_op <= 4'h0;
        id_ex_alu_src <= 1'b0;
    end else begin
        // Decode instruction
        id_ex_opcode <= if_id_instruction[31:24];
        id_ex_rd <= if_id_instruction[23:19];
        id_ex_rs1 <= if_id_instruction[18:14];
        id_ex_rs2 <= if_id_instruction[13:9];
        id_ex_immediate <= if_id_instruction[13:0];
        id_ex_jump_addr <= if_id_instruction[23:0];
        
        // Read registers
        id_ex_reg_data1 <= reg_read_data1;
        id_ex_reg_data2 <= reg_read_data2;
        id_ex_pc <= if_id_pc;
        
        // Control signals
        id_ex_reg_write <= reg_write;
        id_ex_mem_read <= mem_read;
        id_ex_mem_write <= mem_write;
        id_ex_alu_op <= alu_op;
        id_ex_alu_src <= alu_src;
        id_ex_mem_to_reg <= mem_to_reg;
        id_ex_branch <= branch;
        id_ex_jump <= jump;
    end
end
```

### 7.4 Execute (EX)

**EX Stage Operations:**
1. Perform ALU operation
2. Calculate branch target
3. Calculate memory address
4. Pass results to MEM stage

**Verilog Implementation:**
```verilog
// Execute stage
always @(posedge clk or posedge reset) begin
    if (reset) begin
        ex_mem_rd <= 5'h0;
        ex_mem_alu_result <= 64'h0;
        ex_mem_reg_data2 <= 64'h0;
        ex_mem_reg_write <= 1'b0;
        ex_mem_mem_read <= 1'b0;
        ex_mem_mem_write <= 1'b0;
        ex_mem_zero_flag <= 1'b0;
    end else begin
        ex_mem_rd <= id_ex_rd;
        ex_mem_alu_result <= alu_result;
        ex_mem_reg_data2 <= id_ex_reg_data2;
        ex_mem_reg_write <= id_ex_reg_write;
        ex_mem_mem_read <= id_ex_mem_read;
        ex_mem_mem_write <= id_ex_mem_write;
        ex_mem_mem_to_reg <= id_ex_mem_to_reg;
        ex_mem_zero_flag <= alu_zero;
        ex_mem_carry_flag <= alu_carry;
        ex_mem_overflow_flag <= alu_overflow;
        ex_mem_negative_flag <= alu_negative;
    end
end
```

### 7.5 Memory Access (MEM)

**MEM Stage Operations:**
1. Access data memory (if load/store)
2. Pass ALU result or memory data to WB
3. Handle memory exceptions

**Verilog Implementation:**
```verilog
// Memory Access stage
always @(posedge clk or posedge reset) begin
    if (reset) begin
        mem_wb_rd <= 5'h0;
        mem_wb_alu_result <= 64'h0;
        mem_wb_mem_data <= 64'h0;
        mem_wb_reg_write <= 1'b0;
    end else begin
        mem_wb_rd <= ex_mem_rd;
        mem_wb_alu_result <= ex_mem_alu_result;
        mem_wb_mem_data <= dmem_read_data;
        mem_wb_reg_write <= ex_mem_reg_write;
        mem_wb_mem_to_reg <= ex_mem_mem_to_reg;
    end
end
```

### 7.6 Write Back (WB)

**WB Stage Operations:**
1. Select data to write back (ALU result or memory data)
2. Write to destination register
3. Update register file

**Verilog Implementation:**
```verilog
// Write Back stage (combinational selection)
always @(*) begin
    case (mem_wb_mem_to_reg)
        2'b00: reg_write_data = mem_wb_alu_result;  // ALU result
        2'b01: reg_write_data = mem_wb_mem_data;    // Memory data
        2'b10: reg_write_data = mem_wb_pc + 4;      // PC + 4 (for CALL)
        default: reg_write_data = 64'h0;
    endcase
end
```

### 7.7 Pipeline Hazards and Solutions

**Types of Hazards:**

**1. Data Hazards:**
```assembly
ADD R1, R2, R3   # R1 = R2 + R3
SUB R4, R1, R5   # R4 = R1 - R5  (needs R1 from previous instruction)
```

**Solution: Forwarding (Bypassing)**
```verilog
// Forward ALU result from EX/MEM to EX stage
if (ex_mem_reg_write && ex_mem_rd != 0 && ex_mem_rd == id_ex_rs1)
    alu_operand_a = ex_mem_alu_result;

// Forward from MEM/WB to EX stage
if (mem_wb_reg_write && mem_wb_rd != 0 && mem_wb_rd == id_ex_rs1)
    alu_operand_a = reg_write_data;
```

**2. Control Hazards (Branches):**
```assembly
JZ label         # Branch not resolved until MEM stage
ADD R1, R2, R3   # Should this execute?
```

**Solution: Branch Prediction + Flushing**
```verilog
// Simple prediction: assume not taken
// Flush pipeline if prediction wrong
if (branch_taken && branch_prediction_wrong) begin
    if_id_instruction <= 32'h0;  // NOP
    id_ex_opcode <= 8'h0;        // NOP
end
```

**3. Structural Hazards:**
- Avoided by having separate instruction and data memory
- Separate read/write ports on register file

**Pipeline Efficiency:**
```
CPI (Cycles Per Instruction):
- Ideal: 1.0 (one instruction per cycle)
- With hazards: 1.2 - 1.5
- With stalls: 2.0 - 3.0
```

---

# PART II: ASSEMBLY LANGUAGE

---

## Chapter 8: A1M Assembly Language Fundamentals

### 8.1 Assembly Language Basics

Assembly language is a low-level programming language with a strong correspondence between instructions and machine code. Each assembly instruction typically corresponds to one machine instruction.

**Assembly Program Structure:**
```assembly
; Comments start with semicolon
; Directives start with period

.text                   ; Code section

main:                   ; Label definition
    MOVI R1, 10        ; Load immediate value
    MOVI R2, 20        ; Load another value
    ADD R3, R1, R2     ; Add them
    SYSCALL 0x00       ; Exit
```

### 8.2 Syntax and Structure

**Instruction Format:**
```
[label:] MNEMONIC operand1, operand2, operand3 [; comment]
```

**Elements:**
- **Label**: Optional identifier followed by colon
- **Mnemonic**: Instruction name (ADD, SUB, LOAD, etc.)
- **Operands**: Registers, immediates, or memory addresses
- **Comment**: Optional explanatory text after semicolon

**Register Notation:**
```
R0, R1, R2, ..., R31    ; General purpose registers
```

**Immediate Values:**
```
Decimal:    10, -5, 100
Hexadecimal: 0x10, 0xFF, 0xDEADBEEF
Binary:     0b1010, 0b11111111
```

### 8.3 Assembler Directives

**Common Directives:**

```assembly
.text                   ; Start code section
.data                   ; Start data section
.global symbol          ; Make symbol globally visible
.align n                ; Align to n-byte boundary
.word value             ; Define 32-bit value
.dword value            ; Define 64-bit value
.byte value             ; Define 8-bit value
.ascii "string"         ; Define ASCII string
.asciiz "string"        ; Define null-terminated string
```

**Example Usage:**
```assembly
.data
    msg: .asciiz "Hello, World!"
    value: .dword 42

.text
.global main

main:
    MOVI R1, 72        ; 'H'
    SYSCALL 0x02       ; Print character
    SYSCALL 0x00       ; Exit
```

### 8.4 Labels and Symbols

**Labels:**
- Mark locations in code or data
- Used for jumps, calls, and data references
- Must start with letter or underscore
- Can contain letters, digits, underscores

**Label Examples:**
```assembly
start:                  ; Code label
    MOVI R1, 0

loop_begin:            ; Loop label
    ADDI R1, R1, 1
    CMPI R1, 10
    JNZ loop_begin

data_value:            ; Data label
    .dword 12345
```

**Symbol Resolution:**
```assembly
CALL function_name     ; Forward reference (resolved in second pass)
JMP loop_start         ; Backward reference (already defined)
```

### 8.5 Comments and Documentation

**Single-line Comments:**
```assembly
; This is a comment
MOVI R1, 10            ; Load 10 into R1
```

**Multi-line Comments (convention):**
```assembly
; ────────────────────────────────────
; Function: calculate_sum
; Purpose: Add two numbers
; Input: R1 = first number, R2 = second
; Output: R2 = sum
; ────────────────────────────────────
calculate_sum:
    ADD R2, R1, R2
    RET
```

**Documentation Best Practices:**
```assembly
;═══════════════════════════════════════════════════════════
; Program: factorial.asm
; Author: Shahrear Hossain Shawon
; Date: November 2025
; Description: Calculate factorial of a number
; Input: R1 = number
; Output: R2 = factorial(number)
;═══════════════════════════════════════════════════════════

.text
.global main

main:
    MOVI R1, 5         ; Calculate 5!
    CALL factorial     ; Call factorial function
    SYSCALL 0x00       ; Exit

;───────────────────────────────────────────────────────────
; Function: factorial
; Calculates n! recursively
; Input: R1 = n
; Output: R2 = n!
; Modifies: R1, R2, R31
;───────────────────────────────────────────────────────────
factorial:
    ; Base case: if n <= 1, return 1
    CMPI R1, 1
    JNN base_case
    
    ; Recursive case: n * factorial(n-1)
    ; Save R1 and R31
    PUSH R1
    PUSH R31
    
    ; Calculate factorial(n-1)
    SUBI R1, R1, 1
    CALL factorial
    
    ; Restore R1 and R31
    POP R31
    POP R1
    
    ; Multiply n * factorial(n-1)
    MUL R2, R1, R2
    RET

base_case:
    MOVI R2, 1
    RET
```

---

## Chapter 9: Data Movement Instructions

### 9.1 Register-to-Register Transfers

**MOV Instruction:**
```assembly
MOV RD, RS              ; RD = RS

; Examples:
MOV R1, R2              ; Copy R2 to R1
MOV R5, R10             ; Copy R10 to R5
```

**Implementation Note:**
Since A1M doesn't have a dedicated MOV instruction, it's simulated using ADD:
```assembly
; MOV R1, R2 is assembled as:
MOVI R1, 0
ADD R1, R1, R2          ; R1 = 0 + R2
```

Or more efficiently in the compiler:
```assembly
; Direct ADD with R0 (always zero)
ADD R1, R2, R0          ; R1 = R2 + 0 = R2
```

### 9.2 Immediate Value Loading

**MOVI - Move Immediate (14-bit):**
```assembly
MOVI RD, immediate      ; RD = immediate (sign-extended)

; Examples:
MOVI R1, 42             ; R1 = 42
MOVI R2, -10            ; R2 = -10
MOVI R3, 0x100          ; R3 = 256
MOVI R4, 8191           ; Maximum positive 14-bit value
MOVI R5, -8192          ; Minimum negative 14-bit value
```

**LUI - Load Upper Immediate:**
```assembly
LUI RD, immediate       ; RD = immediate << 50

; Used for loading large constants:
LUI R1, 0x1000          ; R1 = 0x1000 << 50
ADDI R1, R1, 0x500      ; R1 = R1 + 0x500
; Now R1 contains large 64-bit value
```

**Loading 64-bit Constants:**
```assembly
; Method 1: Using LUI + ORI
LUI R1, 0x1234          ; Upper bits
ORI R1, R1, 0x5678      ; Lower bits

; Method 2: Multiple shifts and adds
MOVI R1, 0x12
SHLI R1, R1, 8
ADDI R1, R1, 0x34
SHLI R1, R1, 8
ADDI R1, R1, 0x56
```

### 9.3 Memory Load Operations

**LOAD - Load Doubleword (64 bits):**
```assembly
LOAD RD, offset(base)   ; RD = Memory[base + offset]

; Examples:
LOAD R1, 0(R2)          ; Load from address in R2
LOAD R3, 8(R4)          ; Load from R4 + 8
LOAD R5, -16(R6)        ; Load from R6 - 16
```

**LOADB - Load Byte (8 bits, zero-extended):**
```assembly
LOADB RD, offset(base)  ; RD = (uint64_t)Memory[base + offset]

; Examples:
LOADB R1, 0(R2)         ; Load byte, zero-extend to 64 bits
LOADB R3, 100(R4)       ; Load byte from R4 + 100
```

**LOADH - Load Halfword (16 bits):**
```assembly
LOADH RD, offset(base)  ; RD = (uint64_t)Memory[base + offset] (2 bytes)

; Example:
LOADH R1, 0(R2)         ; Load 16-bit value
```

**LOADW - Load Word (32 bits):**
```assembly
LOADW RD, offset(base)  ; RD = (uint64_t)Memory[base + offset] (4 bytes)

; Example:
LOADW R1, 0(R2)         ; Load 32-bit value
```

### 9.4 Memory Store Operations

**STORE - Store Doubleword:**
```assembly
STORE RS, offset(base)  ; Memory[base + offset] = RS

; Examples:
STORE R1, 0(R2)         ; Store R1 to address in R2
STORE R3, 8(R4)         ; Store R3 to R4 + 8
STORE R5, -32(R6)       ; Store R5 to R6 - 32
```

**STOREB - Store Byte:**
```assembly
STOREB RS, offset(base) ; Memory[base + offset] = RS[7:0]

; Example:
STOREB R1, 0(R2)        ; Store lowest byte of R1
```

**STOREH - Store Halfword:**
```assembly
STOREH RS, offset(base) ; Memory[base + offset:offset+1] = RS[15:0]

; Example:
STOREH R1, 0(R2)        ; Store lowest 16 bits of R1
```

**STOREW - Store Word:**
```assembly
STOREW RS, offset(base) ; Memory[base + offset:offset+3] = RS[31:0]

; Example:
STOREW R1, 0(R2)        ; Store lowest 32 bits of R1
```

### 9.5 Code Examples

**Example 1: Array Access**
```assembly
; Load array element
; R1 = base address of array
; R2 = index
; R3 = array[index]

.text
    MOVI R1, 0x100000   ; Array base address
    MOVI R2, 5          ; Index = 5
    
    ; Calculate address: base + (index * 8)
    SHLI R2, R2, 3      ; R2 = index * 8 (each element is 8 bytes)
    ADD R2, R1, R2      ; R2 = base + offset
    
    LOAD R3, 0(R2)      ; R3 = array[5]
```

**Example 2: String Copy**
```assembly
; Copy string from source to destination
; R1 = source address
; R2 = destination address

.text
string_copy:
    MOVI R3, 0          ; Offset counter

copy_loop:
    LOADB R4, 0(R1)     ; Load byte from source
    STOREB R4, 0(R2)    ; Store byte to destination
    
    ; Check for null terminator
    CMPI R4, 0
    JZ copy_done
    
    ; Increment pointers
    ADDI R1, R1, 1
    ADDI R2, R2, 1
    JMP copy_loop

copy_done:
    RET
```

**Example 3: Struct Member Access**
```assembly
; Struct layout:
; struct Point {
;     int64_t x;   // offset 0
;     int64_t y;   // offset 8
; };

.text
    ; Load struct member
    MOVI R1, 0x200000   ; Base address of struct
    
    LOAD R2, 0(R1)      ; R2 = point.x
    LOAD R3, 8(R1)      ; R3 = point.y
    
    ; Modify and store back
    ADDI R2, R2, 10     ; point.x += 10
    ADDI R3, R3, 20     ; point.y += 20
    
    STORE R2, 0(R1)     ; Save point.x
    STORE R3, 8(R1)     ; Save point.y
```

---

## Chapter 10: Arithmetic and Logical Instructions

### 10.1 Arithmetic Operations

**Addition:**
```assembly
ADD RD, RS1, RS2        ; RD = RS1 + RS2
ADDI RD, RS1, imm       ; RD = RS1 + imm

; Examples:
ADD R1, R2, R3          ; R1 = R2 + R3
ADDI R1, R1, 10         ; R1 = R1 + 10
ADDI R4, R5, -5         ; R4 = R5 - 5 (add negative)
```

**Subtraction:**
```assembly
SUB RD, RS1, RS2        ; RD = RS1 - RS2
SUBI RD, RS1, imm       ; RD = RS1 - imm

; Examples:
SUB R1, R2, R3          ; R1 = R2 - R3
SUBI R1, R1, 1          ; R1 = R1 - 1 (decrement)
```

**Multiplication:**
```assembly
MUL RD, RS1, RS2        ; RD = RS1 * RS2 (signed)
MULI RD, RS1, imm       ; RD = RS1 * imm

; Examples:
MUL R1, R2, R3          ; R1 = R2 * R3
MULI R4, R5, 8          ; R4 = R5 * 8
```

**Division:**
```assembly
DIV RD, RS1, RS2        ; RD = RS1 / RS2 (signed)
DIVI RD, RS1, imm       ; RD = RS1 / imm

; Examples:
DIV R1, R2, R3          ; R1 = R2 / R3
DIVI R4, R5, 2          ; R4 = R5 / 2 (halve)
```

**Modulo:**
```assembly
MOD RD, RS1, RS2        ; RD = RS1 % RS2
MODI RD, RS1, imm       ; RD = RS1 % imm

; Examples:
MOD R1, R2, R3          ; R1 = R2 % R3
MODI R4, R5, 10         ; R4 = R5 % 10
```

### 10.2 Logical Operations

**AND:**
```assembly
AND RD, RS1, RS2        ; RD = RS1 & RS2
ANDI RD, RS1, imm       ; RD = RS1 & imm

; Examples:
AND R1, R2, R3          ; Bitwise AND
ANDI R4, R5, 0xFF       ; Mask lowest 8 bits
ANDI R6, R7, 1          ; Test if odd
```

**OR:**
```assembly
OR RD, RS1, RS2         ; RD = RS1 | RS2
ORI RD, RS1, imm        ; RD = RS1 | imm

; Examples:
OR R1, R2, R3           ; Bitwise OR
ORI R4, R5, 0x80        ; Set bit 7
```

**XOR:**
```assembly
XOR RD, RS1, RS2        ; RD = RS1 ^ RS2
XORI RD, RS1, imm       ; RD = RS1 ^ imm

; Examples:
XOR R1, R2, R3          ; Bitwise XOR
XORI R4, R4, -1         ; Bitwise NOT (XOR with all 1s)
XOR R5, R6, R6          ; Clear register (R5 = 0)
```

**NOT:**
```assembly
NOT RD, RS              ; RD = ~RS (bitwise NOT)

; Example:
NOT R1, R2              ; R1 = ~R2 (all bits flipped)

; Implementation (using XOR):
XORI R1, R2, -1         ; XOR with 0xFFFFFFFFFFFFFFFF
```

### 10.3 Shift Operations

**Logical Shift Left:**
```assembly
SHL RD, RS1, RS2        ; RD = RS1 << RS2
SHLI RD, RS1, imm       ; RD = RS1 << imm

; Examples:
SHL R1, R2, R3          ; Shift R2 left by R3 positions
SHLI R4, R5, 3          ; Multiply R5 by 8 (2^3)
SHLI R6, R7, 1          ; Double R7
```

**Logical Shift Right:**
```assembly
SHR RD, RS1, RS2        ; RD = RS1 >> RS2 (unsigned)
SHRI RD, RS1, imm       ; RD = RS1 >> imm

; Examples:
SHR R1, R2, R3          ; Shift R2 right by R3 positions
SHRI R4, R5, 3          ; Divide R5 by 8 (unsigned)
SHRI R6, R7, 1          ; Halve R7 (unsigned)
```

**Arithmetic Shift Right:**
```assembly
SAR RD, RS1, RS2        ; RD = RS1 >> RS2 (sign-extended)
SARI RD, RS1, imm       ; RD = RS1 >> imm (sign-extended)

; Examples:
SAR R1, R2, R3          ; Shift right, preserve sign
SARI R4, R5, 3          ; Divide R5 by 8 (signed)
```

**Rotate Operations:**
```assembly
ROL RD, RS1, RS2        ; Rotate left
ROR RD, RS1, RS2        ; Rotate right

; Examples:
ROL R1, R2, 8           ; Rotate R2 left by 8 bits
ROR R3, R4, 16          ; Rotate R4 right by 16 bits
```

### 10.4 Comparison Operations

**CMP - Compare:**
```assembly
CMP RS1, RS2            ; Compare RS1 with RS2, set flags
CMPI RS1, imm           ; Compare RS1 with immediate

; Sets flags:
; Zero flag (ZF): RS1 == RS2
; Negative flag (NF): RS1 < RS2 (signed)
; Carry flag (CF): RS1 < RS2 (unsigned)

; Examples:
CMP R1, R2              ; Compare R1 and R2
CMPI R3, 0              ; Compare R3 with 0
CMPI R4, 100            ; Compare R4 with 100
```

**Conditional Execution Based on Flags:**
```assembly
; After CMP R1, R2:
JZ equal_label          ; Jump if R1 == R2
JNZ not_equal_label     ; Jump if R1 != R2
JGT greater_label       ; Jump if R1 > R2 (signed)
JLT less_label          ; Jump if R1 < R2 (signed)
JGE greater_eq_label    ; Jump if R1 >= R2
JLE less_eq_label       ; Jump if R1 <= R2
```

### 10.5 Practical Examples

**Example 1: Absolute Value**
```assembly
; Calculate absolute value of R1
; Result in R1

absolute_value:
    CMPI R1, 0          ; Compare with 0
    JGE already_positive
    
    ; Negate if negative
    MOVI R2, 0
    SUB R1, R2, R1      ; R1 = 0 - R1
    
already_positive:
    RET
```

**Example 2: Min/Max Functions**
```assembly
; Find minimum of R1 and R2, result in R3

find_min:
    CMP R1, R2          ; Compare R1 and R2
    JLE r1_is_smaller
    
    ; R2 is smaller
    MOV R3, R2
    JMP min_done
    
r1_is_smaller:
    MOV R3, R1
    
min_done:
    RET

; Find maximum of R1 and R2, result in R3

find_max:
    CMP R1, R2          ; Compare R1 and R2
    JGE r1_is_larger
    
    ; R2 is larger
    MOV R3, R2
    JMP max_done
    
r1_is_larger:
    MOV R3, R1
    
max_done:
    RET
```

**Example 3: Power of 2 Check**
```assembly
; Check if R1 is a power of 2
; Result: R2 = 1 if power of 2, 0 otherwise

is_power_of_two:
    ; Power of 2 has only one bit set
    ; n & (n-1) == 0 for powers of 2
    
    CMPI R1, 0
    JLE not_power       ; 0 and negative not powers of 2
    
    SUBI R2, R1, 1      ; R2 = R1 - 1
    AND R2, R1, R2      ; R2 = R1 & (R1 - 1)
    CMPI R2, 0
    JZ is_power
    
not_power:
    MOVI R2, 0          ; Not a power of 2
    RET
    
is_power:
    MOVI R2, 1          ; Is a power of 2
    RET
```

**Example 4: Count Set Bits (Population Count)**
```assembly
; Count number of 1 bits in R1
; Result in R2

popcount:
    MOVI R2, 0          ; Counter = 0
    MOVI R3, 64         ; Loop 64 times
    
count_loop:
    ANDI R4, R1, 1      ; Get lowest bit
    ADD R2, R2, R4      ; Add to counter
    SHRI R1, R1, 1      ; Shift right
    
    SUBI R3, R3, 1      ; Decrement loop counter
    CMPI R3, 0
    JNZ count_loop
    
    RET
```

**Example 5: Swap Two Values Without Temp**
```assembly
; Swap R1 and R2 using XOR trick

swap_xor:
    XOR R1, R1, R2      ; R1 = R1 ^ R2
    XOR R2, R1, R2      ; R2 = R1 ^ R2 = (R1 ^ R2) ^ R2 = R1
    XOR R1, R1, R2      ; R1 = R1 ^ R2 = (R1 ^ R2) ^ R1 = R2
    RET
```

---

## Chapter 11: Control Flow Instructions

### 11.1 Unconditional Jumps

**JMP - Jump:**
```assembly
JMP target              ; PC = target address

; Examples:
JMP main_loop           ; Jump to label
JMP skip_section        ; Jump forward
JMP 0x1000             ; Jump to absolute address
```

**JMPR - Jump Register:**
```assembly
JMPR RS                 ; PC = RS (indirect jump)

; Examples:
JMPR R1                 ; Jump to address in R1
JMPR R31                ; Jump to return address
```

### 11.2 Conditional Branches

**Branch Instructions (based on flags):**
```assembly
JZ target               ; Jump if Zero flag set (equal)
JNZ target              ; Jump if Zero flag clear (not equal)
JGT target              ; Jump if Greater Than (signed)
JLT target              ; Jump if Less Than (signed)
JGE target              ; Jump if Greater or Equal (signed)
JLE target              ; Jump if Less or Equal (signed)
JC target               ; Jump if Carry flag set
JNC target              ; Jump if Carry flag clear
JO target               ; Jump if Overflow flag set
JNO target              ; Jump if Overflow flag clear
JN target               ; Jump if Negative flag set
JNN target              ; Jump if Negative flag clear (positive)

; Examples:
CMP R1, R2
JZ equal_case           ; Jump if R1 == R2
JGT greater_case        ; Jump if R1 > R2
JLT less_case           ; Jump if R1 < R2
```

### 11.3 Function Calls

**CALL - Call Subroutine:**
```assembly
CALL target             ; R31 = PC + 4; PC = target

; Examples:
CALL function_name      ; Call function, save return address
CALL printf             ; Call standard library function
```

**RET - Return from Subroutine:**
```assembly
RET                     ; PC = R31

; Example function:
my_function:
    ; Function body
    ADDI R1, R1, 1
    RET                 ; Return to caller
```

**Function with Arguments:**
```assembly
; Calling convention:
; R4-R11: First 8 arguments
; R1: Return value
; R31: Return address

; Call function: result = add_numbers(a, b)
    MOVI R4, 10         ; First argument
    MOVI R5, 20         ; Second argument
    CALL add_numbers
    MOV R10, R1         ; Save result

add_numbers:
    ADD R1, R4, R5      ; Return value in R1
    RET
```

### 11.4 Stack Operations

**PUSH - Push to Stack:**
```assembly
PUSH RS                 ; SP -= 8; Memory[SP] = RS

; Examples:
PUSH R1                 ; Save R1 on stack
PUSH R2                 ; Save R2 on stack
PUSH R31                ; Save return address
```

**POP - Pop from Stack:**
```assembly
POP RD                  ; RD = Memory[SP]; SP += 8

; Examples:
POP R1                  ; Restore R1 from stack
POP R2                  ; Restore R2 from stack
POP R31                 ; Restore return address
```

**Stack Frame Example:**
```assembly
function_with_locals:
    ; Prologue: Save registers and allocate locals
    PUSH R31                ; Save return address
    PUSH R4                 ; Save callee-saved registers
    PUSH R5
    SUBI R3, R3, 16         ; Allocate 16 bytes for locals
    
    ; Function body
    MOVI R4, 10
    STORE R4, 0(R3)         ; Store local variable
    LOAD R5, 0(R3)          ; Load local variable
    
    ; Epilogue: Restore and return
    ADDI R3, R3, 16         ; Deallocate locals
    POP R5                  ; Restore registers
    POP R4
    POP R31
    RET
```

### 11.5 Loop Constructs

**For Loop:**
```assembly
; for (i = 0; i < 10; i++) { ... }

    MOVI R1, 0              ; i = 0
    MOVI R2, 10             ; limit = 10

for_loop:
    CMP R1, R2              ; Compare i with limit
    JGE for_done            ; Exit if i >= 10
    
    ; Loop body
    ; ... do something ...
    
    ADDI R1, R1, 1          ; i++
    JMP for_loop

for_done:
```

**While Loop:**
```assembly
; while (condition) { ... }

while_loop:
    ; Check condition
    CMPI R1, 0
    JZ while_done           ; Exit if condition false
    
    ; Loop body
    ; ... do something ...
    SUBI R1, R1, 1          ; Modify condition variable
    
    JMP while_loop

while_done:
```

**Do-While Loop:**
```assembly
; do { ... } while (condition);

do_while_loop:
    ; Loop body (always executes once)
    ; ... do something ...
    SUBI R1, R1, 1
    
    ; Check condition
    CMPI R1, 0
    JNZ do_while_loop       ; Continue if condition true
```

**Break and Continue:**
```assembly
; Loop with break and continue

    MOVI R1, 0

loop_with_break:
    ADDI R1, R1, 1
    
    ; Continue if R1 is odd
    ANDI R2, R1, 1
    CMPI R2, 1
    JZ continue_label
    
    ; Break if R1 > 100
    CMPI R1, 100
    JGT break_label
    
    ; Process even numbers
    ; ... code ...
    
continue_label:
    JMP loop_with_break

break_label:
```

### 11.6 Switch/Case Statements

**Jump Table Implementation:**
```assembly
; switch (R1) { case 0: ... case 1: ... case 2: ... }

switch_statement:
    ; Bounds check
    CMPI R1, 3
    JGE default_case
    
    ; Jump table lookup
    SHLI R1, R1, 3          ; Multiply by 8 (address size)
    MOVI R2, jump_table
    ADD R1, R1, R2          ; R1 = &jump_table[case]
    LOAD R1, 0(R1)          ; R1 = jump_table[case]
    JMPR R1                 ; Jump to case handler

jump_table:
    .dword case_0
    .dword case_1
    .dword case_2

case_0:
    ; Handle case 0
    MOVI R10, 100
    JMP switch_end

case_1:
    ; Handle case 1
    MOVI R10, 200
    JMP switch_end

case_2:
    ; Handle case 2
    MOVI R10, 300
    JMP switch_end

default_case:
    ; Default handler
    MOVI R10, 0

switch_end:
```

### 11.7 Nested Function Calls

**Example: Factorial (Recursive):**
```assembly
; int64_t factorial(int64_t n) {
;     if (n <= 1) return 1;
;     return n * factorial(n - 1);
; }

factorial:
    ; R4 = n (input)
    ; R1 = return value
    
    ; Base case: if n <= 1
    CMPI R4, 1
    JLE base_case
    
    ; Recursive case
    PUSH R4                 ; Save n
    PUSH R31                ; Save return address
    
    SUBI R4, R4, 1          ; n - 1
    CALL factorial          ; factorial(n - 1)
    MOV R5, R1              ; Save result
    
    POP R31                 ; Restore return address
    POP R4                  ; Restore n
    
    MUL R1, R4, R5          ; n * factorial(n - 1)
    RET

base_case:
    MOVI R1, 1              ; Return 1
    RET
```

**Example: Fibonacci (Recursive):**
```assembly
; int64_t fib(int64_t n) {
;     if (n <= 1) return n;
;     return fib(n-1) + fib(n-2);
; }

fibonacci:
    ; R4 = n (input)
    ; R1 = return value
    
    ; Base case: if n <= 1, return n
    CMPI R4, 1
    JLE fib_base
    
    ; Save registers
    PUSH R4
    PUSH R31
    
    ; Calculate fib(n-1)
    SUBI R4, R4, 1
    CALL fibonacci
    PUSH R1                 ; Save fib(n-1)
    
    ; Calculate fib(n-2)
    POP R5                  ; R5 = fib(n-1)
    POP R31
    POP R4
    PUSH R5                 ; Save fib(n-1) again
    PUSH R31
    
    SUBI R4, R4, 2
    CALL fibonacci
    
    ; Add results
    POP R31
    POP R5                  ; R5 = fib(n-1)
    ADD R1, R1, R5          ; fib(n-1) + fib(n-2)
    RET

fib_base:
    MOV R1, R4              ; Return n
    RET
```

---

## Chapter 12: System Call Interface

### 12.1 System Call Mechanism

The A1M architecture uses a dedicated `SYSCALL` instruction to request operating system services. The syscall number is specified as an immediate operand.

**SYSCALL Instruction:**
```assembly
SYSCALL imm             ; Trigger system call with code 'imm'
```

**Register Convention:**
- **R1**: Syscall argument / return value
- **R2**: Secondary argument (for some syscalls)
- **Immediate**: Syscall number (0x00 - 0xFF)

### 12.2 Standard System Calls

**0x00 - EXIT:**
```assembly
; Exit program
SYSCALL 0x00            ; Terminate program

; Example:
main:
    ; ... program code ...
    SYSCALL 0x00        ; Exit with success
```

**0x01 - PRINT_INT:**
```assembly
; Print integer in R1
SYSCALL 0x01

; Example:
    MOVI R1, 42
    SYSCALL 0x01        ; Prints "42"
```

**0x02 - PRINT_CHAR:**
```assembly
; Print character in R1
SYSCALL 0x02

; Example:
    MOVI R1, 65         ; ASCII 'A'
    SYSCALL 0x02        ; Prints "A"
```

**0x03 - PRINT_STRING:**
```assembly
; Print null-terminated string at address in R1
SYSCALL 0x03

; Example:
.data
    message: .asciiz "Hello, World!"

.text
    MOVI R1, message
    SYSCALL 0x03        ; Prints "Hello, World!"
```

**0x04 - READ_INT:**
```assembly
; Read integer from stdin into R1
SYSCALL 0x04

; Example:
    SYSCALL 0x04        ; Wait for user input
    MOV R10, R1         ; Save input value
```

**0x05 - READ_CHAR:**
```assembly
; Read character from stdin into R1
SYSCALL 0x05

; Example:
    SYSCALL 0x05        ; Read one character
    STOREB R1, 0(R2)    ; Store it
```

**0x06 - ALLOCATE:**
```assembly
; Allocate R1 bytes of memory
; Returns pointer in R1
SYSCALL 0x06

; Example:
    MOVI R1, 1024       ; Request 1KB
    SYSCALL 0x06        ; Allocate memory
    MOV R10, R1         ; Save pointer
```

**0x07 - FREE:**
```assembly
; Free memory at address in R1
SYSCALL 0x07

; Example:
    MOV R1, R10         ; Pointer to free
    SYSCALL 0x07        ; Free memory
```

### 12.3 I/O Examples

**Example 1: Print "Hello, World!"**
```assembly
.data
    hello_msg: .asciiz "Hello, World!\n"

.text
.global main

main:
    MOVI R1, hello_msg
    SYSCALL 0x03        ; Print string
    SYSCALL 0x00        ; Exit
```

**Example 2: Read and Echo Integer**
```assembly
.data
    prompt: .asciiz "Enter a number: "
    result_msg: .asciiz "You entered: "

.text
main:
    ; Print prompt
    MOVI R1, prompt
    SYSCALL 0x03
    
    ; Read integer
    SYSCALL 0x04
    MOV R10, R1         ; Save input
    
    ; Print result message
    MOVI R1, result_msg
    SYSCALL 0x03
    
    ; Print the number
    MOV R1, R10
    SYSCALL 0x01
    
    ; Exit
    SYSCALL 0x00
```

**Example 3: Character-by-Character String Input**
```assembly
.data
    buffer: .space 100      ; 100-byte buffer

.text
main:
    MOVI R2, buffer         ; R2 = buffer address
    MOVI R3, 0              ; R3 = character count

read_loop:
    SYSCALL 0x05            ; Read character
    CMPI R1, 10             ; Check for newline (0x0A)
    JZ read_done
    
    STOREB R1, 0(R2)        ; Store character
    ADDI R2, R2, 1          ; Next position
    ADDI R3, R3, 1          ; Increment count
    
    CMPI R3, 99             ; Check buffer limit
    JLT read_loop

read_done:
    MOVI R1, 0
    STOREB R1, 0(R2)        ; Null terminate
    
    ; Print the string
    MOVI R1, buffer
    SYSCALL 0x03
    
    SYSCALL 0x00
```

### 12.4 Memory Management

**Dynamic Allocation Example:**
```assembly
; Allocate array of 10 integers

.text
main:
    ; Allocate 10 * 8 = 80 bytes
    MOVI R1, 80
    SYSCALL 0x06            ; Allocate
    MOV R10, R1             ; R10 = array base
    
    ; Initialize array
    MOVI R2, 0              ; Index
init_loop:
    CMPI R2, 10
    JGE init_done
    
    ; array[i] = i * i
    MUL R3, R2, R2
    SHLI R4, R2, 3          ; Offset = i * 8
    ADD R4, R10, R4         ; Address = base + offset
    STORE R3, 0(R4)
    
    ADDI R2, R2, 1
    JMP init_loop

init_done:
    ; Use array...
    
    ; Free memory
    MOV R1, R10
    SYSCALL 0x07            ; Free
    
    SYSCALL 0x00
```

### 12.5 File I/O (Extended Syscalls)

**0x10 - OPEN:**
```assembly
; Open file
; R1 = filename pointer
; R2 = mode (0=read, 1=write, 2=append)
; Returns: R1 = file descriptor
SYSCALL 0x10
```

**0x11 - CLOSE:**
```assembly
; Close file
; R1 = file descriptor
SYSCALL 0x11
```

**0x12 - READ:**
```assembly
; Read from file
; R1 = file descriptor
; R2 = buffer pointer
; R3 = bytes to read
; Returns: R1 = bytes read
SYSCALL 0x12
```

**0x13 - WRITE:**
```assembly
; Write to file
; R1 = file descriptor
; R2 = buffer pointer
; R3 = bytes to write
; Returns: R1 = bytes written
SYSCALL 0x13
```

**File I/O Example:**
```assembly
.data
    filename: .asciiz "output.txt"
    data: .asciiz "Hello from A1M!\n"

.text
main:
    ; Open file for writing
    MOVI R1, filename
    MOVI R2, 1              ; Write mode
    SYSCALL 0x10
    MOV R10, R1             ; Save file descriptor
    
    ; Write data
    MOV R1, R10             ; File descriptor
    MOVI R2, data           ; Data pointer
    MOVI R3, 16             ; Bytes to write
    SYSCALL 0x13
    
    ; Close file
    MOV R1, R10
    SYSCALL 0x11
    
    SYSCALL 0x00
```

---

## Chapter 13: Assembler Implementation

### 13.1 Two-Pass Assembly Process

The A1M assembler uses a two-pass algorithm:

**Pass 1: Symbol Collection**
- Scan through source code
- Record label definitions and their addresses
- Build symbol table
- Calculate instruction sizes

**Pass 2: Code Generation**
- Generate machine code for each instruction
- Resolve symbolic references using symbol table
- Apply relocations
- Output binary file

### 13.2 Assembler Data Structures

**Symbol Table Entry:**
```c
typedef struct {
    char name[64];          // Symbol name
    uint64_t address;       // Address/value
    int section;            // .text, .data, etc.
    int global;             // Is it global?
} Symbol;

// Symbol table
Symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;
```

**Instruction Encoding:**
```c
typedef struct {
    uint8_t opcode;         // 8-bit opcode
    uint8_t rd;             // Destination register (5 bits)
    uint8_t rs1;            // Source register 1 (5 bits)
    uint8_t rs2;            // Source register 2 (5 bits)
    int16_t immediate;      // 14-bit immediate (sign-extended)
    uint32_t jump_addr;     // 24-bit jump address
} Instruction;
```

### 13.3 Lexical Analysis

**Token Types:**
```c
typedef enum {
    TOKEN_LABEL,            // identifier:
    TOKEN_MNEMONIC,         // ADD, SUB, etc.
    TOKEN_REGISTER,         // R0, R1, etc.
    TOKEN_IMMEDIATE,        // 42, 0x10, 0b1010
    TOKEN_COMMA,            // ,
    TOKEN_LPAREN,           // (
    TOKEN_RPAREN,           // )
    TOKEN_DIRECTIVE,        // .text, .data, etc.
    TOKEN_STRING,           // "hello"
    TOKEN_NEWLINE,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[256];
    int64_t value;          // For immediates
    int line_number;
} Token;
```

**Lexer Implementation (Simplified):**
```c
Token get_next_token(FILE *fp) {
    Token tok;
    int c;
    
    // Skip whitespace
    while ((c = fgetc(fp)) != EOF && isspace(c) && c != '\n');
    
    if (c == EOF) {
        tok.type = TOKEN_EOF;
        return tok;
    }
    
    if (c == '\n') {
        tok.type = TOKEN_NEWLINE;
        return tok;
    }
    
    if (c == ';') {
        // Skip comment
        while ((c = fgetc(fp)) != EOF && c != '\n');
        tok.type = TOKEN_NEWLINE;
        return tok;
    }
    
    if (c == '.') {
        // Directive
        tok.type = TOKEN_DIRECTIVE;
        // Read directive name...
        return tok;
    }
    
    if (c == 'R' || c == 'r') {
        // Register
        int reg_num = 0;
        fscanf(fp, "%d", &reg_num);
        tok.type = TOKEN_REGISTER;
        tok.value = reg_num;
        return tok;
    }
    
    if (isdigit(c) || c == '-') {
        // Immediate value
        ungetc(c, fp);
        fscanf(fp, "%ld", &tok.value);
        tok.type = TOKEN_IMMEDIATE;
        return tok;
    }
    
    if (isalpha(c) || c == '_') {
        // Identifier or mnemonic
        int i = 0;
        tok.lexeme[i++] = c;
        while ((c = fgetc(fp)) != EOF && (isalnum(c) || c == '_')) {
            tok.lexeme[i++] = c;
        }
        tok.lexeme[i] = '\0';
        ungetc(c, fp);
        
        // Check if it's a label (followed by ':')
        c = fgetc(fp);
        if (c == ':') {
            tok.type = TOKEN_LABEL;
        } else {
            ungetc(c, fp);
            tok.type = TOKEN_MNEMONIC;
        }
        return tok;
    }
    
    // Single character tokens
    if (c == ',') tok.type = TOKEN_COMMA;
    else if (c == '(') tok.type = TOKEN_LPAREN;
    else if (c == ')') tok.type = TOKEN_RPAREN;
    
    return tok;
}
```

### 13.4 Instruction Encoding

**Encode R-Type Instruction:**
```c
uint32_t encode_r_type(uint8_t opcode, uint8_t rd, 
                       uint8_t rs1, uint8_t rs2) {
    uint32_t instruction = 0;
    
    instruction |= ((uint32_t)opcode << 24);    // Bits 31-24
    instruction |= ((uint32_t)rd << 19);        // Bits 23-19
    instruction |= ((uint32_t)rs1 << 14);       // Bits 18-14
    instruction |= ((uint32_t)rs2 << 9);        // Bits 13-9
    // Bits 8-0: unused
    
    return instruction;
}
```

**Encode I-Type Instruction:**
```c
uint32_t encode_i_type(uint8_t opcode, uint8_t rd, 
                       uint8_t rs1, int16_t immediate) {
    uint32_t instruction = 0;
    
    instruction |= ((uint32_t)opcode << 24);    // Bits 31-24
    instruction |= ((uint32_t)rd << 19);        // Bits 23-19
    instruction |= ((uint32_t)rs1 << 14);       // Bits 18-14
    instruction |= ((uint32_t)immediate & 0x3FFF);  // Bits 13-0
    
    return instruction;
}
```

**Encode J-Type Instruction:**
```c
uint32_t encode_j_type(uint8_t opcode, uint32_t address) {
    uint32_t instruction = 0;
    
    instruction |= ((uint32_t)opcode << 24);    // Bits 31-24
    instruction |= (address & 0xFFFFFF);        // Bits 23-0
    
    return instruction;
}
```

### 13.5 Symbol Resolution

**Add Symbol to Table:**
```c
void add_symbol(const char *name, uint64_t address, 
                int section, int global) {
    if (symbol_count >= MAX_SYMBOLS) {
        error("Symbol table overflow");
        return;
    }
    
    Symbol *sym = &symbol_table[symbol_count++];
    strncpy(sym->name, name, 63);
    sym->name[63] = '\0';
    sym->address = address;
    sym->section = section;
    sym->global = global;
}
```

**Lookup Symbol:**
```c
Symbol *find_symbol(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return &symbol_table[i];
        }
    }
    return NULL;
}
```

**Resolve Label Reference:**
```c
int64_t resolve_label(const char *label, uint64_t current_pc) {
    Symbol *sym = find_symbol(label);
    if (!sym) {
        error("Undefined label: %s", label);
        return 0;
    }
    
    // For branches, calculate relative offset
    int64_t offset = sym->address - current_pc;
    return offset;
}
```

### 13.6 Complete Assembler Flow

```c
int assemble(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "wb");
    
    uint64_t pc = 0;
    int current_section = SECTION_TEXT;
    
    // Pass 1: Build symbol table
    while (!feof(in)) {
        Token tok = get_next_token(in);
        
        if (tok.type == TOKEN_LABEL) {
            add_symbol(tok.lexeme, pc, current_section, 0);
        }
        else if (tok.type == TOKEN_MNEMONIC) {
            pc += 4;  // Each instruction is 4 bytes
        }
        else if (tok.type == TOKEN_DIRECTIVE) {
            handle_directive(&tok, &current_section, &pc);
        }
    }
    
    // Pass 2: Generate code
    rewind(in);
    pc = 0;
    
    while (!feof(in)) {
        Token tok = get_next_token(in);
        
        if (tok.type == TOKEN_MNEMONIC) {
            uint32_t instruction = encode_instruction(&tok, pc);
            fwrite(&instruction, sizeof(uint32_t), 1, out);
            pc += 4;
        }
    }
    
    fclose(in);
    fclose(out);
    return 0;
}
```

---

# PART III: EMULATOR

---

## Chapter 14: Emulator Architecture

### 14.1 Emulator Overview

The A1M emulator is a software implementation that executes A1M machine code on a host system. It simulates the CPU, memory, and I/O devices.

**Key Components:**
- CPU state (registers, PC, flags)
- Memory subsystem
- Instruction fetch-decode-execute loop
- System call handler
- Debugging facilities

**Emulator Structure:**
```c
typedef struct {
    uint64_t registers[32];     // R0-R31
    uint64_t pc;                // Program counter
    uint8_t flags;              // Status flags (Z, N, C, V)
    uint8_t *memory;            // Main memory
    size_t memory_size;         // Memory size
    int running;                // Execution state
    uint64_t instruction_count; // Performance counter
} CPU;

// Flag bits
#define FLAG_ZERO     0x01
#define FLAG_NEGATIVE 0x02
#define FLAG_CARRY    0x04
#define FLAG_OVERFLOW 0x08
```

### 14.2 CPU Initialization

```c
CPU *cpu_create(size_t memory_size) {
    CPU *cpu = malloc(sizeof(CPU));
    if (!cpu) return NULL;
    
    // Initialize registers
    for (int i = 0; i < 32; i++) {
        cpu->registers[i] = 0;
    }
    
    // R0 is hardwired to zero
    cpu->registers[0] = 0;
    
    // Initialize stack pointer (R3) to top of memory
    cpu->registers[3] = memory_size - 8;
    
    // Initialize PC
    cpu->pc = 0x1000;  // Entry point
    
    // Clear flags
    cpu->flags = 0;
    
    // Allocate memory
    cpu->memory = calloc(memory_size, 1);
    cpu->memory_size = memory_size;
    
    // Initialize state
    cpu->running = 1;
    cpu->instruction_count = 0;
    
    return cpu;
}

void cpu_destroy(CPU *cpu) {
    if (cpu) {
        free(cpu->memory);
        free(cpu);
    }
}
```

### 14.3 Memory Access Functions

```c
// Read 8-bit byte from memory
uint8_t mem_read_byte(CPU *cpu, uint64_t address) {
    if (address >= cpu->memory_size) {
        fprintf(stderr, "Memory read out of bounds: 0x%lx\n", address);
        return 0;
    }
    return cpu->memory[address];
}

// Write 8-bit byte to memory
void mem_write_byte(CPU *cpu, uint64_t address, uint8_t value) {
    if (address >= cpu->memory_size) {
        fprintf(stderr, "Memory write out of bounds: 0x%lx\n", address);
        return;
    }
    cpu->memory[address] = value;
}

// Read 64-bit doubleword from memory (little-endian)
uint64_t mem_read_dword(CPU *cpu, uint64_t address) {
    uint64_t value = 0;
    for (int i = 0; i < 8; i++) {
        value |= ((uint64_t)mem_read_byte(cpu, address + i)) << (i * 8);
    }
    return value;
}

// Write 64-bit doubleword to memory (little-endian)
void mem_write_dword(CPU *cpu, uint64_t address, uint64_t value) {
    for (int i = 0; i < 8; i++) {
        mem_write_byte(cpu, address + i, (value >> (i * 8)) & 0xFF);
    }
}

// Read 32-bit instruction from memory
uint32_t mem_read_instruction(CPU *cpu, uint64_t address) {
    uint32_t instruction = 0;
    for (int i = 0; i < 4; i++) {
        instruction |= ((uint32_t)mem_read_byte(cpu, address + i)) << (i * 8);
    }
    return instruction;
}
```

### 14.4 Instruction Fetch and Decode

```c
typedef struct {
    uint8_t opcode;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    int16_t immediate;
    uint32_t jump_addr;
} DecodedInstruction;

DecodedInstruction decode_instruction(uint32_t instruction) {
    DecodedInstruction decoded;
    
    // Extract fields
    decoded.opcode = (instruction >> 24) & 0xFF;
    decoded.rd = (instruction >> 19) & 0x1F;
    decoded.rs1 = (instruction >> 14) & 0x1F;
    decoded.rs2 = (instruction >> 9) & 0x1F;
    
    // Sign-extend 14-bit immediate
    decoded.immediate = instruction & 0x3FFF;
    if (decoded.immediate & 0x2000) {
        decoded.immediate |= 0xC000;  // Sign extend
    }
    
    // 24-bit jump address
    decoded.jump_addr = instruction & 0xFFFFFF;
    
    return decoded;
}
```

### 14.5 Instruction Execution

```c
void execute_instruction(CPU *cpu, DecodedInstruction *inst) {
    uint64_t rs1_val = cpu->registers[inst->rs1];
    uint64_t rs2_val = cpu->registers[inst->rs2];
    uint64_t result = 0;
    int64_t signed_result;
    
    switch (inst->opcode) {
        case 0x00:  // NOP
            break;
            
        case 0x01:  // HALT
            cpu->running = 0;
            break;
            
        case 0x02:  // ADD
            result = rs1_val + rs2_val;
            cpu->registers[inst->rd] = result;
            update_flags(cpu, result);
            break;
            
        case 0x03:  // ADDI
            result = rs1_val + (int64_t)inst->immediate;
            cpu->registers[inst->rd] = result;
            update_flags(cpu, result);
            break;
            
        case 0x04:  // SUB
            result = rs1_val - rs2_val;
            cpu->registers[inst->rd] = result;
            update_flags(cpu, result);
            break;
            
        case 0x05:  // SUBI
            result = rs1_val - (int64_t)inst->immediate;
            cpu->registers[inst->rd] = result;
            update_flags(cpu, result);
            break;
            
        case 0x06:  // MUL
            signed_result = (int64_t)rs1_val * (int64_t)rs2_val;
            cpu->registers[inst->rd] = signed_result;
            update_flags(cpu, signed_result);
            break;
            
        case 0x08:  // DIV
            if (rs2_val != 0) {
                signed_result = (int64_t)rs1_val / (int64_t)rs2_val;
                cpu->registers[inst->rd] = signed_result;
                update_flags(cpu, signed_result);
            } else {
                fprintf(stderr, "Division by zero at PC=0x%lx\n", cpu->pc);
            }
            break;
            
        case 0x0A:  // MOD
            if (rs2_val != 0) {
                signed_result = (int64_t)rs1_val % (int64_t)rs2_val;
                cpu->registers[inst->rd] = signed_result;
                update_flags(cpu, signed_result);
            }
            break;
            
        case 0x0C:  // AND
            result = rs1_val & rs2_val;
            cpu->registers[inst->rd] = result;
            update_flags(cpu, result);
            break;
            
        case 0x0E:  // OR
            result = rs1_val | rs2_val;
            cpu->registers[inst->rd] = result;
            update_flags(cpu, result);
            break;
            
        case 0x10:  // XOR
            result = rs1_val ^ rs2_val;
            cpu->registers[inst->rd] = result;
            update_flags(cpu, result);
            break;
            
        case 0x12:  // SHL
            result = rs1_val << (rs2_val & 0x3F);
            cpu->registers[inst->rd] = result;
            update_flags(cpu, result);
            break;
            
        case 0x14:  // SHR
            result = rs1_val >> (rs2_val & 0x3F);
            cpu->registers[inst->rd] = result;
            update_flags(cpu, result);
            break;
            
        case 0x16:  // SAR (arithmetic right shift)
            signed_result = (int64_t)rs1_val >> (rs2_val & 0x3F);
            cpu->registers[inst->rd] = signed_result;
            update_flags(cpu, signed_result);
            break;
            
        case 0x20:  // LOAD
            result = rs1_val + (int64_t)inst->immediate;
            cpu->registers[inst->rd] = mem_read_dword(cpu, result);
            break;
            
        case 0x21:  // STORE
            result = rs1_val + (int64_t)inst->immediate;
            mem_write_dword(cpu, result, cpu->registers[inst->rd]);
            break;
            
        case 0x30:  // JMP
            cpu->pc = inst->jump_addr;
            return;  // Don't increment PC
            
        case 0x31:  // JZ
            if (cpu->flags & FLAG_ZERO) {
                cpu->pc = inst->jump_addr;
                return;
            }
            break;
            
        case 0x32:  // JNZ
            if (!(cpu->flags & FLAG_ZERO)) {
                cpu->pc = inst->jump_addr;
                return;
            }
            break;
            
        case 0x39:  // CALL
            cpu->registers[31] = cpu->pc + 4;
            cpu->pc = inst->jump_addr;
            return;
            
        case 0x3A:  // RET
            cpu->pc = cpu->registers[31];
            return;
            
        case 0x40:  // CMP
            result = rs1_val - rs2_val;
            update_flags(cpu, result);
            break;
            
        case 0x50:  // SYSCALL
            handle_syscall(cpu, inst->immediate);
            break;
            
        default:
            fprintf(stderr, "Unknown opcode 0x%02x at PC=0x%lx\n", 
                    inst->opcode, cpu->pc);
            cpu->running = 0;
            break;
    }
    
    // R0 is always zero
    cpu->registers[0] = 0;
    
    // Increment PC
    cpu->pc += 4;
}
```

### 14.6 Flag Updates

```c
void update_flags(CPU *cpu, uint64_t result) {
    // Clear all flags
    cpu->flags = 0;
    
    // Zero flag
    if (result == 0) {
        cpu->flags |= FLAG_ZERO;
    }
    
    // Negative flag (MSB set)
    if (result & 0x8000000000000000ULL) {
        cpu->flags |= FLAG_NEGATIVE;
    }
}

void update_flags_with_carry(CPU *cpu, uint64_t a, uint64_t b, 
                             uint64_t result, int subtract) {
    update_flags(cpu, result);
    
    // Carry flag
    if (subtract) {
        if (a < b) cpu->flags |= FLAG_CARRY;
    } else {
        if (result < a) cpu->flags |= FLAG_CARRY;
    }
    
    // Overflow flag (signed overflow)
    int64_t sa = (int64_t)a;
    int64_t sb = (int64_t)b;
    int64_t sr = (int64_t)result;
    
    if (subtract) {
        if ((sa > 0 && sb < 0 && sr < 0) || 
            (sa < 0 && sb > 0 && sr > 0)) {
            cpu->flags |= FLAG_OVERFLOW;
        }
    } else {
        if ((sa > 0 && sb > 0 && sr < 0) || 
            (sa < 0 && sb < 0 && sr > 0)) {
            cpu->flags |= FLAG_OVERFLOW;
        }
    }
}
```

### 14.7 Main Execution Loop

```c
void cpu_run(CPU *cpu) {
    while (cpu->running) {
        // Fetch instruction
        uint32_t instruction = mem_read_instruction(cpu, cpu->pc);
        
        // Decode instruction
        DecodedInstruction decoded = decode_instruction(instruction);
        
        // Execute instruction
        execute_instruction(cpu, &decoded);
        
        // Increment instruction counter
        cpu->instruction_count++;
        
        // Check for execution limit (prevent infinite loops)
        if (cpu->instruction_count > MAX_INSTRUCTIONS) {
            fprintf(stderr, "Execution limit reached\n");
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <binary_file>\n", argv[0]);
        return 1;
    }
    
    // Create CPU
    CPU *cpu = cpu_create(16 * 1024 * 1024);  // 16 MB memory
    
    // Load program into memory
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        fprintf(stderr, "Cannot open file: %s\n", argv[1]);
        cpu_destroy(cpu);
        return 1;
    }
    
    fread(cpu->memory + 0x1000, 1, cpu->memory_size - 0x1000, fp);
    fclose(fp);
    
    // Run program
    cpu_run(cpu);
    
    // Print statistics
    printf("\nExecution completed\n");
    printf("Instructions executed: %lu\n", cpu->instruction_count);
    
    // Cleanup
    cpu_destroy(cpu);
    
    return 0;
}
```

---

## Chapter 15: System Call Implementation

### 15.1 System Call Handler

```c
void handle_syscall(CPU *cpu, uint8_t syscall_number) {
    uint64_t arg1 = cpu->registers[1];
    uint64_t arg2 = cpu->registers[2];
    uint64_t arg3 = cpu->registers[3];
    
    switch (syscall_number) {
        case 0x00:  // EXIT
            cpu->running = 0;
            break;
            
        case 0x01:  // PRINT_INT
            printf("%ld", (int64_t)arg1);
            fflush(stdout);
            break;
            
        case 0x02:  // PRINT_CHAR
            printf("%c", (char)arg1);
            fflush(stdout);
            break;
            
        case 0x03:  // PRINT_STRING
            syscall_print_string(cpu, arg1);
            break;
            
        case 0x04:  // READ_INT
            syscall_read_int(cpu);
            break;
            
        case 0x05:  // READ_CHAR
            syscall_read_char(cpu);
            break;
            
        case 0x06:  // ALLOCATE
            syscall_allocate(cpu, arg1);
            break;
            
        case 0x07:  // FREE
            syscall_free(cpu, arg1);
            break;
            
        default:
            fprintf(stderr, "Unknown syscall: 0x%02x\n", syscall_number);
            break;
    }
}
```

### 15.2 I/O System Calls

```c
void syscall_print_string(CPU *cpu, uint64_t address) {
    while (1) {
        uint8_t ch = mem_read_byte(cpu, address);
        if (ch == 0) break;  // Null terminator
        printf("%c", ch);
        address++;
    }
    fflush(stdout);
}

void syscall_read_int(CPU *cpu) {
    int64_t value;
    if (scanf("%ld", &value) == 1) {
        cpu->registers[1] = value;
    } else {
        cpu->registers[1] = 0;
    }
}

void syscall_read_char(CPU *cpu) {
    int ch = getchar();
    cpu->registers[1] = (ch == EOF) ? 0 : ch;
}
```

### 15.3 Memory Management System Calls

```c
#define MAX_ALLOCATIONS 1024

typedef struct {
    uint64_t address;
    size_t size;
    int used;
} Allocation;

Allocation allocations[MAX_ALLOCATIONS];
uint64_t heap_pointer = 0x300000;  // Start of heap

void init_heap() {
    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        allocations[i].used = 0;
    }
}

void syscall_allocate(CPU *cpu, size_t size) {
    // Find free allocation slot
    int slot = -1;
    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        if (!allocations[i].used) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        fprintf(stderr, "Allocation table full\n");
        cpu->registers[1] = 0;
        return;
    }
    
    // Check if we have enough memory
    if (heap_pointer + size >= cpu->memory_size) {
        fprintf(stderr, "Out of memory\n");
        cpu->registers[1] = 0;
        return;
    }
    
    // Allocate
    allocations[slot].address = heap_pointer;
    allocations[slot].size = size;
    allocations[slot].used = 1;
    
    // Clear allocated memory
    for (size_t i = 0; i < size; i++) {
        mem_write_byte(cpu, heap_pointer + i, 0);
    }
    
    // Return address in R1
    cpu->registers[1] = heap_pointer;
    
    // Update heap pointer
    heap_pointer += size;
    
    // Align to 8-byte boundary
    heap_pointer = (heap_pointer + 7) & ~7ULL;
}

void syscall_free(CPU *cpu, uint64_t address) {
    // Find allocation
    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        if (allocations[i].used && allocations[i].address == address) {
            allocations[i].used = 0;
            return;
        }
    }
    
    fprintf(stderr, "Invalid free: address 0x%lx not allocated\n", address);
}
```

### 15.4 Debugging Support

```c
void print_cpu_state(CPU *cpu) {
    printf("\n=== CPU State ===\n");
    printf("PC: 0x%016lx\n", cpu->pc);
    printf("Flags: [%c%c%c%c]\n",
           (cpu->flags & FLAG_ZERO) ? 'Z' : '-',
           (cpu->flags & FLAG_NEGATIVE) ? 'N' : '-',
           (cpu->flags & FLAG_CARRY) ? 'C' : '-',
           (cpu->flags & FLAG_OVERFLOW) ? 'V' : '-');
    
    printf("\nRegisters:\n");
    for (int i = 0; i < 32; i += 4) {
        printf("R%-2d: 0x%016lx  R%-2d: 0x%016lx  "
               "R%-2d: 0x%016lx  R%-2d: 0x%016lx\n",
               i, cpu->registers[i],
               i+1, cpu->registers[i+1],
               i+2, cpu->registers[i+2],
               i+3, cpu->registers[i+3]);
    }
    
    printf("\nInstructions executed: %lu\n", cpu->instruction_count);
    printf("=================\n\n");
}

void disassemble_instruction(uint32_t instruction, uint64_t pc) {
    DecodedInstruction decoded = decode_instruction(instruction);
    
    printf("0x%08lx: ", pc);
    
    switch (decoded.opcode) {
        case 0x00: printf("NOP"); break;
        case 0x01: printf("HALT"); break;
        case 0x02: 
            printf("ADD R%d, R%d, R%d", decoded.rd, decoded.rs1, decoded.rs2);
            break;
        case 0x03:
            printf("ADDI R%d, R%d, %d", decoded.rd, decoded.rs1, decoded.immediate);
            break;
        case 0x04:
            printf("SUB R%d, R%d, R%d", decoded.rd, decoded.rs1, decoded.rs2);
            break;
        case 0x20:
            printf("LOAD R%d, %d(R%d)", decoded.rd, decoded.immediate, decoded.rs1);
            break;
        case 0x21:
            printf("STORE R%d, %d(R%d)", decoded.rd, decoded.immediate, decoded.rs1);
            break;
        case 0x30:
            printf("JMP 0x%06x", decoded.jump_addr);
            break;
        case 0x39:
            printf("CALL 0x%06x", decoded.jump_addr);
            break;
        case 0x3A:
            printf("RET");
            break;
        case 0x50:
            printf("SYSCALL 0x%02x", decoded.immediate & 0xFF);
            break;
        default:
            printf("UNKNOWN(0x%02x)", decoded.opcode);
            break;
    }
    
    printf("\n");
}
```

---

# PART IV: ALGO LANGUAGE

---

## Chapter 16: Algo Language Introduction

### 16.1 Language Philosophy

Algo is a high-level programming language designed for the A1M architecture. It combines:
- Simple, clean syntax inspired by C
- Strong typing with type inference
- Modern features (functions, structs, arrays)
- Direct access to hardware when needed
- Educational focus

**Design Goals:**
- Easy to learn for beginners
- Sufficient for complex programs
- Efficient compilation to A1M assembly
- Clear correspondence to underlying hardware

### 16.2 Basic Syntax

**Hello World:**
```algo
fun main() {
    print("Hello, World!");
}
```

**Variables:**
```algo
fun main() {
    int x = 10;
    int y = 20;
    int sum = x + y;
    print(sum);
}
```

**Types:**
```algo
int     // 64-bit signed integer
bool    // Boolean (true/false)
char    // 8-bit character
long    // 64-bit signed integer (alias for int)
```

### 16.3 Program Structure

**Complete Program:**
```algo
// Global variables
int global_counter = 0;

// Function declaration
fun increment() -> int {
    global_counter = global_counter + 1;
    return global_counter;
}

// Main function (entry point)
fun main() {
    int count = increment();
    print("Count: ");
    print(count);
}
```

**Comments:**
```algo
// Single-line comment

/*
   Multi-line comment
   can span multiple lines
*/
```

### 16.4 Lexical Elements

**Keywords:**
```
fun      // Function definition
return   // Return from function
if       // Conditional
else     // Alternative condition
while    // While loop
for      // For loop
int      // Integer type
bool     // Boolean type
char     // Character type
long     // Long integer type
true     // Boolean true
false    // Boolean false
```

**Operators:**
```algo
// Arithmetic
+  -  *  /  %

// Comparison
==  !=  <  >  <=  >=

// Logical
&&  ||  !

// Bitwise
&  |  ^  ~  <<  >>

// Assignment
=  +=  -=  *=  /=  %=
```

**Literals:**
```algo
// Integer literals
42
0x2A        // Hexadecimal
0b101010    // Binary

// Boolean literals
true
false

// Character literals
'A'
'\\n'
'\\t'

// String literals
"Hello, World!"
"Line 1\\nLine 2"
```

### 16.5 Type System

**Type Declaration:**
```algo
int x;              // Uninitialized
int y = 42;         // Initialized
bool flag = true;
char letter = 'A';
```

**Type Inference (future):**
```algo
var x = 42;         // Inferred as int
var name = "John";  // Inferred as string
```

**Type Sizes:**
```algo
fun main() {
    print(sizeof(int));     // 8
    print(sizeof(bool));    // 1
    print(sizeof(char));    // 1
    print(sizeof(long));    // 8
}
```

---

## Chapter 17: Expressions and Operators

### 17.1 Arithmetic Expressions

**Basic Arithmetic:**
```algo
fun main() {
    int a = 10;
    int b = 3;
    
    int sum = a + b;        // 13
    int diff = a - b;       // 7
    int prod = a * b;       // 30
    int quot = a / b;       // 3
    int rem = a % b;        // 1
    
    print(sum);
    print(diff);
    print(prod);
    print(quot);
    print(rem);
}
```

**Operator Precedence:**
```
Highest:  ()
          * / %
          + -
          << >>
          < <= > >=
          == !=
          &
          ^
          |
          &&
Lowest:   ||
```

**Example:**
```algo
int result = 2 + 3 * 4;     // 14, not 20
int result2 = (2 + 3) * 4;  // 20
```

### 17.2 Comparison and Logical Operators

**Comparisons:**
```algo
fun main() {
    int x = 10;
    int y = 20;
    
    bool eq = (x == y);     // false
    bool ne = (x != y);     // true
    bool lt = (x < y);      // true
    bool gt = (x > y);      // false
    bool le = (x <= y);     // true
    bool ge = (x >= y);     // false
}
```

**Logical Operations:**
```algo
fun main() {
    bool a = true;
    bool b = false;
    
    bool and_result = a && b;   // false
    bool or_result = a || b;    // true
    bool not_a = !a;            // false
}
```

**Short-circuit Evaluation:**
```algo
fun expensive_check() -> bool {
    print("Checking...");
    return true;
}

fun main() {
    bool x = false;
    
    // expensive_check() is NOT called
    if (x && expensive_check()) {
        print("Both true");
    }
}
```

### 17.3 Bitwise Operators

**Bitwise Operations:**
```algo
fun main() {
    int a = 0b1100;     // 12
    int b = 0b1010;     // 10
    
    int and_result = a & b;     // 0b1000 = 8
    int or_result = a | b;      // 0b1110 = 14
    int xor_result = a ^ b;     // 0b0110 = 6
    int not_result = ~a;        // 0b...0011 = -13
    
    int left_shift = a << 2;    // 0b110000 = 48
    int right_shift = a >> 2;   // 0b0011 = 3
}
```

**Bit Manipulation Examples:**
```algo
// Set bit n
fun set_bit(int value, int n) -> int {
    return value | (1 << n);
}

// Clear bit n
fun clear_bit(int value, int n) -> int {
    return value & ~(1 << n);
}

// Toggle bit n
fun toggle_bit(int value, int n) -> int {
    return value ^ (1 << n);
}

// Test bit n
fun test_bit(int value, int n) -> bool {
    return (value & (1 << n)) != 0;
}
```

### 17.4 Assignment Operators

**Simple Assignment:**
```algo
int x = 10;
x = 20;
```

**Compound Assignment:**
```algo
int x = 10;

x += 5;     // x = x + 5;  (15)
x -= 3;     // x = x - 3;  (12)
x *= 2;     // x = x * 2;  (24)
x /= 4;     // x = x / 4;  (6)
x %= 4;     // x = x % 4;  (2)
```

**Increment/Decrement (future):**
```algo
int x = 10;
x++;        // x = x + 1
x--;        // x = x - 1
++x;        // x = x + 1
--x;        // x = x - 1
```

### 17.5 Expression Examples

**Example 1: Quadratic Formula**
```algo
fun solve_quadratic(int a, int b, int c) {
    // Calculate discriminant
    int discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        print("No real solutions");
        return;
    }
    
    // For simplicity, integer square root
    int sqrt_disc = int_sqrt(discriminant);
    
    int x1 = (-b + sqrt_disc) / (2 * a);
    int x2 = (-b - sqrt_disc) / (2 * a);
    
    print("x1 = ");
    print(x1);
    print("x2 = ");
    print(x2);
}
```

**Example 2: Power Function**
```algo
fun power(int base, int exponent) -> int {
    if (exponent == 0) {
        return 1;
    }
    
    int result = 1;
    int i = 0;
    while (i < exponent) {
        result = result * base;
        i = i + 1;
    }
    
    return result;
}
```

**Example 3: GCD (Greatest Common Divisor)**
```algo
fun gcd(int a, int b) -> int {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

---

## Chapter 18: Control Structures

### 18.1 If-Else Statements

**Simple If:**
```algo
fun main() {
    int x = 10;
    
    if (x > 0) {
        print("Positive");
    }
}
```

**If-Else:**
```algo
fun main() {
    int x = -5;
    
    if (x > 0) {
        print("Positive");
    } else {
        print("Non-positive");
    }
}
```

**If-Else-If Chain:**
```algo
fun classify(int x) {
    if (x > 0) {
        print("Positive");
    } else if (x < 0) {
        print("Negative");
    } else {
        print("Zero");
    }
}
```

**Nested If:**
```algo
fun check_range(int x) {
    if (x >= 0) {
        if (x <= 100) {
            print("In range [0, 100]");
        } else {
            print("Greater than 100");
        }
    } else {
        print("Negative");
    }
}
```

### 18.2 While Loops

**Basic While Loop:**
```algo
fun count_to_ten() {
    int i = 1;
    while (i <= 10) {
        print(i);
        i = i + 1;
    }
}
```

**Infinite Loop with Break:**
```algo
fun read_until_zero() {
    while (true) {
        int value = read_int();
        
        if (value == 0) {
            break;
        }
        
        print(value);
    }
}
```

**Factorial Using While:**
```algo
fun factorial(int n) -> int {
    int result = 1;
    int i = 1;
    
    while (i <= n) {
        result = result * i;
        i = i + 1;
    }
    
    return result;
}
```

### 18.3 For Loops

**Basic For Loop:**
```algo
fun count_to_ten() {
    int i;
    for (i = 1; i <= 10; i = i + 1) {
        print(i);
    }
}
```

**For Loop with Multiple Statements:**
```algo
fun sum_array(int n) -> int {
    int sum = 0;
    int i;
    
    for (i = 0; i < n; i = i + 1) {
        sum = sum + i;
    }
    
    return sum;
}
```

**Nested For Loops:**
```algo
fun multiplication_table() {
    int i;
    int j;
    
    for (i = 1; i <= 10; i = i + 1) {
        for (j = 1; j <= 10; j = j + 1) {
            int product = i * j;
            print(product);
            print(" ");
        }
        print("\\n");
    }
}
```

### 18.4 Break and Continue

**Break Statement:**
```algo
fun find_first_divisor(int n) -> int {
    int i;
    for (i = 2; i < n; i = i + 1) {
        if (n % i == 0) {
            return i;  // Found divisor, exit
        }
    }
    return n;  // n is prime
}
```

**Continue Statement:**
```algo
fun print_odd_numbers(int n) {
    int i;
    for (i = 1; i <= n; i = i + 1) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        print(i);
    }
}
```

### 18.5 Control Flow Examples

**Example 1: Prime Number Check**
```algo
fun is_prime(int n) -> bool {
    if (n <= 1) {
        return false;
    }
    
    if (n == 2) {
        return true;
    }
    
    if (n % 2 == 0) {
        return false;
    }
    
    int i;
    for (i = 3; i * i <= n; i = i + 2) {
        if (n % i == 0) {
            return false;
        }
    }
    
    return true;
}
```

**Example 2: Fibonacci Sequence**
```algo
fun fibonacci(int n) {
    int a = 0;
    int b = 1;
    int i;
    
    for (i = 0; i < n; i = i + 1) {
        print(a);
        
        int temp = a + b;
        a = b;
        b = temp;
    }
}
```

**Example 3: Binary Search**
```algo
fun binary_search(int value, int n) -> int {
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        int mid_value = array[mid];  // Assume array exists
        
        if (mid_value == value) {
            return mid;
        } else if (mid_value < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;  // Not found
}
```

---

## Chapter 19: Functions

### 19.1 Function Declaration and Definition

**Basic Function:**
```algo
fun greet() {
    print("Hello!");
}

fun main() {
    greet();
}
```

**Function with Parameters:**
```algo
fun add(int a, int b) -> int {
    return a + b;
}

fun main() {
    int result = add(5, 3);
    print(result);  // 8
}
```

**Function with Multiple Parameters:**
```algo
fun calculate(int a, int b, int c) -> int {
    return a * b + c;
}

fun main() {
    int result = calculate(2, 3, 4);  // 2*3 + 4 = 10
    print(result);
}
```

### 19.2 Return Values

**Single Return:**
```algo
fun square(int x) -> int {
    return x * x;
}
```

**Multiple Return Points:**
```algo
fun absolute(int x) -> int {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}
```

**Early Return:**
```algo
fun divide(int a, int b) -> int {
    if (b == 0) {
        print("Error: division by zero");
        return 0;
    }
    
    return a / b;
}
```

**Void Functions:**
```algo
fun print_banner() {
    print("====================");
    print("  Welcome to A1M   ");
    print("====================");
}
```

### 19.3 Recursion

**Factorial (Recursive):**
```algo
fun factorial(int n) -> int {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

fun main() {
    int result = factorial(5);  // 120
    print(result);
}
```

**Fibonacci (Recursive):**
```algo
fun fibonacci(int n) -> int {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

fun main() {
    int i;
    for (i = 0; i < 10; i = i + 1) {
        print(fibonacci(i));
    }
}
```

**Binary Search (Recursive):**
```algo
fun binary_search_recursive(int value, int left, int right) -> int {
    if (left > right) {
        return -1;  // Not found
    }
    
    int mid = (left + right) / 2;
    int mid_value = array[mid];
    
    if (mid_value == value) {
        return mid;
    } else if (mid_value < value) {
        return binary_search_recursive(value, mid + 1, right);
    } else {
        return binary_search_recursive(value, left, mid - 1);
    }
}
```

**Tower of Hanoi:**
```algo
fun hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        print("Move disk from ");
        print(from);
        print(" to ");
        print(to);
        return;
    }
    
    hanoi(n - 1, from, aux, to);
    print("Move disk from ");
    print(from);
    print(" to ");
    print(to);
    hanoi(n - 1, aux, to, from);
}
```

### 19.4 Calling Conventions

**Register Usage:**
- **R4-R11**: First 8 function arguments
- **R1**: Return value
- **R31**: Return address (set by CALL)
- **R3**: Stack pointer

**Example with Calling Convention:**
```algo
// This function:
fun add_three(int a, int b, int c) -> int {
    return a + b + c;
}

// Compiles to assembly:
/*
add_three:
    ; R4 = a, R5 = b, R6 = c
    ADD R1, R4, R5      ; R1 = a + b
    ADD R1, R1, R6      ; R1 = R1 + c
    RET                  ; Return to caller
*/
```

**Caller's Responsibility:**
```algo
fun main() {
    int result = add_three(10, 20, 30);
    // Compiler generates:
    // MOVI R4, 10
    // MOVI R5, 20
    // MOVI R6, 30
    // CALL add_three
    // MOV R10, R1      ; Save result
}
```

### 19.5 Local Variables and Stack

**Function with Local Variables:**
```algo
fun complex_calculation(int x) -> int {
    int temp1 = x * 2;
    int temp2 = temp1 + 5;
    int result = temp2 * temp2;
    return result;
}

// Assembly (simplified):
/*
complex_calculation:
    ; Prologue: allocate stack space
    SUBI R3, R3, 24         ; Allocate 3 locals * 8 bytes
    
    ; temp1 = x * 2
    MULI R5, R4, 2          ; R5 = temp1
    STORE R5, 0(R3)
    
    ; temp2 = temp1 + 5
    ADDI R6, R5, 5          ; R6 = temp2
    STORE R6, 8(R3)
    
    ; result = temp2 * temp2
    MUL R1, R6, R6          ; R1 = result
    STORE R1, 16(R3)
    
    ; Epilogue: deallocate and return
    ADDI R3, R3, 24
    RET
*/
```

### 19.6 Advanced Function Examples

**Example 1: Euclidean Algorithm (GCD)**
```algo
fun gcd(int a, int b) -> int {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

fun lcm(int a, int b) -> int {
    return (a * b) / gcd(a, b);
}
```

**Example 2: Power with Optimization**
```algo
// Fast exponentiation using repeated squaring
fun power_fast(int base, int exp) -> int {
    if (exp == 0) {
        return 1;
    }
    
    if (exp % 2 == 0) {
        int half = power_fast(base, exp / 2);
        return half * half;
    } else {
        return base * power_fast(base, exp - 1);
    }
}
```

**Example 3: Ackermann Function**
```algo
fun ackermann(int m, int n) -> int {
    if (m == 0) {
        return n + 1;
    }
    if (n == 0) {
        return ackermann(m - 1, 1);
    }
    return ackermann(m - 1, ackermann(m, n - 1));
}
```

---

## Chapter 20: Arrays and Pointers

### 20.1 Array Declaration

**Static Arrays:**
```algo
// Global array (in .data section)
int numbers[10];

fun main() {
    int i;
    for (i = 0; i < 10; i = i + 1) {
        numbers[i] = i * i;
    }
}
```

**Array Initialization:**
```algo
int primes[5] = {2, 3, 5, 7, 11};

fun main() {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        print(primes[i]);
    }
}
```

### 20.2 Array Access

**Reading from Array:**
```algo
fun main() {
    int values[5] = {10, 20, 30, 40, 50};
    
    int first = values[0];      // 10
    int third = values[2];      // 30
    int last = values[4];       // 50
    
    print(first);
    print(third);
    print(last);
}
```

**Writing to Array:**
```algo
fun main() {
    int data[100];
    
    int i;
    for (i = 0; i < 100; i = i + 1) {
        data[i] = i * 2;
    }
}
```

### 20.3 Multidimensional Arrays

**2D Array:**
```algo
int matrix[3][3];

fun init_matrix() {
    int i;
    int j;
    
    for (i = 0; i < 3; i = i + 1) {
        for (j = 0; j < 3; j = j + 1) {
            matrix[i][j] = i * 3 + j;
        }
    }
}

fun print_matrix() {
    int i;
    int j;
    
    for (i = 0; i < 3; i = i + 1) {
        for (j = 0; j < 3; j = j + 1) {
            print(matrix[i][j]);
            print(" ");
        }
        print("\\n");
    }
}
```

**Matrix Multiplication:**
```algo
int A[2][2];
int B[2][2];
int C[2][2];

fun matrix_multiply() {
    int i;
    int j;
    int k;
    
    for (i = 0; i < 2; i = i + 1) {
        for (j = 0; j < 2; j = j + 1) {
            C[i][j] = 0;
            for (k = 0; k < 2; k = k + 1) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}
```

### 20.4 Pointer Basics

**Pointer Declaration:**
```algo
int *ptr;       // Pointer to int

fun main() {
    int value = 42;
    ptr = &value;       // ptr points to value
    
    int x = *ptr;       // x = 42 (dereference)
    *ptr = 100;         // value = 100
}
```

**Pointer Arithmetic:**
```algo
fun main() {
    int array[10];
    int *ptr = &array[0];
    
    *ptr = 1;           // array[0] = 1
    *(ptr + 1) = 2;     // array[1] = 2
    *(ptr + 2) = 3;     // array[2] = 3
}
```

### 20.5 Arrays and Functions

**Passing Array to Function:**
```algo
fun sum_array(int *arr, int size) -> int {
    int sum = 0;
    int i;
    
    for (i = 0; i < size; i = i + 1) {
        sum = sum + arr[i];
    }
    
    return sum;
}

fun main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    int total = sum_array(numbers, 5);
    print(total);  // 15
}
```

**Modifying Array in Function:**
```algo
fun double_values(int *arr, int size) {
    int i;
    for (i = 0; i < size; i = i + 1) {
        arr[i] = arr[i] * 2;
    }
}

fun main() {
    int data[3] = {1, 2, 3};
    double_values(data, 3);
    // data is now {2, 4, 6}
}
```

### 20.6 Advanced Array Examples

**Example 1: Bubble Sort**
```algo
fun bubble_sort(int *arr, int n) {
    int i;
    int j;
    
    for (i = 0; i < n - 1; i = i + 1) {
        for (j = 0; j < n - i - 1; j = j + 1) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
```

**Example 2: Linear Search**
```algo
fun linear_search(int *arr, int n, int target) -> int {
    int i;
    for (i = 0; i < n; i = i + 1) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;  // Not found
}
```

**Example 3: Array Reverse**
```algo
fun reverse_array(int *arr, int n) {
    int left = 0;
    int right = n - 1;
    
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        
        left = left + 1;
        right = right - 1;
    }
}
```

---

## Chapter 21: Structures (Future Feature)

### 21.1 Structure Definition

**Basic Structure:**
```algo
struct Point {
    int x;
    int y;
};

fun main() {
    struct Point p;
    p.x = 10;
    p.y = 20;
    
    print(p.x);
    print(p.y);
}
```

**Nested Structures:**
```algo
struct Date {
    int day;
    int month;
    int year;
};

struct Person {
    int age;
    struct Date birthday;
};

fun main() {
    struct Person john;
    john.age = 25;
    john.birthday.day = 15;
    john.birthday.month = 3;
    john.birthday.year = 1998;
}
```

### 21.2 Structure Functions

**Functions with Structures:**
```algo
struct Rectangle {
    int width;
    int height;
};

fun area(struct Rectangle *rect) -> int {
    return rect->width * rect->height;
}

fun perimeter(struct Rectangle *rect) -> int {
    return 2 * (rect->width + rect->height);
}
```

### 21.3 Memory Layout

**Structure in Memory:**
```
struct Point {
    int x;      // Offset 0, size 8
    int y;      // Offset 8, size 8
};              // Total size: 16 bytes

struct Person {
    int age;    // Offset 0, size 8
    char name;  // Offset 8, size 1
    // Padding: 7 bytes
    int id;     // Offset 16, size 8
};              // Total size: 24 bytes
```

---

## Chapter 22: Standard Library Functions

### 22.1 I/O Functions

**Print Functions:**
```algo
fun print(int value);          // Print integer
fun print(char value);         // Print character
fun print(bool value);         // Print boolean
```

**Input Functions:**
```algo
fun read_int() -> int;         // Read integer from stdin
fun read_char() -> char;       // Read character from stdin
```

### 22.2 String Functions

**String Operations:**
```algo
fun strlen(char *str) -> int;                      // String length
fun strcpy(char *dest, char *src);                 // String copy
fun strcmp(char *s1, char *s2) -> int;            // String compare
fun strcat(char *dest, char *src);                // String concatenate
```

**Example Usage:**
```algo
fun main() {
    char buffer[100];
    char *hello = "Hello";
    
    strcpy(buffer, hello);
    int len = strlen(buffer);
    print(len);  // 5
}
```

### 22.3 Math Functions

**Mathematical Operations:**
```algo
fun abs(int x) -> int;         // Absolute value
fun min(int a, int b) -> int;  // Minimum
fun max(int a, int b) -> int;  // Maximum
fun sqrt(int x) -> int;        // Integer square root
```

**Example Implementations:**
```algo
fun abs(int x) -> int {
    if (x < 0) {
        return -x;
    }
    return x;
}

fun min(int a, int b) -> int {
    if (a < b) {
        return a;
    }
    return b;
}

fun max(int a, int b) -> int {
    if (a > b) {
        return a;
    }
    return b;
}

fun sqrt(int x) -> int {
    if (x <= 0) {
        return 0;
    }
    
    int guess = x / 2;
    while (guess * guess > x) {
        guess = (guess + x / guess) / 2;
    }
    
    return guess;
}
```

### 22.4 Memory Functions

**Dynamic Memory:**
```algo
fun malloc(int size) -> int*;  // Allocate memory
fun free(int *ptr);            // Free memory
```

**Example:**
```algo
fun main() {
    int *array = malloc(10 * sizeof(int));
    
    int i;
    for (i = 0; i < 10; i = i + 1) {
        array[i] = i;
    }
    
    free(array);
}
```

---

## Chapter 23: Complete Algo Programs

### 23.1 Prime Number Generator

```algo
fun is_prime(int n) -> bool {
    if (n <= 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    
    int i;
    for (i = 3; i * i <= n; i = i + 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

fun print_primes(int limit) {
    print("Prime numbers up to ");
    print(limit);
    print(":\\n");
    
    int count = 0;
    int n;
    for (n = 2; n <= limit; n = n + 1) {
        if (is_prime(n)) {
            print(n);
            print(" ");
            count = count + 1;
            
            if (count % 10 == 0) {
                print("\\n");
            }
        }
    }
    
    print("\\nTotal: ");
    print(count);
    print(" primes\\n");
}

fun main() {
    print_primes(100);
}
```

### 23.2 Sorting Algorithms

**Quick Sort:**
```algo
int array[100];

fun partition(int low, int high) -> int {
    int pivot = array[high];
    int i = low - 1;
    int j;
    
    for (j = low; j < high; j = j + 1) {
        if (array[j] <= pivot) {
            i = i + 1;
            
            // Swap array[i] and array[j]
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    
    // Swap array[i+1] and array[high]
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    
    return i + 1;
}

fun quicksort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quicksort(low, pi - 1);
        quicksort(pi + 1, high);
    }
}

fun main() {
    int n = 10;
    int i;
    
    // Fill with reverse sorted data
    for (i = 0; i < n; i = i + 1) {
        array[i] = n - i;
    }
    
    print("Before sorting:\\n");
    for (i = 0; i < n; i = i + 1) {
        print(array[i]);
        print(" ");
    }
    
    quicksort(0, n - 1);
    
    print("\\nAfter sorting:\\n");
    for (i = 0; i < n; i = i + 1) {
        print(array[i]);
        print(" ");
    }
}
```

### 23.3 Calculator Program

```algo
fun add_op(int a, int b) -> int { return a + b; }
fun sub_op(int a, int b) -> int { return a - b; }
fun mul_op(int a, int b) -> int { return a * b; }
fun div_op(int a, int b) -> int { 
    if (b == 0) {
        print("Error: Division by zero\\n");
        return 0;
    }
    return a / b; 
}

fun calculator() {
    while (true) {
        print("\\nSimple Calculator\\n");
        print("1. Add\\n");
        print("2. Subtract\\n");
        print("3. Multiply\\n");
        print("4. Divide\\n");
        print("5. Exit\\n");
        print("Enter choice: ");
        
        int choice = read_int();
        
        if (choice == 5) {
            print("Goodbye!\\n");
            return;
        }
        
        if (choice < 1 || choice > 4) {
            print("Invalid choice\\n");
            continue;
        }
        
        print("Enter first number: ");
        int a = read_int();
        
        print("Enter second number: ");
        int b = read_int();
        
        int result;
        
        if (choice == 1) {
            result = add_op(a, b);
        } else if (choice == 2) {
            result = sub_op(a, b);
        } else if (choice == 3) {
            result = mul_op(a, b);
        } else if (choice == 4) {
            result = div_op(a, b);
        }
        
        print("Result: ");
        print(result);
        print("\\n");
    }
}

fun main() {
    calculator();
}
```

### 23.4 Number Guessing Game

```algo
fun random(int max) -> int {
    // Simple LCG pseudorandom number generator
    int seed = 12345;
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed % max;
}

fun guessing_game() {
    int secret = random(100) + 1;  // 1 to 100
    int attempts = 0;
    int max_attempts = 7;
    
    print("I'm thinking of a number between 1 and 100\\n");
    print("You have ");
    print(max_attempts);
    print(" attempts to guess it.\\n\\n");
    
    while (attempts < max_attempts) {
        print("Attempt ");
        print(attempts + 1);
        print("/");
        print(max_attempts);
        print(" - Enter your guess: ");
        
        int guess = read_int();
        attempts = attempts + 1;
        
        if (guess == secret) {
            print("Congratulations! You guessed it in ");
            print(attempts);
            print(" attempts!\\n");
            return;
        } else if (guess < secret) {
            print("Too low!\\n");
        } else {
            print("Too high!\\n");
        }
    }
    
    print("Sorry! You've run out of attempts.\\n");
    print("The number was ");
    print(secret);
    print("\\n");
}

fun main() {
    guessing_game();
}
```

---

# PART V: COMPILER IMPLEMENTATION

---

## Chapter 24: Compiler Architecture

### 24.1 Compiler Overview

The Algo compiler transforms high-level Algo code into A1M assembly language through several phases:

**Compilation Phases:**
```
Source Code (.algo)
       ↓
   Lexical Analysis (Lexer)
       ↓
   Token Stream
       ↓
   Syntax Analysis (Parser)
       ↓
   Abstract Syntax Tree (AST)
       ↓
   Semantic Analysis
       ↓
   Intermediate Representation (IR)
       ↓
   Code Generation
       ↓
   Assembly Code (.asm)
       ↓
   Assembler
       ↓
   Machine Code (.bin)
```

### 24.2 Compiler Structure

**Main Compiler Components:**
```c
// compiler/src/main.c

#include "lexer.h"
#include "parser.h"
#include "codegen.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input.algo>\n", argv[0]);
        return 1;
    }
    
    // Phase 1: Lexical Analysis
    Lexer *lexer = lexer_create(argv[1]);
    if (!lexer) {
        fprintf(stderr, "Cannot open file: %s\n", argv[1]);
        return 1;
    }
    
    // Phase 2: Parsing
    Parser *parser = parser_create(lexer);
    ASTNode *ast = parser_parse(parser);
    
    if (parser->error_count > 0) {
        fprintf(stderr, "Parsing failed with %d errors\n", 
                parser->error_count);
        return 1;
    }
    
    // Phase 3: Code Generation
    CodeGenerator *codegen = codegen_create();
    codegen_generate(codegen, ast);
    
    // Output assembly code
    char output_file[256];
    snprintf(output_file, sizeof(output_file), "%s.asm", argv[1]);
    codegen_write_output(codegen, output_file);
    
    // Cleanup
    lexer_destroy(lexer);
    parser_destroy(parser);
    codegen_destroy(codegen);
    ast_destroy(ast);
    
    printf("Compilation successful: %s -> %s\n", argv[1], output_file);
    
    return 0;
}
```

### 24.3 Data Structures

**Abstract Syntax Tree Node:**
```c
typedef enum {
    AST_PROGRAM,
    AST_FUNCTION,
    AST_VARIABLE_DECL,
    AST_ASSIGNMENT,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_LITERAL,
    AST_IDENTIFIER,
    AST_FUNCTION_CALL,
    AST_IF_STATEMENT,
    AST_WHILE_LOOP,
    AST_FOR_LOOP,
    AST_RETURN,
    AST_BLOCK
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    
    union {
        // Literals
        int64_t int_value;
        char char_value;
        int bool_value;
        
        // Identifiers
        char *name;
        
        // Binary operations
        struct {
            TokenType op;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary_op;
        
        // Function definition
        struct {
            char *name;
            struct ASTNode **parameters;
            int param_count;
            struct ASTNode *body;
            DataType return_type;
        } function;
        
        // Variable declaration
        struct {
            char *name;
            DataType type;
            struct ASTNode *initializer;
        } var_decl;
        
        // Control structures
        struct {
            struct ASTNode *condition;
            struct ASTNode *then_branch;
            struct ASTNode *else_branch;
        } if_stmt;
        
        // Statements list
        struct {
            struct ASTNode **statements;
            int count;
        } block;
    } data;
    
    int line_number;
    struct ASTNode *next;  // For linked lists
} ASTNode;
```

**Symbol Table:**
```c
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_PARAMETER
} SymbolType;

typedef struct Symbol {
    char name[64];
    SymbolType type;
    DataType data_type;
    int offset;         // Stack offset for locals
    int register_num;   // Assigned register
    int scope_level;
    struct Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *symbols;
    int scope_level;
    struct SymbolTable *parent;
} SymbolTable;
```

### 24.4 Error Handling

**Error Reporting:**
```c
typedef struct {
    char message[256];
    int line_number;
    int column;
} CompileError;

void report_error(Parser *parser, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    fprintf(stderr, "Error at line %d: ", parser->current_token.line);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    
    va_end(args);
    parser->error_count++;
}

void report_warning(Parser *parser, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    fprintf(stderr, "Warning at line %d: ", parser->current_token.line);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    
    va_end(args);
}
```

### 24.5 Optimization Phases (Future)

**Planned Optimizations:**
- Constant folding
- Dead code elimination
- Register allocation optimization
- Tail call optimization
- Loop unrolling
- Peephole optimization

**Example - Constant Folding:**
```c
ASTNode *optimize_constant_folding(ASTNode *node) {
    if (node->type == AST_BINARY_OP) {
        // If both operands are constants
        if (node->data.binary_op.left->type == AST_LITERAL &&
            node->data.binary_op.right->type == AST_LITERAL) {
            
            int64_t left = node->data.binary_op.left->data.int_value;
            int64_t right = node->data.binary_op.right->data.int_value;
            int64_t result;
            
            switch (node->data.binary_op.op) {
                case TOKEN_PLUS:
                    result = left + right;
                    break;
                case TOKEN_MINUS:
                    result = left - right;
                    break;
                case TOKEN_STAR:
                    result = left * right;
                    break;
                // ... other operators
            }
            
            // Replace binary op with constant
            ASTNode *constant = ast_create_literal_int(result);
            ast_destroy(node);
            return constant;
        }
    }
    
    return node;
}
```

---

## Chapter 25: Lexical Analysis

### 25.1 Lexer Implementation

**Token Definition:**
```c
// compiler/src/lexer.h

typedef enum {
    TOKEN_EOF,
    TOKEN_ERROR,
    
    // Literals
    TOKEN_INT_LITERAL,
    TOKEN_CHAR_LITERAL,
    TOKEN_STRING_LITERAL,
    TOKEN_TRUE,
    TOKEN_FALSE,
    
    // Identifiers and Keywords
    TOKEN_IDENTIFIER,
    TOKEN_FUN,
    TOKEN_RETURN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_INT,
    TOKEN_BOOL,
    TOKEN_CHAR,
    TOKEN_LONG,
    
    // Operators
    TOKEN_PLUS,         // +
    TOKEN_MINUS,        // -
    TOKEN_STAR,         // *
    TOKEN_SLASH,        // /
    TOKEN_PERCENT,      // %
    TOKEN_AMPERSAND,    // &
    TOKEN_PIPE,         // |
    TOKEN_CARET,        // ^
    TOKEN_TILDE,        // ~
    TOKEN_LSHIFT,       // <<
    TOKEN_RSHIFT,       // >>
    
    // Comparison
    TOKEN_EQ,           // ==
    TOKEN_NEQ,          // !=
    TOKEN_LT,           // <
    TOKEN_GT,           // >
    TOKEN_LE,           // <=
    TOKEN_GE,           // >=
    
    // Logical
    TOKEN_AND,          // &&
    TOKEN_OR,           // ||
    TOKEN_NOT,          // !
    
    // Assignment
    TOKEN_ASSIGN,       // =
    TOKEN_PLUS_ASSIGN,  // +=
    TOKEN_MINUS_ASSIGN, // -=
    
    // Delimiters
    TOKEN_LPAREN,       // (
    TOKEN_RPAREN,       // )
    TOKEN_LBRACE,       // {
    TOKEN_RBRACE,       // }
    TOKEN_LBRACKET,     // [
    TOKEN_RBRACKET,     // ]
    TOKEN_COMMA,        // ,
    TOKEN_SEMICOLON,    // ;
    TOKEN_ARROW,        // ->
    TOKEN_DOT           // .
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[256];
    int line;
    int column;
    
    union {
        int64_t int_value;
        char char_value;
        char *string_value;
    } value;
} Token;
```

**Lexer Structure:**
```c
typedef struct {
    const char *source;
    const char *current;
    int line;
    int column;
    FILE *file;
} Lexer;

Lexer *lexer_create(const char *filename) {
    Lexer *lexer = malloc(sizeof(Lexer));
    
    lexer->file = fopen(filename, "r");
    if (!lexer->file) {
        free(lexer);
        return NULL;
    }
    
    // Read entire file
    fseek(lexer->file, 0, SEEK_END);
    long size = ftell(lexer->file);
    fseek(lexer->file, 0, SEEK_SET);
    
    char *source = malloc(size + 1);
    fread(source, 1, size, lexer->file);
    source[size] = '\0';
    
    lexer->source = source;
    lexer->current = source;
    lexer->line = 1;
    lexer->column = 1;
    
    return lexer;
}
```

### 25.2 Token Recognition

**Get Next Token:**
```c
Token lexer_next_token(Lexer *lexer) {
    Token token;
    
    // Skip whitespace and comments
    skip_whitespace(lexer);
    
    if (*lexer->current == '\0') {
        token.type = TOKEN_EOF;
        return token;
    }
    
    token.line = lexer->line;
    token.column = lexer->column;
    
    // Numbers
    if (isdigit(*lexer->current)) {
        return scan_number(lexer);
    }
    
    // Identifiers and keywords
    if (isalpha(*lexer->current) || *lexer->current == '_') {
        return scan_identifier(lexer);
    }
    
    // String literals
    if (*lexer->current == '"') {
        return scan_string(lexer);
    }
    
    // Character literals
    if (*lexer->current == '\'') {
        return scan_char(lexer);
    }
    
    // Operators and punctuation
    return scan_operator(lexer);
}
```

**Scan Number:**
```c
Token scan_number(Lexer *lexer) {
    Token token;
    token.type = TOKEN_INT_LITERAL;
    token.line = lexer->line;
    
    const char *start = lexer->current;
    int64_t value = 0;
    int base = 10;
    
    // Check for hex (0x) or binary (0b)
    if (*lexer->current == '0') {
        lexer->current++;
        lexer->column++;
        
        if (*lexer->current == 'x' || *lexer->current == 'X') {
            base = 16;
            lexer->current++;
            lexer->column++;
        } else if (*lexer->current == 'b' || *lexer->current == 'B') {
            base = 2;
            lexer->current++;
            lexer->column++;
        } else {
            value = 0;
        }
    }
    
    // Parse digits
    while (1) {
        int digit_value = -1;
        char c = *lexer->current;
        
        if (c >= '0' && c <= '9') {
            digit_value = c - '0';
        } else if (base == 16 && c >= 'a' && c <= 'f') {
            digit_value = c - 'a' + 10;
        } else if (base == 16 && c >= 'A' && c <= 'F') {
            digit_value = c - 'A' + 10;
        } else {
            break;
        }
        
        if (digit_value >= base) break;
        
        value = value * base + digit_value;
        lexer->current++;
        lexer->column++;
    }
    
    token.value.int_value = value;
    snprintf(token.lexeme, sizeof(token.lexeme), "%.*s", 
             (int)(lexer->current - start), start);
    
    return token;
}
```

**Scan Identifier:**
```c
Token scan_identifier(Lexer *lexer) {
    Token token;
    const char *start = lexer->current;
    
    // Read identifier characters
    while (isalnum(*lexer->current) || *lexer->current == '_') {
        lexer->current++;
        lexer->column++;
    }
    
    // Extract lexeme
    int length = lexer->current - start;
    snprintf(token.lexeme, sizeof(token.lexeme), "%.*s", length, start);
    
    // Check if it's a keyword
    token.type = check_keyword(token.lexeme);
    token.line = lexer->line;
    
    return token;
}

TokenType check_keyword(const char *lexeme) {
    struct {
        const char *keyword;
        TokenType type;
    } keywords[] = {
        {"fun", TOKEN_FUN},
        {"return", TOKEN_RETURN},
        {"if", TOKEN_IF},
        {"else", TOKEN_ELSE},
        {"while", TOKEN_WHILE},
        {"for", TOKEN_FOR},
        {"int", TOKEN_INT},
        {"bool", TOKEN_BOOL},
        {"char", TOKEN_CHAR},
        {"long", TOKEN_LONG},
        {"true", TOKEN_TRUE},
        {"false", TOKEN_FALSE},
        {NULL, TOKEN_IDENTIFIER}
    };
    
    for (int i = 0; keywords[i].keyword != NULL; i++) {
        if (strcmp(lexeme, keywords[i].keyword) == 0) {
            return keywords[i].type;
        }
    }
    
    return TOKEN_IDENTIFIER;
}
```

### 25.3 String and Character Handling

**Scan String:**
```c
Token scan_string(Lexer *lexer) {
    Token token;
    token.type = TOKEN_STRING_LITERAL;
    token.line = lexer->line;
    
    lexer->current++;  // Skip opening "
    lexer->column++;
    
    char buffer[1024];
    int i = 0;
    
    while (*lexer->current != '"' && *lexer->current != '\0') {
        if (*lexer->current == '\\') {
            // Escape sequence
            lexer->current++;
            lexer->column++;
            
            switch (*lexer->current) {
                case 'n': buffer[i++] = '\n'; break;
                case 't': buffer[i++] = '\t'; break;
                case 'r': buffer[i++] = '\r'; break;
                case '\\': buffer[i++] = '\\'; break;
                case '"': buffer[i++] = '"'; break;
                case '0': buffer[i++] = '\0'; break;
                default:
                    buffer[i++] = *lexer->current;
            }
        } else {
            buffer[i++] = *lexer->current;
        }
        
        lexer->current++;
        lexer->column++;
    }
    
    buffer[i] = '\0';
    
    if (*lexer->current == '"') {
        lexer->current++;
        lexer->column++;
    }
    
    token.value.string_value = strdup(buffer);
    strcpy(token.lexeme, buffer);
    
    return token;
}
```

---

## Chapter 26: Syntax Analysis (Parser)

### 26.1 Recursive Descent Parser

**Parser Structure:**
```c
typedef struct {
    Lexer *lexer;
    Token current_token;
    Token peek_token;
    int error_count;
    SymbolTable *symbol_table;
} Parser;

Parser *parser_create(Lexer *lexer) {
    Parser *parser = malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->error_count = 0;
    parser->symbol_table = symbol_table_create();
    
    // Prime the parser with first two tokens
    parser->current_token = lexer_next_token(lexer);
    parser->peek_token = lexer_next_token(lexer);
    
    return parser;
}
```

**Token Management:**
```c
void advance(Parser *parser) {
    parser->current_token = parser->peek_token;
    parser->peek_token = lexer_next_token(parser->lexer);
}

int match(Parser *parser, TokenType type) {
    if (parser->current_token.type == type) {
        advance(parser);
        return 1;
    }
    return 0;
}

void expect(Parser *parser, TokenType type) {
    if (parser->current_token.type != type) {
        report_error(parser, "Expected token type %d, got %d", 
                     type, parser->current_token.type);
    }
    advance(parser);
}
```

### 26.2 Parsing Functions

**Parse Program:**
```c
ASTNode *parser_parse(Parser *parser) {
    ASTNode *program = ast_create_program();
    
    while (parser->current_token.type != TOKEN_EOF) {
        ASTNode *decl = parse_declaration(parser);
        if (decl) {
            ast_add_child(program, decl);
        }
    }
    
    return program;
}
```

**Parse Declaration:**
```c
ASTNode *parse_declaration(Parser *parser) {
    if (parser->current_token.type == TOKEN_FUN) {
        return parse_function(parser);
    } else if (is_type_keyword(parser->current_token.type)) {
        return parse_variable_declaration(parser);
    } else {
        report_error(parser, "Expected declaration");
        advance(parser);
        return NULL;
    }
}
```

**Parse Function:**
```c
ASTNode *parse_function(Parser *parser) {
    expect(parser, TOKEN_FUN);
    
    ASTNode *func = ast_create_function();
    
    // Function name
    if (parser->current_token.type != TOKEN_IDENTIFIER) {
        report_error(parser, "Expected function name");
        return NULL;
    }
    func->data.function.name = strdup(parser->current_token.lexeme);
    advance(parser);
    
    // Parameters
    expect(parser, TOKEN_LPAREN);
    
    func->data.function.parameters = NULL;
    func->data.function.param_count = 0;
    
    if (parser->current_token.type != TOKEN_RPAREN) {
        do {
            ASTNode *param = parse_parameter(parser);
            func->data.function.param_count++;
            // Add to parameter list...
        } while (match(parser, TOKEN_COMMA));
    }
    
    expect(parser, TOKEN_RPAREN);
    
    // Return type
    if (match(parser, TOKEN_ARROW)) {
        func->data.function.return_type = parse_type(parser);
    } else {
        func->data.function.return_type = TYPE_VOID;
    }
    
    // Function body
    func->data.function.body = parse_block(parser);
    
    return func;
}
```

**Parse Statement:**
```c
ASTNode *parse_statement(Parser *parser) {
    switch (parser->current_token.type) {
        case TOKEN_IF:
            return parse_if_statement(parser);
        case TOKEN_WHILE:
            return parse_while_statement(parser);
        case TOKEN_FOR:
            return parse_for_statement(parser);
        case TOKEN_RETURN:
            return parse_return_statement(parser);
        case TOKEN_LBRACE:
            return parse_block(parser);
        case TOKEN_INT:
        case TOKEN_BOOL:
        case TOKEN_CHAR:
            return parse_variable_declaration(parser);
        default:
            return parse_expression_statement(parser);
    }
}
```

**Parse If Statement:**
```c
ASTNode *parse_if_statement(Parser *parser) {
    expect(parser, TOKEN_IF);
    
    ASTNode *if_stmt = ast_create_if();
    
    expect(parser, TOKEN_LPAREN);
    if_stmt->data.if_stmt.condition = parse_expression(parser);
    expect(parser, TOKEN_RPAREN);
    
    if_stmt->data.if_stmt.then_branch = parse_statement(parser);
    
    if (match(parser, TOKEN_ELSE)) {
        if_stmt->data.if_stmt.else_branch = parse_statement(parser);
    } else {
        if_stmt->data.if_stmt.else_branch = NULL;
    }
    
    return if_stmt;
}
```

### 26.3 Expression Parsing

**Parse Expression (Precedence Climbing):**
```c
ASTNode *parse_expression(Parser *parser) {
    return parse_assignment(parser);
}

ASTNode *parse_assignment(Parser *parser) {
    ASTNode *expr = parse_logical_or(parser);
    
    if (match(parser, TOKEN_ASSIGN)) {
        ASTNode *value = parse_assignment(parser);
        return ast_create_assignment(expr, value);
    }
    
    return expr;
}

ASTNode *parse_logical_or(Parser *parser) {
    ASTNode *left = parse_logical_and(parser);
    
    while (match(parser, TOKEN_OR)) {
        Token op = parser->current_token;
        ASTNode *right = parse_logical_and(parser);
        left = ast_create_binary_op(op.type, left, right);
    }
    
    return left;
}

ASTNode *parse_logical_and(Parser *parser) {
    ASTNode *left = parse_equality(parser);
    
    while (match(parser, TOKEN_AND)) {
        Token op = parser->current_token;
        ASTNode *right = parse_equality(parser);
        left = ast_create_binary_op(op.type, left, right);
    }
    
    return left;
}

ASTNode *parse_equality(Parser *parser) {
    ASTNode *left = parse_comparison(parser);
    
    while (parser->current_token.type == TOKEN_EQ ||
           parser->current_token.type == TOKEN_NEQ) {
        TokenType op = parser->current_token.type;
        advance(parser);
        ASTNode *right = parse_comparison(parser);
        left = ast_create_binary_op(op, left, right);
    }
    
    return left;
}

ASTNode *parse_comparison(Parser *parser) {
    ASTNode *left = parse_addition(parser);
    
    while (parser->current_token.type == TOKEN_LT ||
           parser->current_token.type == TOKEN_GT ||
           parser->current_token.type == TOKEN_LE ||
           parser->current_token.type == TOKEN_GE) {
        TokenType op = parser->current_token.type;
        advance(parser);
        ASTNode *right = parse_addition(parser);
        left = ast_create_binary_op(op, left, right);
    }
    
    return left;
}

ASTNode *parse_addition(Parser *parser) {
    ASTNode *left = parse_multiplication(parser);
    
    while (parser->current_token.type == TOKEN_PLUS ||
           parser->current_token.type == TOKEN_MINUS) {
        TokenType op = parser->current_token.type;
        advance(parser);
        ASTNode *right = parse_multiplication(parser);
        left = ast_create_binary_op(op, left, right);
    }
    
    return left;
}

ASTNode *parse_multiplication(Parser *parser) {
    ASTNode *left = parse_unary(parser);
    
    while (parser->current_token.type == TOKEN_STAR ||
           parser->current_token.type == TOKEN_SLASH ||
           parser->current_token.type == TOKEN_PERCENT) {
        TokenType op = parser->current_token.type;
        advance(parser);
        ASTNode *right = parse_unary(parser);
        left = ast_create_binary_op(op, left, right);
    }
    
    return left;
}

ASTNode *parse_unary(Parser *parser) {
    if (parser->current_token.type == TOKEN_NOT ||
        parser->current_token.type == TOKEN_MINUS ||
        parser->current_token.type == TOKEN_TILDE) {
        TokenType op = parser->current_token.type;
        advance(parser);
        ASTNode *operand = parse_unary(parser);
        return ast_create_unary_op(op, operand);
    }
    
    return parse_postfix(parser);
}

ASTNode *parse_postfix(Parser *parser) {
    ASTNode *expr = parse_primary(parser);
    
    while (1) {
        if (match(parser, TOKEN_LPAREN)) {
            // Function call
            expr = parse_function_call(parser, expr);
        } else if (match(parser, TOKEN_LBRACKET)) {
            // Array subscript
            ASTNode *index = parse_expression(parser);
            expect(parser, TOKEN_RBRACKET);
            expr = ast_create_array_access(expr, index);
        } else {
            break;
        }
    }
    
    return expr;
}

ASTNode *parse_primary(Parser *parser) {
    // Integer literal
    if (parser->current_token.type == TOKEN_INT_LITERAL) {
        int64_t value = parser->current_token.value.int_value;
        advance(parser);
        return ast_create_literal_int(value);
    }
    
    // Boolean literal
    if (parser->current_token.type == TOKEN_TRUE) {
        advance(parser);
        return ast_create_literal_bool(1);
    }
    if (parser->current_token.type == TOKEN_FALSE) {
        advance(parser);
        return ast_create_literal_bool(0);
    }
    
    // Character literal
    if (parser->current_token.type == TOKEN_CHAR_LITERAL) {
        char value = parser->current_token.value.char_value;
        advance(parser);
        return ast_create_literal_char(value);
    }
    
    // Identifier
    if (parser->current_token.type == TOKEN_IDENTIFIER) {
        char *name = strdup(parser->current_token.lexeme);
        advance(parser);
        return ast_create_identifier(name);
    }
    
    // Parenthesized expression
    if (match(parser, TOKEN_LPAREN)) {
        ASTNode *expr = parse_expression(parser);
        expect(parser, TOKEN_RPAREN);
        return expr;
    }
    
    report_error(parser, "Expected expression");
    return NULL;
}
```

---

## Chapter 27: Semantic Analysis

### 27.1 Type Checking

**Type System:**
```c
typedef enum {
    TYPE_VOID,
    TYPE_INT,
    TYPE_BOOL,
    TYPE_CHAR,
    TYPE_LONG,
    TYPE_POINTER,
    TYPE_ARRAY,
    TYPE_FUNCTION
} DataType;

typedef struct TypeInfo {
    DataType base_type;
    struct TypeInfo *element_type;  // For arrays/pointers
    int array_size;
} TypeInfo;
```

**Type Checker:**
```c
TypeInfo *check_expression_type(ASTNode *expr, SymbolTable *symtab) {
    switch (expr->type) {
        case AST_LITERAL:
            if (expr->data.int_value != 0) {
                return type_create(TYPE_INT);
            }
            break;
            
        case AST_IDENTIFIER: {
            Symbol *sym = symbol_table_lookup(symtab, expr->data.name);
            if (!sym) {
                error("Undefined variable: %s", expr->data.name);
                return type_create(TYPE_VOID);
            }
            return type_copy(sym->data_type);
        }
        
        case AST_BINARY_OP: {
            TypeInfo *left = check_expression_type(
                expr->data.binary_op.left, symtab);
            TypeInfo *right = check_expression_type(
                expr->data.binary_op.right, symtab);
            
            // Check type compatibility
            if (!types_compatible(left, right)) {
                error("Type mismatch in binary operation");
            }
            
            return type_create(TYPE_INT);  // Simplified
        }
    }
    
    return type_create(TYPE_VOID);
}
```

### 27.2 Symbol Table Management

**Symbol Table Operations:**
```c
SymbolTable *symbol_table_create() {
    SymbolTable *table = malloc(sizeof(SymbolTable));
    table->symbols = NULL;
    table->scope_level = 0;
    table->parent = NULL;
    return table;
}

void symbol_table_enter_scope(SymbolTable *table) {
    SymbolTable *new_scope = symbol_table_create();
    new_scope->parent = table;
    new_scope->scope_level = table->scope_level + 1;
    // Set as current scope...
}

void symbol_table_exit_scope(SymbolTable *table) {
    // Return to parent scope...
}

Symbol *symbol_table_lookup(SymbolTable *table, const char *name) {
    // Search current scope
    Symbol *sym = table->symbols;
    while (sym) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
        sym = sym->next;
    }
    
    // Search parent scopes
    if (table->parent) {
        return symbol_table_lookup(table->parent, name);
    }
    
    return NULL;
}

void symbol_table_insert(SymbolTable *table, Symbol *symbol) {
    symbol->next = table->symbols;
    table->symbols = symbol;
    symbol->scope_level = table->scope_level;
}
```

### 27.3 Semantic Checks

**Variable Declaration Check:**
```c
void check_variable_declaration(ASTNode *decl, SymbolTable *symtab) {
    const char *name = decl->data.var_decl.name;
    
    // Check if already declared in current scope
    Symbol *existing = symbol_table_lookup_current_scope(symtab, name);
    if (existing) {
        error("Variable '%s' already declared in this scope", name);
        return;
    }
    
    // Create symbol
    Symbol *sym = symbol_create(name, SYMBOL_VARIABLE);
    sym->data_type = decl->data.var_decl.type;
    
    // Check initializer type if present
    if (decl->data.var_decl.initializer) {
        TypeInfo *init_type = check_expression_type(
            decl->data.var_decl.initializer, symtab);
        
        if (!types_compatible(&sym->data_type, init_type)) {
            error("Initializer type mismatch for variable '%s'", name);
        }
    }
    
    symbol_table_insert(symtab, sym);
}
```

**Function Call Check:**
```c
void check_function_call(ASTNode *call, SymbolTable *symtab) {
    const char *func_name = call->data.function_call.name;
    
    Symbol *func = symbol_table_lookup(symtab, func_name);
    if (!func || func->type != SYMBOL_FUNCTION) {
        error("Undefined function: %s", func_name);
        return;
    }
    
    // Check argument count
    int expected = func->param_count;
    int actual = call->data.function_call.arg_count;
    
    if (expected != actual) {
        error("Function '%s' expects %d arguments, got %d",
              func_name, expected, actual);
    }
    
    // Check argument types
    for (int i = 0; i < actual && i < expected; i++) {
        TypeInfo *arg_type = check_expression_type(
            call->data.function_call.arguments[i], symtab);
        TypeInfo *param_type = &func->parameters[i].data_type;
        
        if (!types_compatible(arg_type, param_type)) {
            error("Argument %d type mismatch in call to '%s'",
                  i + 1, func_name);
        }
    }
}
```

---

## Chapter 28: Code Generation

### 28.1 Code Generator Structure

**Code Generator:**
```c
typedef struct {
    FILE *output;
    int next_register;
    int next_label;
    int stack_offset;
    SymbolTable *symbol_table;
} CodeGenerator;

CodeGenerator *codegen_create() {
    CodeGenerator *gen = malloc(sizeof(CodeGenerator));
    gen->output = NULL;
    gen->next_register = 10;  // R10-R30 for temps
    gen->next_label = 0;
    gen->stack_offset = 0;
    gen->symbol_table = NULL;
    return gen;
}
```

### 28.2 Register Allocation

**Simple Register Allocator:**
```c
int allocate_register(CodeGenerator *gen) {
    if (gen->next_register > 30) {
        // Spill to stack
        error("Register spill not implemented");
        return -1;
    }
    return gen->next_register++;
}

void free_register(CodeGenerator *gen, int reg) {
    if (reg == gen->next_register - 1) {
        gen->next_register--;
    }
}

int get_temp_register(CodeGenerator *gen) {
    return allocate_register(gen);
}
```

### 28.3 Expression Code Generation

**Generate Expression:**
```c
int codegen_expression(CodeGenerator *gen, ASTNode *expr) {
    switch (expr->type) {
        case AST_LITERAL: {
            int reg = allocate_register(gen);
            emit(gen, "    MOVI R%d, %ld", reg, expr->data.int_value);
            return reg;
        }
        
        case AST_IDENTIFIER: {
            Symbol *sym = symbol_table_lookup(gen->symbol_table, 
                                             expr->data.name);
            if (!sym) {
                error("Undefined variable: %s", expr->data.name);
                return -1;
            }
            
            int reg = allocate_register(gen);
            if (sym->type == SYMBOL_PARAMETER || 
                sym->type == SYMBOL_VARIABLE) {
                // Load from stack
                emit(gen, "    LOAD R%d, %d(R3)", reg, sym->offset);
            }
            return reg;
        }
        
        case AST_BINARY_OP: {
            int left_reg = codegen_expression(gen, 
                                             expr->data.binary_op.left);
            int right_reg = codegen_expression(gen, 
                                              expr->data.binary_op.right);
            
            int result_reg = allocate_register(gen);
            
            switch (expr->data.binary_op.op) {
                case TOKEN_PLUS:
                    emit(gen, "    ADD R%d, R%d, R%d", 
                         result_reg, left_reg, right_reg);
                    break;
                case TOKEN_MINUS:
                    emit(gen, "    SUB R%d, R%d, R%d", 
                         result_reg, left_reg, right_reg);
                    break;
                case TOKEN_STAR:
                    emit(gen, "    MUL R%d, R%d, R%d", 
                         result_reg, left_reg, right_reg);
                    break;
                case TOKEN_SLASH:
                    emit(gen, "    DIV R%d, R%d, R%d", 
                         result_reg, left_reg, right_reg);
                    break;
                // ... other operators
            }
            
            free_register(gen, left_reg);
            free_register(gen, right_reg);
            
            return result_reg;
        }
        
        case AST_FUNCTION_CALL:
            return codegen_function_call(gen, expr);
    }
    
    return -1;
}
```

### 28.4 Statement Code Generation

**Generate Statement:**
```c
void codegen_statement(CodeGenerator *gen, ASTNode *stmt) {
    switch (stmt->type) {
        case AST_VARIABLE_DECL: {
            // Allocate stack space
            gen->stack_offset -= 8;
            
            Symbol *sym = symbol_table_lookup(gen->symbol_table,
                                             stmt->data.var_decl.name);
            sym->offset = gen->stack_offset;
            
            // Generate initializer if present
            if (stmt->data.var_decl.initializer) {
                int reg = codegen_expression(gen, 
                                            stmt->data.var_decl.initializer);
                emit(gen, "    STORE R%d, %d(R3)", reg, sym->offset);
                free_register(gen, reg);
            }
            break;
        }
        
        case AST_ASSIGNMENT: {
            int value_reg = codegen_expression(gen, 
                                              stmt->data.assignment.value);
            
            Symbol *sym = symbol_table_lookup(gen->symbol_table,
                                             stmt->data.assignment.target->data.name);
            if (sym) {
                emit(gen, "    STORE R%d, %d(R3)", value_reg, sym->offset);
            }
            
            free_register(gen, value_reg);
            break;
        }
        
        case AST_IF_STATEMENT:
            codegen_if_statement(gen, stmt);
            break;
            
        case AST_WHILE_LOOP:
            codegen_while_loop(gen, stmt);
            break;
            
        case AST_RETURN:
            codegen_return(gen, stmt);
            break;
            
        case AST_BLOCK:
            for (int i = 0; i < stmt->data.block.count; i++) {
                codegen_statement(gen, stmt->data.block.statements[i]);
            }
            break;
    }
}
```

**Generate If Statement:**
```c
void codegen_if_statement(CodeGenerator *gen, ASTNode *if_stmt) {
    int else_label = gen->next_label++;
    int end_label = gen->next_label++;
    
    // Generate condition
    int cond_reg = codegen_expression(gen, if_stmt->data.if_stmt.condition);
    emit(gen, "    CMPI R%d, 0", cond_reg);
    emit(gen, "    JZ .L%d", else_label);
    free_register(gen, cond_reg);
    
    // Generate then branch
    codegen_statement(gen, if_stmt->data.if_stmt.then_branch);
    emit(gen, "    JMP .L%d", end_label);
    
    // Generate else branch
    emit(gen, ".L%d:", else_label);
    if (if_stmt->data.if_stmt.else_branch) {
        codegen_statement(gen, if_stmt->data.if_stmt.else_branch);
    }
    
    emit(gen, ".L%d:", end_label);
}
```

**Generate While Loop:**
```c
void codegen_while_loop(CodeGenerator *gen, ASTNode *while_stmt) {
    int loop_start = gen->next_label++;
    int loop_end = gen->next_label++;
    
    emit(gen, ".L%d:", loop_start);
    
    // Generate condition
    int cond_reg = codegen_expression(gen, 
                                     while_stmt->data.while_loop.condition);
    emit(gen, "    CMPI R%d, 0", cond_reg);
    emit(gen, "    JZ .L%d", loop_end);
    free_register(gen, cond_reg);
    
    // Generate body
    codegen_statement(gen, while_stmt->data.while_loop.body);
    
    emit(gen, "    JMP .L%d", loop_start);
    emit(gen, ".L%d:", loop_end);
}
```

### 28.5 Function Code Generation

**Generate Function:**
```c
void codegen_function(CodeGenerator *gen, ASTNode *func) {
    emit(gen, "\n%s:", func->data.function.name);
    
    // Prologue
    emit(gen, "    ; Function prologue");
    emit(gen, "    PUSH R31");  // Save return address
    
    // Save callee-saved registers (R10-R30)
    for (int i = 10; i <= 30; i++) {
        emit(gen, "    PUSH R%d", i);
    }
    
    // Allocate stack space for locals
    int local_space = calculate_local_space(func);
    if (local_space > 0) {
        emit(gen, "    SUBI R3, R3, %d", local_space);
    }
    
    gen->stack_offset = 0;
    
    // Generate function body
    codegen_statement(gen, func->data.function.body);
    
    // Epilogue (if no explicit return)
    emit(gen, "\n%s_exit:", func->data.function.name);
    
    // Deallocate locals
    if (local_space > 0) {
        emit(gen, "    ADDI R3, R3, %d", local_space);
    }
    
    // Restore callee-saved registers
    for (int i = 30; i >= 10; i--) {
        emit(gen, "    POP R%d", i);
    }
    
    emit(gen, "    POP R31");   // Restore return address
    emit(gen, "    RET");
}
```

---

# PART VI: COMPILATION PROCESS

---

## Chapter 29: Building the Toolchain

### 29.1 Build System

**Makefile Structure:**
```makefile
# Top-level Makefile for A1M Toolchain

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
LDFLAGS = 

# Directories
COMPILER_DIR = compiler
ASSEMBLER_DIR = assembler
EMULATOR_DIR = emulator
BUILD_DIR = build

# Targets
COMPILER = $(BUILD_DIR)/algo
ASSEMBLER = $(BUILD_DIR)/a1m-asm
EMULATOR = $(BUILD_DIR)/a1m-emu

.PHONY: all clean install uninstall

all: $(COMPILER) $(ASSEMBLER) $(EMULATOR)

# Compiler
$(COMPILER): $(COMPILER_DIR)/src/*.c $(COMPILER_DIR)/src/*.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ \
		$(COMPILER_DIR)/src/main.c \
		$(COMPILER_DIR)/src/lexer.c \
		$(COMPILER_DIR)/src/parser.c \
		$(COMPILER_DIR)/src/codegen.c \
		$(COMPILER_DIR)/src/ast.c \
		$(COMPILER_DIR)/src/symboltable.c

# Assembler
$(ASSEMBLER): $(ASSEMBLER_DIR)/src/*.c $(ASSEMBLER_DIR)/src/*.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ \
		$(ASSEMBLER_DIR)/src/main.c \
		$(ASSEMBLER_DIR)/src/lexer.c \
		$(ASSEMBLER_DIR)/src/parser.c \
		$(ASSEMBLER_DIR)/src/encoder.c

# Emulator
$(EMULATOR): $(EMULATOR_DIR)/src/*.c $(EMULATOR_DIR)/src/*.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ \
		$(EMULATOR_DIR)/src/main.c \
		$(EMULATOR_DIR)/src/cpu.c \
		$(EMULATOR_DIR)/src/memory.c \
		$(EMULATOR_DIR)/src/syscall.c

clean:
	rm -rf $(BUILD_DIR)

install: all
	sudo cp $(COMPILER) /usr/local/bin/
	sudo cp $(ASSEMBLER) /usr/local/bin/
	sudo cp $(EMULATOR) /usr/local/bin/
	sudo cp scripts/algo-run /usr/local/bin/
	@echo "A1M Toolchain installed successfully"

uninstall:
	sudo rm -f /usr/local/bin/algo
	sudo rm -f /usr/local/bin/a1m-asm
	sudo rm -f /usr/local/bin/a1m-emu
	sudo rm -f /usr/local/bin/algo-run
	@echo "A1M Toolchain uninstalled"
```

### 29.2 Installation Script

**install.sh:**
```bash
#!/bin/bash
# A1M Toolchain Installation Script

set -e

echo "Building A1M Toolchain..."

# Build all components
make clean
make all

# Install binaries
echo "Installing to /usr/local/bin..."
sudo make install

# Verify installation
echo ""
echo "Verifying installation..."
which algo
which a1m-asm
which a1m-emu
which algo-run

echo ""
echo "A1M Toolchain installed successfully!"
echo "Usage: algo <source.algo>"
```

### 29.3 Compilation Workflow

**Complete Compilation Pipeline:**
```bash
#!/bin/bash
# algo-run: Complete compilation and execution script

if [ $# -lt 1 ]; then
    echo "Usage: $0 <source.algo>"
    exit 1
fi

SOURCE=$1
BASENAME=$(basename "$SOURCE" .algo)
ASM_FILE="${BASENAME}.asm"
BIN_FILE="${BASENAME}.bin"

# Step 1: Compile Algo to Assembly
echo "Compiling $SOURCE..."
algo "$SOURCE" || exit 1

# Step 2: Assemble to Binary
echo "Assembling ${ASM_FILE}..."
a1m-asm "${ASM_FILE}" -o "${BIN_FILE}" || exit 1

# Step 3: Execute
echo "Running ${BIN_FILE}..."
echo "─────────────────────────"
a1m-emu "${BIN_FILE}"

# Cleanup (optional)
# rm -f "${ASM_FILE}" "${BIN_FILE}"
```

### 29.4 Cross-Platform Support

**Platform Detection:**
```makefile
# Detect platform
UNAME := $(shell uname -s)

ifeq ($(UNAME),Linux)
    PLATFORM = linux
    INSTALL_DIR = /usr/local/bin
endif

ifeq ($(UNAME),Darwin)
    PLATFORM = macos
    INSTALL_DIR = /usr/local/bin
endif

ifeq ($(OS),Windows_NT)
    PLATFORM = windows
    INSTALL_DIR = C:/Program Files/A1M
    EXE_EXT = .exe
else
    EXE_EXT =
endif

# Adjust targets based on platform
COMPILER = $(BUILD_DIR)/algo$(EXE_EXT)
ASSEMBLER = $(BUILD_DIR)/a1m-asm$(EXE_EXT)
EMULATOR = $(BUILD_DIR)/a1m-emu$(EXE_EXT)
```

---

## Chapter 30: Optimization Techniques

### 30.1 Peephole Optimization

**Pattern Matching:**
```c
void peephole_optimize(CodeGenerator *gen) {
    // Pattern: MOV Rx, Rx -> eliminate
    // Pattern: ADD Rx, Ry, R0 -> MOV Rx, Ry
    // Pattern: MUL Rx, Ry, 1 -> MOV Rx, Ry
    // Pattern: MUL Rx, Ry, 2 -> SHL Rx, Ry, 1
    
    Instruction *instr = gen->instructions;
    while (instr) {
        // Eliminate useless MOV
        if (instr->opcode == OP_MOV) {
            if (instr->rd == instr->rs1) {
                remove_instruction(gen, instr);
                continue;
            }
        }
        
        // Replace MUL by power of 2 with shift
        if (instr->opcode == OP_MULI) {
            if (is_power_of_two(instr->immediate)) {
                int shift = log2_int(instr->immediate);
                instr->opcode = OP_SHLI;
                instr->immediate = shift;
            }
        }
        
        instr = instr->next;
    }
}
```

### 30.2 Register Allocation

**Graph Coloring Algorithm:**
```c
typedef struct {
    int reg_count;
    int *interference_matrix;
    int *colors;
} RegisterAllocationGraph;

void allocate_registers_graph_coloring(CodeGenerator *gen) {
    // Build interference graph
    RegisterAllocationGraph *graph = build_interference_graph(gen);
    
    // Color the graph (assign registers)
    color_graph(graph, 21);  // R10-R30 available
    
    // Apply coloring to instructions
    apply_register_assignment(gen, graph);
    
    free_allocation_graph(graph);
}

void build_interference_graph(CodeGenerator *gen) {
    // Two virtual registers interfere if they are live at the same time
    // This requires liveness analysis
}
```

### 30.3 Constant Folding and Propagation

**Constant Folding:**
```c
ASTNode *fold_constants(ASTNode *node) {
    if (node->type != AST_BINARY_OP) {
        return node;
    }
    
    ASTNode *left = fold_constants(node->data.binary_op.left);
    ASTNode *right = fold_constants(node->data.binary_op.right);
    
    if (left->type == AST_LITERAL && right->type == AST_LITERAL) {
        int64_t result;
        
        switch (node->data.binary_op.op) {
            case TOKEN_PLUS:
                result = left->data.int_value + right->data.int_value;
                break;
            case TOKEN_MINUS:
                result = left->data.int_value - right->data.int_value;
                break;
            case TOKEN_STAR:
                result = left->data.int_value * right->data.int_value;
                break;
            case TOKEN_SLASH:
                if (right->data.int_value != 0) {
                    result = left->data.int_value / right->data.int_value;
                } else {
                    return node;
                }
                break;
            default:
                return node;
        }
        
        return ast_create_literal_int(result);
    }
    
    return node;
}
```

### 30.4 Dead Code Elimination

**Remove Unreachable Code:**
```c
void eliminate_dead_code(ASTNode *function) {
    // Mark reachable statements
    mark_reachable(function->data.function.body);
    
    // Remove unreachable statements
    remove_unreachable(function->data.function.body);
}

void mark_reachable(ASTNode *block) {
    for (int i = 0; i < block->data.block.count; i++) {
        ASTNode *stmt = block->data.block.statements[i];
        stmt->reachable = 1;
        
        // If we hit a return, subsequent statements are unreachable
        if (stmt->type == AST_RETURN) {
            for (int j = i + 1; j < block->data.block.count; j++) {
                block->data.block.statements[j]->reachable = 0;
            }
            break;
        }
    }
}
```

### 30.5 Tail Call Optimization

**Tail Call Detection:**
```c
int is_tail_call(ASTNode *return_stmt) {
    if (return_stmt->type != AST_RETURN) {
        return 0;
    }
    
    ASTNode *expr = return_stmt->data.return_value;
    if (expr->type != AST_FUNCTION_CALL) {
        return 0;
    }
    
    // Check if it's calling itself (tail recursion)
    // or another function (tail call)
    return 1;
}

void optimize_tail_call(CodeGenerator *gen, ASTNode *call) {
    // Instead of CALL + RET, use JMP
    emit(gen, "    ; Tail call optimization");
    
    // Set up arguments
    codegen_function_arguments(gen, call);
    
    // Jump directly to function
    emit(gen, "    JMP %s", call->data.function_call.name);
}
```

---

# PART VII: PRACTICAL EXAMPLES

---

## Chapter 31: Example Programs

### 31.1 Fibonacci Calculator

**Iterative Version:**
```algo
// Fibonacci sequence calculator (iterative)

fun fibonacci_iterative(int n) -> int {
    if (n <= 1) {
        return n;
    }
    
    int a = 0;
    int b = 1;
    int i;
    
    for (i = 2; i <= n; i = i + 1) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    
    return b;
}

fun main() {
    int n;
    
    print("Enter n: ");
    n = read_int();
    
    int result = fibonacci_iterative(n);
    
    print("Fibonacci(");
    print(n);
    print(") = ");
    print(result);
}
```

**Generated Assembly:**
```assembly
.text
.global main

fibonacci_iterative:
    PUSH R31
    PUSH R10
    PUSH R11
    PUSH R12
    PUSH R13
    
    ; if (n <= 1) return n
    CMPI R4, 1
    JNN fib_iter_base
    MOV R1, R4
    JMP fib_iter_exit

fib_iter_base:
    ; int a = 0, b = 1
    MOVI R10, 0         ; a
    MOVI R11, 1         ; b
    MOVI R12, 2         ; i

fib_iter_loop:
    ; for (i = 2; i <= n; ...)
    CMP R12, R4
    JGT fib_iter_done
    
    ; temp = a + b
    ADD R13, R10, R11
    
    ; a = b
    MOV R10, R11
    
    ; b = temp
    MOV R11, R13
    
    ; i++
    ADDI R12, R12, 1
    JMP fib_iter_loop

fib_iter_done:
    MOV R1, R11         ; return b

fib_iter_exit:
    POP R13
    POP R12
    POP R11
    POP R10
    POP R31
    RET

main:
    PUSH R31
    
    ; Print prompt
    MOVI R1, prompt_str
    SYSCALL 0x03
    
    ; Read input
    SYSCALL 0x04
    MOV R10, R1
    
    ; Call fibonacci
    MOV R4, R10
    CALL fibonacci_iterative
    MOV R11, R1
    
    ; Print result
    MOVI R1, result_str1
    SYSCALL 0x03
    MOV R1, R10
    SYSCALL 0x01
    MOVI R1, result_str2
    SYSCALL 0x03
    MOV R1, R11
    SYSCALL 0x01
    
    POP R31
    SYSCALL 0x00

.data
prompt_str: .asciiz "Enter n: "
result_str1: .asciiz "Fibonacci("
result_str2: .asciiz ") = "
```

### 31.2 Sorting Benchmark

**Merge Sort Implementation:**
```algo
int array[100];

fun merge(int left, int mid, int right) {
    int temp[100];
    int i = left;
    int j = mid + 1;
    int k = 0;
    
    while (i <= mid && j <= right) {
        if (array[i] <= array[j]) {
            temp[k] = array[i];
            i = i + 1;
        } else {
            temp[k] = array[j];
            j = j + 1;
        }
        k = k + 1;
    }
    
    while (i <= mid) {
        temp[k] = array[i];
        i = i + 1;
        k = k + 1;
    }
    
    while (j <= right) {
        temp[k] = array[j];
        j = j + 1;
        k = k + 1;
    }
    
    int x;
    for (x = 0; x < k; x = x + 1) {
        array[left + x] = temp[x];
    }
}

fun merge_sort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(left, mid);
        merge_sort(mid + 1, right);
        merge(left, mid, right);
    }
}

fun main() {
    int n = 20;
    int i;
    
    // Fill with random-ish data
    for (i = 0; i < n; i = i + 1) {
        array[i] = n - i;
    }
    
    print("Before sorting:\n");
    for (i = 0; i < n; i = i + 1) {
        print(array[i]);
        print(" ");
    }
    
    merge_sort(0, n - 1);
    
    print("\nAfter sorting:\n");
    for (i = 0; i < n; i = i + 1) {
        print(array[i]);
        print(" ");
    }
}
```

### 31.3 Linked List

**Dynamic Linked List (using malloc):**
```algo
// Node structure (simulated)
// struct Node {
//     int data;       // offset 0
//     int* next;      // offset 8
// };

fun create_node(int value) -> int* {
    int *node = malloc(16);  // Allocate 16 bytes
    
    // Set data
    *node = value;
    
    // Set next to NULL
    *(node + 1) = 0;
    
    return node;
}

fun insert_front(int *head, int value) -> int* {
    int *new_node = create_node(value);
    *(new_node + 1) = head;  // new_node->next = head
    return new_node;
}

fun print_list(int *head) {
    int *current = head;
    
    while (current != 0) {
        int value = *current;
        print(value);
        print(" -> ");
        current = *(current + 1);  // current = current->next
    }
    print("NULL\n");
}

fun main() {
    int *list = 0;  // NULL
    
    list = insert_front(list, 3);
    list = insert_front(list, 2);
    list = insert_front(list, 1);
    
    print("List: ");
    print_list(list);
}
```

---

## Chapter 32: Debugging Techniques

### 32.1 Compiler Debug Output

**Enable Debug Mode:**
```c
// compiler/src/debug.h

#define DEBUG_LEXER 1
#define DEBUG_PARSER 1
#define DEBUG_CODEGEN 1

#if DEBUG_LEXER
#define DEBUG_LEX(fmt, ...) \
    fprintf(stderr, "[LEXER] " fmt "\n", ##__VA_ARGS__)
#else
#define DEBUG_LEX(fmt, ...)
#endif

// Usage:
Token lexer_next_token(Lexer *lexer) {
    Token tok = scan_token(lexer);
    DEBUG_LEX("Token: %s (line %d)", token_name(tok.type), tok.line);
    return tok;
}
```

### 32.2 AST Visualization

**Print AST:**
```c
void print_ast(ASTNode *node, int indent) {
    for (int i = 0; i < indent; i++) printf("  ");
    
    switch (node->type) {
        case AST_FUNCTION:
            printf("Function: %s\n", node->data.function.name);
            print_ast(node->data.function.body, indent + 1);
            break;
            
        case AST_BINARY_OP:
            printf("BinaryOp: %s\n", token_name(node->data.binary_op.op));
            print_ast(node->data.binary_op.left, indent + 1);
            print_ast(node->data.binary_op.right, indent + 1);
            break;
            
        case AST_LITERAL:
            printf("Literal: %ld\n", node->data.int_value);
            break;
            
        case AST_IDENTIFIER:
            printf("Identifier: %s\n", node->data.name);
            break;
            
        default:
            printf("Node type: %d\n", node->type);
    }
}
```

### 32.3 Emulator Debugger

**Interactive Debugger:**
```c
void debugger_repl(CPU *cpu) {
    char command[256];
    
    while (1) {
        printf("(a1m-debug) ");
        fgets(command, sizeof(command), stdin);
        
        if (strncmp(command, "step", 4) == 0) {
            // Execute one instruction
            execute_one_instruction(cpu);
            print_cpu_state(cpu);
        }
        else if (strncmp(command, "continue", 8) == 0) {
            // Run until breakpoint
            cpu_run(cpu);
        }
        else if (strncmp(command, "print", 5) == 0) {
            // Print register or memory
            char what[64];
            sscanf(command + 6, "%s", what);
            
            if (what[0] == 'R' || what[0] == 'r') {
                int reg = atoi(what + 1);
                printf("R%d = 0x%016lx (%ld)\n", 
                       reg, cpu->registers[reg], cpu->registers[reg]);
            }
        }
        else if (strncmp(command, "break", 5) == 0) {
            // Set breakpoint
            uint64_t addr;
            sscanf(command + 6, "%lx", &addr);
            set_breakpoint(cpu, addr);
        }
        else if (strncmp(command, "quit", 4) == 0) {
            break;
        }
        else {
            printf("Unknown command. Available: step, continue, print, break, quit\n");
        }
    }
}
```

### 32.4 Common Errors and Solutions

**Error Table:**
```
Error                           Cause                       Solution
─────────────────────────────────────────────────────────────────────
"Undefined variable: x"         Variable not declared       Declare before use
"Type mismatch"                 Wrong type in operation     Check types
"Function 'f' expects N args"   Wrong argument count        Fix call site
"Division by zero"              Runtime div by 0            Add check
"Segmentation fault"            Bad memory access           Check pointers
"Stack overflow"                Too deep recursion          Use iteration
"Register spill"                Too many live variables     Simplify expression
```

---

## Chapter 33: Performance Analysis

### 33.1 Benchmarking

**Benchmark Framework:**
```algo
// Simple benchmark timer (using syscalls)

fun benchmark(int iterations) {
    int i;
    int sum = 0;
    
    print("Running benchmark with ");
    print(iterations);
    print(" iterations...\n");
    
    // Benchmark loop
    for (i = 0; i < iterations; i = i + 1) {
        sum = sum + i;
    }
    
    print("Result: ");
    print(sum);
    print("\n");
}

fun main() {
    benchmark(1000000);
}
```

### 33.2 Profiling

**Instruction Counter:**
```c
typedef struct {
    uint64_t total_instructions;
    uint64_t instruction_count[256];  // Per opcode
    uint64_t function_calls;
    uint64_t memory_accesses;
} Profiler;

void profile_instruction(Profiler *prof, uint8_t opcode) {
    prof->total_instructions++;
    prof->instruction_count[opcode]++;
    
    if (opcode == 0x39) {  // CALL
        prof->function_calls++;
    }
    if (opcode >= 0x20 && opcode <= 0x25) {  // Memory ops
        prof->memory_accesses++;
    }
}

void print_profile(Profiler *prof) {
    printf("\nProfile Report:\n");
    printf("Total instructions: %lu\n", prof->total_instructions);
    printf("Function calls: %lu\n", prof->function_calls);
    printf("Memory accesses: %lu\n", prof->memory_accesses);
    
    printf("\nTop 10 instructions:\n");
    // Sort and print...
}
```

### 33.3 Optimization Impact

**Performance Comparison:**
```
Optimization                Before      After       Improvement
──────────────────────────────────────────────────────────────────
No optimization            100,000     100,000     baseline
Constant folding           100,000      95,000     5%
Dead code elimination       95,000      90,000     5%
Register allocation         90,000      75,000     17%
Peephole optimization       75,000      70,000     7%
──────────────────────────────────────────────────────────────────
Total                      100,000      70,000     30%
```

---

# PART VIII: TESTING AND VERIFICATION

---

## Chapter 34: Test Suite

### 34.1 Unit Tests

**Lexer Tests:**
```c
// tests/test_lexer.c

void test_tokenize_numbers() {
    Lexer *lex = lexer_create_from_string("42 0x2A 0b101010");
    
    Token t1 = lexer_next_token(lex);
    assert(t1.type == TOKEN_INT_LITERAL);
    assert(t1.value.int_value == 42);
    
    Token t2 = lexer_next_token(lex);
    assert(t2.type == TOKEN_INT_LITERAL);
    assert(t2.value.int_value == 0x2A);
    
    Token t3 = lexer_next_token(lex);
    assert(t3.type == TOKEN_INT_LITERAL);
    assert(t3.value.int_value == 0b101010);
    
    printf("✓ test_tokenize_numbers passed\n");
}

void test_tokenize_keywords() {
    Lexer *lex = lexer_create_from_string("fun if else while");
    
    assert(lexer_next_token(lex).type == TOKEN_FUN);
    assert(lexer_next_token(lex).type == TOKEN_IF);
    assert(lexer_next_token(lex).type == TOKEN_ELSE);
    assert(lexer_next_token(lex).type == TOKEN_WHILE);
    
    printf("✓ test_tokenize_keywords passed\n");
}
```

### 34.2 Integration Tests

**End-to-End Compilation Test:**
```bash
#!/bin/bash
# tests/integration/test_hello_world.sh

# Create test program
cat > test_hello.algo <<EOF
fun main() {
    print("Hello, World!");
}
EOF

# Compile
algo test_hello.algo || exit 1

# Assemble
a1m-asm test_hello.asm -o test_hello.bin || exit 1

# Run and capture output
OUTPUT=$(a1m-emu test_hello.bin)

# Verify output
if [ "$OUTPUT" == "Hello, World!" ]; then
    echo "✓ Hello World test passed"
    exit 0
else
    echo "✗ Hello World test failed"
    echo "Expected: Hello, World!"
    echo "Got: $OUTPUT"
    exit 1
fi
```

### 34.3 Regression Tests

**Test Runner:**
```bash
#!/bin/bash
# tests/run_tests.sh

TESTS_DIR="tests/algo"
PASSED=0
FAILED=0

for test_file in $TESTS_DIR/*.algo; do
    echo "Running $(basename $test_file)..."
    
    # Compile and run
    algo-run "$test_file" > /tmp/output.txt 2>&1
    
    # Compare with expected output
    expected="${test_file%.algo}.expected"
    if diff -q /tmp/output.txt "$expected" > /dev/null 2>&1; then
        echo "  ✓ PASSED"
        ((PASSED++))
    else
        echo "  ✗ FAILED"
        ((FAILED++))
        diff /tmp/output.txt "$expected"
    fi
done

echo ""
echo "Results: $PASSED passed, $FAILED failed"
exit $FAILED
```

---

## Chapter 35: Future Enhancements

### 35.1 Language Extensions

**Planned Features:**
- Structures and user-defined types
- Pointers and dynamic memory
- String type with operations
- Arrays as first-class types
- Function pointers
- Modules and imports
- Standard library expansion

**Example - Structures:**
```algo
struct Point {
    int x;
    int y;
};

fun distance(struct Point *p1, struct Point *p2) -> int {
    int dx = p1->x - p2->x;
    int dy = p1->y - p2->y;
    return sqrt(dx * dx + dy * dy);
}
```

### 35.2 Hardware Extensions

**Planned ISA Extensions:**
- Floating-point unit (FPU)
- SIMD instructions
- Cache control instructions
- Atomic operations
- Memory barriers
- Interrupt handling

### 35.3 Toolchain Improvements

**Compiler Enhancements:**
- Better error messages with suggestions
- Incremental compilation
- Link-time optimization (LTO)
- Profile-guided optimization (PGO)
- Static analysis tools
- Code coverage analysis

**IDE Integration:**
- VS Code language server
- Syntax highlighting improvements
- Code completion
- Real-time error checking
- Integrated debugger
- Profiler integration

---

# APPENDICES

---

## Appendix A: Complete Instruction Reference

### A.1 Instruction Summary Table

```
┌────────┬──────────────┬────────┬─────────────────────────────────────┐
│ Opcode │ Mnemonic     │ Format │ Description                         │
├────────┼──────────────┼────────┼─────────────────────────────────────┤
│ 0x00   │ NOP          │ -      │ No operation                        │
│ 0x01   │ HALT         │ -      │ Halt execution                      │
├────────┼──────────────┼────────┼─────────────────────────────────────┤
│ 0x02   │ ADD          │ R-type │ RD = RS1 + RS2                     │
│ 0x03   │ ADDI         │ I-type │ RD = RS1 + IMM                     │
│ 0x04   │ SUB          │ R-type │ RD = RS1 - RS2                     │
│ 0x05   │ SUBI         │ I-type │ RD = RS1 - IMM                     │
│ 0x06   │ MUL          │ R-type │ RD = RS1 * RS2                     │
│ 0x07   │ MULI         │ I-type │ RD = RS1 * IMM                     │
│ 0x08   │ DIV          │ R-type │ RD = RS1 / RS2                     │
│ 0x09   │ DIVI         │ I-type │ RD = RS1 / IMM                     │
│ 0x0A   │ MOD          │ R-type │ RD = RS1 % RS2                     │
│ 0x0B   │ MODI         │ I-type │ RD = RS1 % IMM                     │
├────────┼──────────────┼────────┼─────────────────────────────────────┤
│ 0x0C   │ AND          │ R-type │ RD = RS1 & RS2                     │
│ 0x0D   │ ANDI         │ I-type │ RD = RS1 & IMM                     │
│ 0x0E   │ OR           │ R-type │ RD = RS1 | RS2                     │
│ 0x0F   │ ORI          │ I-type │ RD = RS1 | IMM                     │
│ 0x10   │ XOR          │ R-type │ RD = RS1 ^ RS2                     │
│ 0x11   │ XORI         │ I-type │ RD = RS1 ^ IMM                     │
│ 0x12   │ SHL          │ R-type │ RD = RS1 << RS2                    │
│ 0x13   │ SHLI         │ I-type │ RD = RS1 << IMM                    │
│ 0x14   │ SHR          │ R-type │ RD = RS1 >> RS2 (logical)          │
│ 0x15   │ SHRI         │ I-type │ RD = RS1 >> IMM (logical)          │
│ 0x16   │ SAR          │ R-type │ RD = RS1 >> RS2 (arithmetic)       │
│ 0x17   │ SARI         │ I-type │ RD = RS1 >> IMM (arithmetic)       │
├────────┼──────────────┼────────┼─────────────────────────────────────┤
│ 0x20   │ LOAD         │ I-type │ RD = Memory[RS1 + IMM]             │
│ 0x21   │ STORE        │ I-type │ Memory[RS1 + IMM] = RD             │
│ 0x22   │ LOADB        │ I-type │ RD = (byte)Memory[RS1 + IMM]       │
│ 0x23   │ STOREB       │ I-type │ Memory[RS1 + IMM] = (byte)RD       │
│ 0x24   │ LOADH        │ I-type │ RD = (halfword)Memory[RS1 + IMM]   │
│ 0x25   │ STOREH       │ I-type │ Memory[RS1 + IMM] = (halfword)RD   │
├────────┼──────────────┼────────┼─────────────────────────────────────┤
│ 0x30   │ JMP          │ J-type │ PC = ADDRESS                        │
│ 0x31   │ JZ           │ J-type │ PC = ADDRESS if ZF = 1             │
│ 0x32   │ JNZ          │ J-type │ PC = ADDRESS if ZF = 0             │
│ 0x33   │ JGT          │ J-type │ PC = ADDRESS if NF = 0 and ZF = 0  │
│ 0x34   │ JLT          │ J-type │ PC = ADDRESS if NF = 1             │
│ 0x35   │ JGE          │ J-type │ PC = ADDRESS if NF = 0 or ZF = 1   │
│ 0x36   │ JLE          │ J-type │ PC = ADDRESS if NF = 1 or ZF = 1   │
│ 0x37   │ JMPR         │ R-type │ PC = RS1                            │
│ 0x38   │ JZR          │ R-type │ PC = RS1 if ZF = 1                 │
│ 0x39   │ CALL         │ J-type │ R31 = PC + 4; PC = ADDRESS         │
│ 0x3A   │ RET          │ -      │ PC = R31                            │
├────────┼──────────────┼────────┼─────────────────────────────────────┤
│ 0x40   │ CMP          │ R-type │ Set flags based on RS1 - RS2       │
│ 0x41   │ CMPI         │ I-type │ Set flags based on RS1 - IMM       │
│ 0x42   │ PUSH         │ R-type │ SP -= 8; Memory[SP] = RS1          │
│ 0x43   │ POP          │ R-type │ RD = Memory[SP]; SP += 8           │
├────────┼──────────────┼────────┼─────────────────────────────────────┤
│ 0x50   │ SYSCALL      │ I-type │ System call (IMM = syscall number) │
└────────┴──────────────┴────────┴─────────────────────────────────────┘
```

---

## Appendix B: Register Convention

### B.1 Register Usage

```
Register  ABI Name    Purpose                    Saved By
─────────────────────────────────────────────────────────────
R0        zero        Always zero                -
R1        ret         Return value / syscall arg Caller
R2        arg2        2nd syscall argument       Caller
R3        sp          Stack pointer              Callee
R4-R11    a0-a7       Function arguments         Caller
R12-R30   t0-t18      Temporary registers        Caller
R31       ra          Return address             Caller
```

### B.2 Calling Convention

**Function Call Sequence:**
```assembly
; Caller:
    ; 1. Save caller-saved registers if needed
    PUSH R4
    PUSH R5
    
    ; 2. Set up arguments
    MOVI R4, 10     ; First argument
    MOVI R5, 20     ; Second argument
    
    ; 3. Call function
    CALL my_function
    
    ; 4. Get return value
    MOV R10, R1
    
    ; 5. Restore caller-saved registers
    POP R5
    POP R4

; Callee:
my_function:
    ; 1. Save return address and callee-saved registers
    PUSH R31
    PUSH R10
    
    ; 2. Allocate stack frame
    SUBI R3, R3, 16
    
    ; 3. Function body
    ADD R1, R4, R5
    
    ; 4. Deallocate stack frame
    ADDI R3, R3, 16
    
    ; 5. Restore registers and return
    POP R10
    POP R31
    RET
```

---

## Appendix C: System Call Reference

### C.1 System Call Table

```
Code  Name            Arguments           Returns         Description
───────────────────────────────────────────────────────────────────────
0x00  EXIT            -                   -               Terminate program
0x01  PRINT_INT       R1 = integer        -               Print integer
0x02  PRINT_CHAR      R1 = character      -               Print character
0x03  PRINT_STRING    R1 = address        -               Print string
0x04  READ_INT        -                   R1 = integer    Read integer
0x05  READ_CHAR       -                   R1 = character  Read character
0x06  ALLOCATE        R1 = size           R1 = address    Allocate memory
0x07  FREE            R1 = address        -               Free memory
0x10  OPEN            R1 = filename       R1 = fd         Open file
                      R2 = mode
0x11  CLOSE           R1 = fd             -               Close file
0x12  READ            R1 = fd             R1 = bytes      Read from file
                      R2 = buffer                          read
                      R3 = count
0x13  WRITE           R1 = fd             R1 = bytes      Write to file
                      R2 = buffer                          written
                      R3 = count
```

---

## Appendix D: Assembly Language Quick Reference

### D.1 Assembler Directives

```assembly
.text                   ; Code section
.data                   ; Data section
.global symbol          ; Export symbol
.align n                ; Align to n-byte boundary
.byte value             ; 8-bit value
.word value             ; 32-bit value
.dword value            ; 64-bit value
.ascii "text"           ; ASCII string (no null)
.asciiz "text"          ; Null-terminated string
.space n                ; Reserve n bytes
```

### D.2 Addressing Modes

```assembly
MOVI R1, 42             ; Immediate: value = 42
ADD R1, R2, R3          ; Register: R2, R3
LOAD R1, 8(R2)          ; Base + offset: address = R2 + 8
JMP label               ; Direct: address = label
JMPR R1                 ; Indirect: address = R1
```

---

## Appendix E: Error Codes and Messages

### E.1 Compiler Errors

```
E001: Syntax error: unexpected token
E002: Undefined variable
E003: Type mismatch in expression
E004: Function not declared
E005: Argument count mismatch
E006: Return type mismatch
E007: Duplicate declaration
E008: Break outside loop
E009: Continue outside loop
E010: Invalid lvalue in assignment
```

### E.2 Assembler Errors

```
A001: Unknown instruction mnemonic
A002: Invalid register number
A003: Immediate value out of range
A004: Undefined label
A005: Invalid addressing mode
A006: Duplicate label definition
A007: Invalid directive
A008: Unexpected end of file
```

### E.3 Runtime Errors

```
R001: Division by zero
R002: Memory access violation
R003: Stack overflow
R004: Illegal instruction
R005: System call failed
R006: Null pointer dereference
```

---

## Appendix F: Build and Installation Guide

### F.1 Prerequisites

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential gcc make git
```

**macOS:**
```bash
xcode-select --install
brew install gcc make
```

**Windows (WSL):**
```bash
wsl --install
# Then follow Ubuntu instructions
```

### F.2 Building from Source

```bash
# Clone repository
git clone https://github.com/algoscienceacademy/A1M_Compiler.git
cd A1M_Compiler

# Build all components
make clean
make all

# Run tests
make test

# Install system-wide
sudo make install

# Verify installation
which algo
algo --version
```

### F.3 Configuration

**Environment Variables:**
```bash
export A1M_HOME=/usr/local/A1M
export PATH=$PATH:$A1M_HOME/bin
export A1M_LIB=$A1M_HOME/lib
```

---

## Appendix G: VS Code Extension

### G.1 Installation

```bash
# Install from VSIX
code --install-extension vsextension/algo-lang-*.vsix

# Or build from source
cd vsextension
npm install
npm run compile
vsce package
code --install-extension algo-lang-*.vsix
```

### G.2 Features

- Syntax highlighting for .algo files
- Real-time error checking
- Code snippets
- Run button (Ctrl+Shift+R)
- Integrated terminal output
- Jump to definition
- Symbol search

### G.3 Configuration

```json
{
    "algo.compiler.path": "/usr/local/bin/algo",
    "algo.assembler.path": "/usr/local/bin/a1m-asm",
    "algo.emulator.path": "/usr/local/bin/a1m-emu",
    "algo.autoCompile": true,
    "algo.showAssembly": true
}
```

---

## Appendix H: Contributing Guidelines

### H.1 Development Setup

```bash
# Fork and clone
git clone https://github.com/YOUR_USERNAME/A1M_Compiler.git
cd A1M_Compiler

# Create feature branch
git checkout -b feature/my-feature

# Make changes, test, commit
make test
git add .
git commit -m "Add feature: description"

# Push and create pull request
git push origin feature/my-feature
```

### H.2 Coding Standards

**C Code Style:**
```c
// Use 4 spaces for indentation
// Function names: lowercase_with_underscores
// Type names: PascalCase
// Constants: UPPER_CASE
// Comments: explain why, not what

// Good:
void parse_expression(Parser *parser) {
    // Check for binary operator because...
    if (is_binary_op(token)) {
        ...
    }
}
```
 