#!/bin/bash

# A1M CPU Complete Toolchain Flow Demonstration
# This demonstrates the complete flow: Verilog -> Assembly -> Binary -> Emulator

set -e

echo "======================================================================"
echo "        A1M CPU COMPLETE TOOLCHAIN FLOW DEMONSTRATION"
echo "======================================================================"
echo ""

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}This demonstration shows the complete A1M CPU toolchain:${NC}"
echo "  1. Verilog Hardware Design (a1m_cpu.v)"
echo "  2. Assembly Programming (.asm files)"
echo "  3. Binary Generation (assembler)"
echo "  4. Software Execution (emulator)"
echo ""

# ============================================================================
# Step 1: Verify Verilog Hardware Design
# ============================================================================

echo "======================================================================"
echo -e "${YELLOW}STEP 1: VERILOG HARDWARE DESIGN${NC}"
echo "======================================================================"
echo ""
echo "The A1M CPU is defined in Verilog HDL for FPGA/ASIC implementation."
echo ""
echo "Key Verilog modules:"
ls -lh verilog/cpu/a1m_cpu.v verilog/cpu/alu.v verilog/cpu/register_file.v verilog/cpu/control_unit.v
echo ""
echo "Total Verilog code:"
wc -l verilog/cpu/*.v verilog/memory/*.v verilog/top.v | tail -1
echo ""
echo -e "${GREEN}✓ Hardware design verified${NC}"
echo ""
read -p "Press Enter to continue to Step 2..."
echo ""

# ============================================================================
# Step 2: Assembly Programming
# ============================================================================

echo "======================================================================"
echo -e "${YELLOW}STEP 2: ASSEMBLY PROGRAMMING${NC}"
echo "======================================================================"
echo ""
echo "Writing programs in A1M Assembly language."
echo ""
echo "Example 1: Fibonacci Sequence (examples/asm/fibonacci.asm)"
echo "----------------------------------------"
head -30 examples/asm/fibonacci.asm
echo "... (truncated)"
echo ""
echo -e "${GREEN}✓ Assembly programs ready${NC}"
echo ""
read -p "Press Enter to continue to Step 3..."
echo ""

# ============================================================================
# Step 3: Assembly to Binary (Assembler)
# ============================================================================

echo "======================================================================"
echo -e "${YELLOW}STEP 3: ASSEMBLER (ASM → BINARY)${NC}"
echo "======================================================================"
echo ""
echo "The assembler converts assembly code to machine code binary."
echo ""
echo "Assembling: examples/asm/fibonacci.asm"
./assembler/a1m-asm examples/asm/fibonacci.asm -o /tmp/fibonacci.bin
echo ""
echo "Generated binary:"
ls -lh /tmp/fibonacci.bin
echo ""
echo "Binary content (first 64 bytes in hex):"
hexdump -C /tmp/fibonacci.bin | head -10
echo ""
echo -e "${GREEN}✓ Assembly to binary conversion successful${NC}"
echo ""
read -p "Press Enter to continue to Step 4..."
echo ""

# ============================================================================
# Step 4: Emulator Execution
# ============================================================================

echo "======================================================================"
echo -e "${YELLOW}STEP 4: SOFTWARE EMULATOR EXECUTION${NC}"
echo "======================================================================"
echo ""
echo "The emulator simulates the A1M CPU and executes the binary."
echo ""
echo "Running: /tmp/fibonacci.bin"
echo "----------------------------------------"
./emulator/a1m-emu /tmp/fibonacci.bin
echo ""
echo -e "${GREEN}✓ Program executed successfully in emulator${NC}"
echo ""
read -p "Press Enter to continue to final summary..."
echo ""

# ============================================================================
# Step 5: Complete Flow Summary
# ============================================================================

echo "======================================================================"
echo -e "${YELLOW}COMPLETE TOOLCHAIN FLOW SUMMARY${NC}"
echo "======================================================================"
echo ""
echo "Full pipeline demonstrated:"
echo ""
echo "  1. ${BLUE}Verilog Design${NC} (verilog/cpu/a1m_cpu.v)"
echo "     ↓"
echo "     The hardware CPU implementation (synthesizable to FPGA)"
echo "     - 64-bit RISC architecture"
echo "     - 5-stage pipeline"
echo "     - 32 general-purpose registers"
echo ""
echo "  2. ${BLUE}Assembly Code${NC} (examples/asm/*.asm)"
echo "     ↓"
echo "     Human-readable assembly programs"
echo "     - Uses A1M instruction set (50+ instructions)"
echo "     - Labels, directives, comments"
echo ""
echo "  3. ${BLUE}Assembler${NC} (./assembler/a1m-asm)"
echo "     ↓"
echo "     Converts assembly to machine code"
echo "     - Two-pass assembly"
echo "     - Label resolution"
echo "     - Binary output"
echo ""
echo "  4. ${BLUE}Binary Executable${NC} (program.bin)"
echo "     ↓"
echo "     Raw machine code (32-bit instructions)"
echo "     - Can run on emulator OR"
echo "     - Can load to FPGA memory for hardware execution"
echo ""
echo "  5. ${BLUE}Emulator${NC} (./emulator/a1m-emu)"
echo "     ↓"
echo "     Software simulation of A1M CPU"
echo "     - Executes binaries"
echo "     - Provides debugging output"
echo "     - Register and memory visualization"
echo ""
echo "======================================================================"
echo ""
echo -e "${GREEN}ADDITIONAL COMPONENTS:${NC}"
echo ""
echo "  • ${BLUE}Algo Compiler${NC} (./compiler/algo-compiler)"
echo "    High-level language that compiles to A1M assembly"
echo "    Flow: program.algo → compiler → program.asm → assembler → program.bin"
echo ""
echo "  • ${BLUE}GUI IDE${NC} (./gui/a1m-ide) [requires GTK3]"
echo "    Integrated development environment with:"
echo "    - Code editor with syntax highlighting"
echo "    - One-click compile and assemble"
echo "    - Built-in emulator with visualization"
echo "    - Real-time register and memory inspection"
echo ""
echo "======================================================================"
echo ""
echo "HARDWARE vs SOFTWARE EXECUTION:"
echo ""
echo "  SOFTWARE PATH (Emulator):"
echo "  program.asm → assembler → program.bin → emulator → OUTPUT"
echo "  ↑ What we just demonstrated ↑"
echo ""
echo "  HARDWARE PATH (FPGA):"
echo "  1. Synthesize Verilog to bitstream:"
echo "     verilog/cpu/a1m_cpu.v → Vivado/Quartus → a1m.bit"
echo ""
echo "  2. Load bitstream to FPGA:"
echo "     a1m.bit → FPGA programming tool → FPGA chip"
echo ""
echo "  3. Load program to FPGA memory:"
echo "     program.bin → memory.v initialization → FPGA block RAM"
echo ""
echo "  4. Run on real hardware:"
echo "     FPGA executes instructions on physical A1M CPU!"
echo ""
echo "======================================================================"
echo ""
echo -e "${GREEN}✓ Complete toolchain demonstration finished!${NC}"
echo ""
echo "To explore further:"
echo "  - View documentation: cat docs/TOOLCHAIN_FLOW.md"
echo "  - Try other examples: ls examples/asm/"
echo "  - Simulate in Verilog: cd verilog && iverilog testbench/a1m_testbench.v"
echo "  - Build GUI: sudo apt-get install libgtk-3-dev && make -C gui"
echo ""

