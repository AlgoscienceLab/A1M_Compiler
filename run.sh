#!/usr/bin/env bash
# run.sh - Build and run A1M programs in the terminal emulator
# Usage:
#   ./run.sh program.algo      # Compile, assemble, and run
#   ./run.sh program.asm       # Assemble and run
#   ./run.sh program.bin       # Run binary directly
#   ./run.sh --gui program.asm # Try to launch GUI (may have library conflicts)

set -euo pipefail

PROJ_ROOT="$(cd "$(dirname "$0")" && pwd)"
GUI="$PROJ_ROOT/gui/a1m-ide"
COMPILER="$PROJ_ROOT/compiler/algo-compiler"
ASSEMBLER="$PROJ_ROOT/assembler/a1m-asm"
EMULATOR="$PROJ_ROOT/emulator/a1m-emu"

USE_GUI=false

# Parse options
if [ "$#" -gt 0 ] && [ "$1" = "--gui" ]; then
  USE_GUI=true
  shift
fi

if [ "$#" -eq 0 ]; then
  echo "Usage: $0 [--gui] <program.algo|program.asm|program.bin>"
  echo ""
  echo "Options:"
  echo "  --gui    Launch GUI IDE (may have library conflicts in snap environments)"
  echo ""
  echo "Examples:"
  echo "  $0 examples/algo/hello.algo       # Compile, assemble, run in terminal"
  echo "  $0 examples/asm/fibonacci.asm     # Assemble and run in terminal"
  echo "  $0 program.bin                    # Run binary in terminal"
  echo "  $0 --gui examples/asm/hello.asm   # Assemble and open in GUI"
  echo ""
  exit 0
fi

SRC="$1"

if [ ! -f "$SRC" ]; then
  echo "Error: File not found: $SRC"
  exit 1
fi

EXT="${SRC##*.}"
TMPBIN="/tmp/a1m_run_$$.bin"

case "$EXT" in
  algo)
    if [ ! -x "$COMPILER" ]; then
      echo "Error: Algo compiler not found: $COMPILER"
      echo "Build it with: ./build.sh"
      exit 1
    fi
    echo "═══════════════════════════════════════════════════════════"
    echo "  Compiling Algo: $SRC"
    echo "═══════════════════════════════════════════════════════════"
    TMPASM="/tmp/a1m_temp_$$.asm"
    "$COMPILER" "$SRC" -o "$TMPASM"
    echo ""
    echo "═══════════════════════════════════════════════════════════"
    echo "  Assembling: $TMPASM → $TMPBIN"
    echo "═══════════════════════════════════════════════════════════"
    "$ASSEMBLER" "$TMPASM" -o "$TMPBIN"
    BIN="$TMPBIN"
    ;;
  asm)
    echo "═══════════════════════════════════════════════════════════"
    echo "  Assembling: $SRC → $TMPBIN"
    echo "═══════════════════════════════════════════════════════════"
    "$ASSEMBLER" "$SRC" -o "$TMPBIN"
    BIN="$TMPBIN"
    ;;
  bin)
    echo "═══════════════════════════════════════════════════════════"
    echo "  Using binary: $SRC"
    echo "═══════════════════════════════════════════════════════════"
    BIN="$SRC"
    ;;
  *)
    echo "Error: Unknown file extension: .$EXT"
    echo "Supported: .algo, .asm, .bin"
    exit 1
    ;;
esac

echo ""

if [ "$USE_GUI" = true ]; then
  if [ ! -x "$GUI" ]; then
    echo "Error: GUI not found or not executable: $GUI"
    echo "Build it with: ./build.sh"
    exit 1
  fi
  
  echo "═══════════════════════════════════════════════════════════"
  echo "  Launching GUI with: $BIN"
  echo "═══════════════════════════════════════════════════════════"
  echo ""
  echo "Note: If you see library errors (snap/GTK conflicts), use:"
  echo "      $0 $SRC    (without --gui for terminal emulator)"
  echo ""
  
  # Try to launch GUI
  export GUI_A1M_BIN="$BIN"
  exec "$GUI"
else
  if [ ! -x "$EMULATOR" ]; then
    echo "Error: Emulator not found: $EMULATOR"
    echo "Build it with: ./build.sh"
    exit 1
  fi
  
  echo "═══════════════════════════════════════════════════════════"
  echo "  Running in Terminal Emulator"
  echo "═══════════════════════════════════════════════════════════"
  echo ""
  exec "$EMULATOR" "$BIN"
fi
