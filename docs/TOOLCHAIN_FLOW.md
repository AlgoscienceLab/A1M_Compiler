# A1M CPU Toolchain Flow

## Complete Development Flow

```
┌─────────────────────────────────────────────────────────────────────┐
│                        A1M CPU TOOLCHAIN FLOW                        │
└─────────────────────────────────────────────────────────────────────┘

HARDWARE DESIGN (Verilog)
┌──────────────────────────────────────┐
│  1. Verilog HDL Implementation       │
│     verilog/cpu/a1m_cpu.v            │
│     verilog/cpu/alu.v                │
│     verilog/cpu/register_file.v      │
│     verilog/cpu/control_unit.v       │
│     verilog/memory/memory.v          │
│     verilog/top.v                    │
└──────────────────┬───────────────────┘
                   │
                   ├─> Simulation: iverilog verilog/testbench/a1m_testbench.v
                   │   Output: vvp a.out (waveform: gtkwave dump.vcd)
                   │
                   └─> FPGA Synthesis: vivado/quartus (creates bitstream)
                       Output: .bit/.sof file for FPGA programming


HIGH-LEVEL PROGRAMMING (Algo Language)
┌──────────────────────────────────────┐
│  2. Write Algo Source Code           │
│     examples/algo/hello.algo         │
│     examples/algo/fibonacci.algo     │
│                                      │
│     func main() -> int {             │
│         let x: int = 10;             │
│         print(x);                    │
│         return 0;                    │
│     }                                │
└──────────────────┬───────────────────┘
                   │
                   ▼
┌──────────────────────────────────────┐
│  3. Algo Compiler                    │
│     ./compiler/algo-compiler         │
│                                      │
│     Input:  program.algo             │
│     Output: program.asm              │
│                                      │
│  Performs:                           │
│  • Lexical analysis (tokenization)   │
│  • Parsing (AST generation)          │
│  • Semantic analysis                 │
│  • Code generation (A1M assembly)    │
└──────────────────┬───────────────────┘
                   │
                   ▼

ASSEMBLY LEVEL
┌──────────────────────────────────────┐
│  4. A1M Assembly Code                │
│     examples/asm/hello.asm           │
│                                      │
│     .text                            │
│     main:                            │
│         ADDI R1, R0, 42              │
│         SW R1, 0(R2)                 │
│         HALT                         │
└──────────────────┬───────────────────┘
                   │
                   ▼
┌──────────────────────────────────────┐
│  5. A1M Assembler                    │
│     ./assembler/a1m-asm              │
│                                      │
│     Input:  program.asm              │
│     Output: program.bin              │
│                                      │
│  Performs:                           │
│  • Two-pass assembly                 │
│  • Label resolution                  │
│  • Instruction encoding              │
│  • Binary generation                 │
└──────────────────┬───────────────────┘
                   │
                   ▼

BINARY EXECUTABLE
┌──────────────────────────────────────┐
│  6. Machine Code Binary              │
│     program.bin                      │
│                                      │
│  Format: Raw 32-bit instructions     │
│  0x00000000: 20010002A  # ADDI       │
│  0x00000004: AC020000   # SW         │
│  0x00000008: 00000000   # HALT       │
└──────────────────┬───────────────────┘
                   │
                   ├─────────────────────────────────┐
                   │                                 │
                   ▼                                 ▼
         
EXECUTION PATHS

┌──────────────────────────────┐    ┌─────────────────────────────┐
│  7a. Software Emulator       │    │  7b. Hardware Execution     │
│      ./emulator/a1m-emu      │    │      (FPGA/ASIC)            │
│                              │    │                             │
│  Runs binary in software     │    │  Load binary to FPGA        │
│  • Instruction simulation    │    │  memory and execute on      │
│  • Memory emulation          │    │  real A1M CPU hardware      │
│  • Register state tracking   │    │                             │
│  • Debugging support         │    │  via: top.v loaded to       │
│  • System call handling      │    │  Xilinx/Altera FPGA         │
└──────────────┬───────────────┘    └─────────────────────────────┘
               │
               ▼
┌──────────────────────────────────────┐
│  8. GUI IDE (Integrated)             │
│     ./gui/a1m-ide                    │
│                                      │
│  ┌────────────────────────────────┐  │
│  │  Code Editor                   │  │
│  │  • Syntax highlighting         │  │
│  │  • File operations             │  │
│  │  • Auto-save                   │  │
│  └────────────────────────────────┘  │
│                                      │
│  ┌────────────────────────────────┐  │
│  │  Build System                  │  │
│  │  • Compile Algo → ASM          │  │
│  │  • Assemble ASM → BIN          │  │
│  │  • One-click build & run       │  │
│  └────────────────────────────────┘  │
│                                      │
│  ┌────────────────────────────────┐  │
│  │  Integrated Emulator           │  │
│  │  • Load and execute binary     │  │
│  │  • Step-by-step execution      │  │
│  │  • Breakpoint support          │  │
│  │  • Execution speed control     │  │
│  └────────────────────────────────┘  │
│                                      │
│  ┌────────────────────────────────┐  │
│  │  Live Visualization            │  │
│  │  • Register viewer (R0-R31)    │  │
│  │  • Memory inspector            │  │
│  │  • PC and status display       │  │
│  │  • Output console              │  │
│  └────────────────────────────────┘  │
└──────────────────────────────────────┘
```

