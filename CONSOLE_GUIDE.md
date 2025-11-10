╔══════════════════════════════════════════════════════════════════╗
║                   A1M CPU CONSOLE - Quick Reference              ║
║                  100% Custom C Implementation                    ║
╚══════════════════════════════════════════════════════════════════╝

┌──────────────────────────────────────────────────────────────────┐
│ LAUNCHING THE CONSOLE                                            │
└──────────────────────────────────────────────────────────────────┘

  Interactive Mode:
    ./console.sh

  Quick Run Mode:
    ./console.sh <filename>

  Examples:
    ./console.sh examples/asm/hello.asm
    ./console.sh examples/algo/hello.algo
    ./console.sh output.bin


┌──────────────────────────────────────────────────────────────────┐
│ MENU OPTIONS                                                     │
└──────────────────────────────────────────────────────────────────┘

  [1] Run Algo Program
      • Compiles .algo → .asm → .bin
      • Runs on A1M emulator
      • Shows full execution details

  [2] Run Assembly
      • Assembles .asm → .bin
      • Runs on A1M emulator
      • Shows assembly process

  [3] Run Binary
      • Runs pre-assembled .bin directly
      • Shows execution output

  [4] View Last Output
      • Displays previous program output
      • Useful for reviewing results

  [5] Help
      • Detailed help about A1M CPU
      • Workflow explanation
      • Usage examples

  [6] Exit
      • Close the console


┌──────────────────────────────────────────────────────────────────┐
│ WORKFLOW                                                         │
└──────────────────────────────────────────────────────────────────┘

  Algo Program (.algo)
       ↓
   [Algo Compiler] → Assembly (.asm)
       ↓
   [Assembler] → Binary (.bin)
       ↓
   [A1M Emulator] → Output


┌──────────────────────────────────────────────────────────────────┐
│ EXAMPLE SESSION                                                  │
└──────────────────────────────────────────────────────────────────┘

  $ ./console.sh

  ╔═══════════════════════════════════════════════════════════════╗
  ║      A1M CPU Console - Algo Development Environment          ║
  ║                Custom 64-bit CPU Emulator                     ║
  ╚═══════════════════════════════════════════════════════════════╝

  ┌───────────────────────────────────────────────────────────────┐
  │ [1] Run Algo   [2] Run Assembly   [3] Run Binary             │
  │ [4] Last Out   [5] Help           [6] Exit                   │
  └───────────────────────────────────────────────────────────────┘

  Your choice: 1

  Enter .algo filename: examples/algo/hello.algo

  📝 Step 1: Compiling Algo → Assembly...
  ✓ Compilation successful

  ⚙️  Step 2: Assembling Assembly → Binary...
  ✓ Assembly successful

  🚀 Step 3: Running on A1M CPU Emulator...
  [Program output appears here]

  ✓ Execution complete


┌──────────────────────────────────────────────────────────────────┐
│ FILE TYPES                                                       │
└──────────────────────────────────────────────────────────────────┘

  .algo  →  Algo high-level language source
  .asm   →  A1M assembly language
  .bin   →  A1M machine code binary


┌──────────────────────────────────────────────────────────────────┐
│ EXAMPLE FILES                                                    │
└──────────────────────────────────────────────────────────────────┘

  Assembly:
    examples/asm/hello.asm       - Hello world
    examples/asm/fibonacci.asm   - Fibonacci sequence
    examples/asm/math.asm        - Math operations

  Algo:
    examples/algo/hello.algo     - Hello world
    examples/algo/variables.algo - Variable usage
    examples/algo/functions.algo - Function definitions


┌──────────────────────────────────────────────────────────────────┐
│ A1M CPU ARCHITECTURE                                             │
└──────────────────────────────────────────────────────────────────┘

  Type:       64-bit RISC
  Registers:  32 GPRs (R0-R31)
  Pipeline:   5 stages (IF/ID/EX/MEM/WB)
  Instructions: 50+ opcodes
  Memory:     64-bit addressable


┌──────────────────────────────────────────────────────────────────┐
│ TOOLCHAIN COMPONENTS                                             │
└──────────────────────────────────────────────────────────────────┘

  emulator/a1m-emu
    • Software emulation of A1M CPU
    • Executes .bin machine code
    • Shows execution statistics

  assembler/a1m-asm
    • Converts .asm → .bin
    • Two-pass assembly
    • Label resolution

  compiler/algo-compiler
    • Converts .algo → .asm
    • High-level to assembly
    • Custom language for A1M

  gui-console/a1m-console
    • Terminal-based development environment
    • Integrated workflow
    • Pure C, no dependencies


┌──────────────────────────────────────────────────────────────────┐
│ TIPS & TRICKS                                                    │
└──────────────────────────────────────────────────────────────────┘

  • Use Quick Run mode to test files quickly
  • Press [4] to review previous output without re-running
  • All compilation steps are shown for transparency
  • Errors display detailed information for debugging
  • Output is saved to /tmp/a1m_last_output.txt


┌──────────────────────────────────────────────────────────────────┐
│ TROUBLESHOOTING                                                  │
└──────────────────────────────────────────────────────────────────┘

  "A1M emulator not found"
    → Run ./build.sh first

  "Compilation failed"
    → Check .algo syntax
    → View compiler output for details

  "Assembly failed"
    → Check .asm syntax
    → Verify instruction names
    → Check label definitions

  "Execution failed"
    → Binary may be invalid
    → Check program logic
    → Review assembler output


┌──────────────────────────────────────────────────────────────────┐
│ WHY IS THIS CUSTOM?                                              │
└──────────────────────────────────────────────────────────────────┘

  ✓ Written in pure C (no Python, JavaScript, etc.)
  ✓ No external GUI frameworks (no GTK, Qt, ncurses)
  ✓ No third-party libraries
  ✓ Designed specifically for A1M CPU
  ✓ Integrated with custom toolchain
  ✓ Optimized for Algo language workflow
  ✓ Self-contained and portable


┌──────────────────────────────────────────────────────────────────┐
│ DOCUMENTATION                                                    │
└──────────────────────────────────────────────────────────────────┘

  gui-console/README.md     - Console documentation
  FLOW_GUIDE.md             - Complete workflow guide
  USAGE.md                  - Usage examples
  README.md                 - Project overview


╔══════════════════════════════════════════════════════════════════╗
║ For more information, select [5] Help from the console menu     ║
╚══════════════════════════════════════════════════════════════════╝
