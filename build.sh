#!/bin/bash

# A1M CPU Project Build Script

set -e  # Exit on error

echo "======================================"
echo "  A1M CPU Project Build System"
echo "======================================"
echo ""

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Build function
build_component() {
    local name=$1
    local dir=$2
    
    echo -e "${BLUE}Building $name...${NC}"
    if [ -d "$dir" ]; then
        cd "$dir"
        if [ -f "Makefile" ]; then
            make clean
            make
            if [ $? -eq 0 ]; then
                echo -e "${GREEN}✓ $name built successfully${NC}"
            else
                echo -e "${RED}✗ $name build failed${NC}"
                return 1
            fi
        else
            echo -e "${RED}✗ No Makefile found in $dir${NC}"
            return 1
        fi
        cd - > /dev/null
    else
        echo -e "${RED}✗ Directory $dir not found${NC}"
        return 1
    fi
    echo ""
}

# Main build process
echo "Starting build process..."
echo ""

# Build emulator
build_component "Emulator" "emulator"

# Build assembler
build_component "Assembler" "assembler"

# Build compiler
build_component "Compiler" "compiler"

# Build A1M Console (pure C, no dependencies)
build_component "A1M Console" "gui-console"

echo "======================================"
echo -e "${GREEN}Build process complete!${NC}"
echo "======================================"
echo ""
echo "Built components:"
echo "  - emulator/a1m-emu          : CPU emulator"
echo "  - assembler/a1m-asm         : Assembler"
echo "  - compiler/algo-compiler    : Algo compiler"
echo "  - gui-console/a1m-console   : Terminal console (RECOMMENDED)"
echo ""
echo "Quick start:"
echo "  ./console.sh                     - Launch A1M Console (interactive)"
echo "  ./console.sh examples/asm/hello.asm  - Quick run mode"
echo ""
echo "Or use individual components:"
echo "  1. Assemble: ./assembler/a1m-asm examples/asm/hello.asm -o hello.bin"
echo "  2. Run: ./emulator/a1m-emu hello.bin"
echo ""