## Detailed Component Descriptions

### 1. Verilog HDL (Hardware)
- **Purpose**: Define the actual CPU hardware
- **Location**: `verilog/`
- **Key Files**:
  - `cpu/a1m_cpu.v` - Main 5-stage pipelined CPU
  - `cpu/alu.v` - 64-bit ALU with all operations
  - `cpu/register_file.v` - 32×64-bit register file
  - `cpu/control_unit.v` - Instruction decoder
  - `memory/memory.v` - Memory subsystem
  - `top.v` - Top-level integration
  - `testbench/a1m_testbench.v` - Simulation testbench

- **Testing**: 
  ```bash
  iverilog -o a1m_sim verilog/testbench/a1m_testbench.v
  vvp a1m_sim
  gtkwave dump.vcd  # View waveforms
  ```

### 2. Algo Language (High-Level)
- **Purpose**: High-level programming abstraction
- **Syntax**: C-like with strong typing
- **Features**:
  - Functions with return types
  - Variables with type annotations
  - Control flow (if/while/for)
  - Arrays and pointers
  - Print and system calls

### 3. Algo Compiler
- **Executable**: `compiler/algo-compiler`
- **Input**: `.algo` files
- **Output**: `.asm` files (A1M assembly)
- **Process**:
  1. Tokenization (lexer)
  2. Parsing (build AST)
  3. Semantic analysis (type checking)
  4. Code generation (emit assembly)

- **Usage**:
  ```bash
  ./compiler/algo-compiler input.algo -o output.asm
  ```

### 4. A1M Assembly Language
- **Format**: Human-readable assembly
- **Sections**:
  - `.text` - Code section
  - `.data` - Data section
- **Instructions**: 50+ instructions (ADD, SUB, LOAD, STORE, etc.)
- **Addressing**: Supports R-type, I-type, J-type formats

### 5. A1M Assembler
- **Executable**: `assembler/a1m-asm`
- **Input**: `.asm` files
- **Output**: `.bin` files (machine code)
- **Algorithm**:
  - **Pass 1**: Build symbol table (resolve labels)
  - **Pass 2**: Generate machine code

- **Usage**:
  ```bash
  ./assembler/a1m-asm input.asm -o output.bin
  ```

### 6. Binary Format
- **Format**: Raw binary, 32-bit instructions
- **Layout**:
  - Instructions are 32 bits each
  - Stored in little-endian format
  - Can be loaded directly into emulator or FPGA memory

### 7a. Software Emulator
- **Executable**: `emulator/a1m-emu`
- **Input**: `.bin` files
- **Features**:
  - Full instruction set simulation
  - 64-bit register emulation
  - Memory subsystem (4GB addressable)
  - System call handling (print, exit, etc.)
  - Debugging output

- **Usage**:
  ```bash
  ./emulator/a1m-emu program.bin
  ./emulator/a1m-emu -d program.bin  # Debug mode
  ```

