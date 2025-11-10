#!/bin/bash

# A1M Run - One-command wrapper for the full Algo toolchain
# Compiles, assembles, and runs an Algo program

set -e

COLOR_GREEN='\033[0;32m'
COLOR_BLUE='\033[0;34m'
COLOR_RED='\033[0;31m'
COLOR_RESET='\033[0m'

if [ $# -lt 1 ]; then
    echo "Usage: algo-run <input.algo> [options]"
    echo
    echo "This command will:"
    echo "  1. Compile .algo to .asm"
    echo "  2. Assemble .asm to .bin"
    echo "  3. Run .bin on the emulator"
    echo
    echo "Options:"
    echo "  --keep-files    Keep intermediate .asm and .bin files"
    echo "  --asm-only      Only compile to assembly (don't assemble or run)"
    echo "  --bin-only      Compile and assemble (don't run)"
    echo
    echo "Examples:"
    echo "  algo-run myprogram.algo"
    echo "  algo-run myprogram.algo --keep-files"
    echo "  algo-run myprogram.algo --asm-only"
    exit 1
fi

INPUT_FILE="$1"
KEEP_FILES=false
ASM_ONLY=false
BIN_ONLY=false

# Parse options
shift
while [ $# -gt 0 ]; do
    case "$1" in
        --keep-files)
            KEEP_FILES=true
            ;;
        --asm-only)
            ASM_ONLY=true
            KEEP_FILES=true
            ;;
        --bin-only)
            BIN_ONLY=true
            KEEP_FILES=true
            ;;
        *)
            echo -e "${COLOR_RED}Unknown option: $1${COLOR_RESET}"
            exit 1
            ;;
    esac
    shift
done

# Check if input file exists
if [ ! -f "$INPUT_FILE" ]; then
    echo -e "${COLOR_RED}Error: File not found: $INPUT_FILE${COLOR_RESET}"
    exit 1
fi

# Check if input file has .algo extension
if [[ ! "$INPUT_FILE" =~ \.algo$ ]]; then
    echo -e "${COLOR_RED}Error: Input file must have .algo extension${COLOR_RESET}"
    exit 1
fi

# Get base filename without extension
BASENAME="${INPUT_FILE%.algo}"
ASM_FILE="${BASENAME}.asm"
BIN_FILE="${BASENAME}.bin"

# Compile to assembly
echo -e "${COLOR_BLUE}[1/3] Compiling...${COLOR_RESET}"
algo "$INPUT_FILE" -o "$ASM_FILE"

if [ "$ASM_ONLY" = true ]; then
    echo -e "${COLOR_GREEN}✓ Assembly file generated: $ASM_FILE${COLOR_RESET}"
    exit 0
fi

# Assemble to binary
echo -e "${COLOR_BLUE}[2/3] Assembling...${COLOR_RESET}"
a1m-asm "$ASM_FILE" -o "$BIN_FILE"

if [ "$BIN_ONLY" = true ]; then
    echo -e "${COLOR_GREEN}✓ Binary file generated: $BIN_FILE${COLOR_RESET}"
    exit 0
fi

# Run emulator
echo -e "${COLOR_BLUE}[3/3] Running...${COLOR_RESET}"
echo -e "${COLOR_BLUE}────────────────────────────────${COLOR_RESET}"
a1m-emu "$BIN_FILE"
echo -e "${COLOR_BLUE}────────────────────────────────${COLOR_RESET}"

# Clean up intermediate files if requested
if [ "$KEEP_FILES" = false ]; then
    rm -f "$ASM_FILE" "$BIN_FILE"
    echo -e "${COLOR_GREEN}✓ Cleaned up intermediate files${COLOR_RESET}"
else
    echo -e "${COLOR_GREEN}✓ Kept files: $ASM_FILE, $BIN_FILE${COLOR_RESET}"
fi
