#!/bin/bash
# Build script for A1M Compiler on macOS
# This script builds all components of the A1M toolchain

set -e  # Exit on error

echo "========================================"
echo "Building A1M Compiler Toolchain"
echo "Platform: macOS"
echo "========================================"
echo ""

# Check if GCC or Clang is available
if ! command -v gcc &> /dev/null && ! command -v clang &> /dev/null; then
    echo "ERROR: No C compiler found"
    echo "Please install Xcode Command Line Tools:"
    echo "  xcode-select --install"
    exit 1
fi

echo "Compiler found:"
if command -v gcc &> /dev/null; then
    gcc --version | head -n 1
elif command -v clang &> /dev/null; then
    clang --version | head -n 1
fi
echo ""

# Build Compiler
echo "[1/4] Building Algo Compiler..."
cd compiler
make clean > /dev/null 2>&1 || true
make
cd ..
echo ""

# Build Assembler
echo "[2/4] Building A1M Assembler..."
cd assembler
make clean > /dev/null 2>&1 || true
make
cd ..
echo ""

# Build Emulator
echo "[3/4] Building A1M Emulator..."
cd emulator
make clean > /dev/null 2>&1 || true
make
cd ..
echo ""

# Build GUI Console
echo "[4/4] Building A1M Console..."
cd gui-console
make clean > /dev/null 2>&1 || true
make
cd ..
echo ""

echo "========================================"
echo "Build completed successfully!"
echo "========================================"
echo ""
echo "Built executables:"
echo "  - compiler/algo-compiler"
echo "  - assembler/a1m-asm"
echo "  - emulator/a1m-emu"
echo "  - gui-console/a1m-console"
echo ""
echo "To test the installation, run:"
echo "  ./compiler/algo-compiler --version"
echo ""