### 7b. Hardware Execution (FPGA)
- Load `.bin` file to FPGA block RAM
- Execute on synthesized A1M CPU
- Tools: Vivado (Xilinx) or Quartus (Intel/Altera)

### 8. GUI IDE
- **Executable**: `gui/a1m-ide`
- **Technology**: GTK 3.0
- **Integrated Features**:
  - **Editor**: Write Algo/Assembly code
  - **Compiler**: One-click compile
  - **Assembler**: Automatic assembly
  - **Emulator**: Embedded CPU emulator
  - **Debugger**: Step, breakpoints, watch
  - **Visualizer**: Registers, memory, output

- **Usage**:
  ```bash
  ./gui/a1m-ide
  # Then: File → Open → examples/algo/fibonacci.algo
  # Build → Build and Run
  ```

## Typical Workflows

### Workflow 1: Algo → Execution (Full Stack)
```bash
# 1. Write Algo code
echo 'func main() -> int { print("Hello"); return 0; }' > hello.algo

# 2. Compile to assembly
./compiler/algo-compiler hello.algo -o hello.asm

# 3. Assemble to binary
./assembler/a1m-asm hello.asm -o hello.bin

# 4. Run in emulator
./emulator/a1m-emu hello.bin
```

### Workflow 2: Assembly → Execution
```bash
# 1. Write assembly
cat > test.asm << 'EOF'
.text
main:
    ADDI R1, R0, 42
    HALT
EOF

# 2. Assemble
./assembler/a1m-asm test.asm -o test.bin

# 3. Execute
./emulator/a1m-emu test.bin
```

### Workflow 3: GUI Development
```bash
# 1. Launch IDE
./gui/a1m-ide

# 2. In GUI:
#    - File → New
#    - Write Algo code
#    - Build → Compile Algo
#    - Build → Assemble
#    - Debug → Run
#    - Watch registers/memory update in real-time
```

### Workflow 4: Hardware Testing
```bash
# 1. Simulate Verilog
cd verilog
iverilog -o sim testbench/a1m_testbench.v
vvp sim

# 2. View waveforms
gtkwave dump.vcd

# 3. Synthesize for FPGA (Vivado example)
vivado -mode batch -source synthesis_script.tcl
```

## Build Instructions

### Build All Components
```bash
./build.sh
```

This builds:
1. Emulator (`emulator/a1m-emu`)
2. Assembler (`assembler/a1m-asm`)
3. Compiler (`compiler/algo-compiler`)
4. GUI IDE (`gui/a1m-ide`) - if GTK3 available

### Build Individual Components
```bash
# Emulator
cd emulator && make

# Assembler
cd assembler && make

# Compiler
cd compiler && make

# GUI
cd gui && make
```

## Testing the Flow

```bash
# Run automated tests
./test.sh

# Run demo
./demo.sh
```

## File Extensions

- `.v` - Verilog HDL source
- `.algo` - Algo high-level source
- `.asm` - A1M assembly source
- `.bin` - A1M binary executable
- `.vcd` - Waveform dump (simulation)
- `.bit/.sof` - FPGA bitstream

## Memory Map

| Address Range | Purpose | Size |
|--------------|---------|------|
| 0x00000000 - 0x00000FFF | Reserved | 4 KB |
| 0x00001000 - 0x000FFFFF | Code (.text) | 1020 KB |
| 0x00100000 - 0x001FFFFF | Data (.data) | 1 MB |
| 0x00200000 - 0x7FFEFFFF | Heap | ~2 GB |
| 0x7FFF0000 - 0x7FFFFFFF | Stack | 64 KB |

## Instruction Set Architecture

The A1M CPU implements a RISC instruction set with:
- **50+ instructions**
- **3 instruction formats**: R-type, I-type, J-type
- **32 general-purpose registers** (R0-R31)
- **64-bit data path**
- **32-bit instruction width**

See `docs/ISA.md` for complete instruction reference.

## Summary

The A1M toolchain provides a complete flow from high-level Algo code to hardware execution:

1. **Design** hardware in Verilog
2. **Write** programs in Algo
3. **Compile** to assembly
4. **Assemble** to binary
5. **Execute** in emulator or on FPGA
6. **Debug** and visualize in GUI

All components are integrated and work together seamlessly!
