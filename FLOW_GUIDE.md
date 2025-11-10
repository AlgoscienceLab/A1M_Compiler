# A1M CPU Toolchain - Quick Reference Flow

## THE COMPLETE FLOW

```
┌─────────────────────────────────────────────────────────────────┐
│                                                                 │
│              A1M CPU DEVELOPMENT TOOLCHAIN                      │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘


LEVEL 1: HARDWARE (Verilog)
═══════════════════════════════════════════════════════════════════
📁 verilog/cpu/a1m_cpu.v  (8.9 KB)
📁 verilog/cpu/alu.v      (3.7 KB)
📁 verilog/cpu/register_file.v
📁 verilog/cpu/control_unit.v
📁 verilog/memory/memory.v

→ Tools: iverilog (simulation), Vivado/Quartus (FPGA synthesis)
→ Output: Bitstream for FPGA or testbench waveforms


LEVEL 2: HIGH-LEVEL LANGUAGE (Algo)
═══════════════════════════════════════════════════════════════════
📝 examples/algo/hello.algo
📝 examples/algo/fibonacci.algo

Example:
    func main() -> int {
        let x: int = 42;
        print(x);
        return 0;
    }

     ↓ [./compiler/algo-compiler]
     
📄 output.asm (A1M Assembly)


LEVEL 3: ASSEMBLY LANGUAGE
═══════════════════════════════════════════════════════════════════
📄 examples/asm/hello.asm
📄 examples/asm/fibonacci.asm

Example:
    .text
    main:
        ADDI R1, R0, 42    # R1 = 42
        SW R1, 0(R2)       # Store R1 to memory
        HALT               # Stop execution

     ↓ [./assembler/a1m-asm]
     
💾 output.bin (Machine Code Binary)


LEVEL 4: BINARY EXECUTABLE
═══════════════════════════════════════════════════════════════════
💾 program.bin (Raw 32-bit instructions)

Hex dump:
    00000000: 20 01 00 2a  ac 02 00 00  00 00 00 00
              [ADDI inst]  [SW inst]    [HALT]

     ↓ Two execution paths:
     
     PATH A: Software         PATH B: Hardware
     ↓                        ↓


LEVEL 5a: SOFTWARE EMULATOR
═══════════════════════════════════════════════════════════════════
💻 ./emulator/a1m-emu program.bin

Features:
  ✓ Simulates A1M CPU in software
  ✓ Executes all 50+ instructions
  ✓ 64-bit register emulation
  ✓ Memory management
  ✓ Debug output
  ✓ System call handling

Output: Program results, register states


LEVEL 5b: HARDWARE EXECUTION
═══════════════════════════════════════════════════════════════════
🔌 FPGA/ASIC with synthesized A1M CPU

Process:
  1. Synthesize Verilog → Bitstream
  2. Program FPGA with bitstream
  3. Load program.bin to FPGA memory
  4. Execute on real hardware

Output: Real hardware execution!


LEVEL 6: GUI INTEGRATED DEVELOPMENT ENVIRONMENT
═══════════════════════════════════════════════════════════════════
🖥️  ./gui/a1m-ide

Features:
  📝 Code Editor (Algo/Assembly)
  🔨 Integrated Compiler
  🔧 Integrated Assembler
  ⚙️  Built-in Emulator
  👁️  Register Viewer
  💾 Memory Inspector
  📊 Real-time Visualization
  🐛 Debugging Tools

One-click: Write → Compile → Assemble → Run → Debug
```

## QUICK START GUIDE

### Option 1: Direct Assembly Programming
```bash
# 1. Write assembly
vim my_program.asm

# 2. Assemble
./assembler/a1m-asm my_program.asm -o my_program.bin

# 3. Run
./emulator/a1m-emu my_program.bin
```

### Option 2: High-Level Algo Programming
```bash
# 1. Write Algo code
vim my_program.algo

# 2. Compile to assembly
./compiler/algo-compiler my_program.algo -o my_program.asm

# 3. Assemble to binary
./assembler/a1m-asm my_program.asm -o my_program.bin

# 4. Run
./emulator/a1m-emu my_program.bin
```

### Option 3: GUI Development (Easiest)
```bash
# Launch IDE
./gui/a1m-ide

# Then use GUI:
# File → New/Open → Write code
# Build → Compile (for .algo) → Assemble
# Debug → Run → Watch execution
```

### Option 4: Hardware Simulation
```bash
# Simulate in Verilog
cd verilog
iverilog -o sim testbench/a1m_testbench.v
vvp sim
gtkwave dump.vcd  # View waveforms
```

## FILE EXTENSIONS

| Extension | Description | Created By |
|-----------|-------------|------------|
| `.v` | Verilog HDL source | Hand-written |
| `.algo` | Algo source code | Hand-written |
| `.asm` | A1M assembly | Hand-written or compiler |
| `.bin` | Binary executable | Assembler |
| `.vcd` | Waveform dump | Verilog simulator |
| `.bit`/`.sof` | FPGA bitstream | Synthesis tools |

## COMPONENT STATUS

✅ **COMPLETE AND WORKING:**
- ✓ Verilog CPU (a1m_cpu.v) - 5-stage pipeline, 64-bit, 32 registers
- ✓ Assembler (a1m-asm) - Two-pass, all instructions supported
- ✓ Emulator (a1m-emu) - Full instruction execution
- ✓ Assembly examples (hello.asm, fibonacci.asm)
- ✓ Build system (build.sh, test.sh)
- ✓ Documentation (8 comprehensive docs)

🚧 **IN PROGRESS:**
- ⚠ Algo Compiler - Basic framework, needs code generation
- ⚠ GUI IDE - Structure complete, requires GTK3 for building

## VERIFIED FLOW TEST

```bash
# This has been tested and works:

examples/asm/fibonacci.asm
    ↓ [./assembler/a1m-asm]
fibonacci.bin (116 bytes)
    ↓ [./emulator/a1m-emu]
✓ Execution complete (29 instructions executed)
```

## NEXT STEPS

1. **For Software Development:**
   - Write assembly programs
   - Use assembler + emulator
   - Debug with emulator output

2. **For Hardware Testing:**
   - Simulate with iverilog
   - View waveforms with gtkwave
   - Synthesize for FPGA deployment

3. **For GUI Development:**
   - Install GTK3: `sudo apt-get install libgtk-3-dev`
   - Build GUI: `make -C gui`
   - Launch: `./gui/a1m-ide`

4. **For Algo Language:**
   - Enhance compiler code generation
   - Test with .algo examples
   - Integrate with GUI

## ARCHITECTURE SUMMARY

- **CPU**: 64-bit RISC, 5-stage pipeline
- **Registers**: 32 GPRs (R0-R31), R0 always 0
- **Instructions**: 50+ (arithmetic, logic, memory, control)
- **Memory**: 4GB addressable space
- **Formats**: R-type, I-type, J-type, M-type

See `docs/ISA.md` for complete instruction set reference.

## DEMONSTRATION

Run the interactive flow demonstration:
```bash
./flow_demo.sh
```

This shows the complete toolchain in action!
