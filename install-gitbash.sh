#!/bin/bash
# Git Bash Compatible Install Script
# Uses mingw32-make instead of make

echo "========================================="
echo "A1M Compiler Installation (Git Bash)"
echo "========================================="
echo ""

# Use mingw32-make from MSYS2
MAKE=/c/msys64/mingw64/bin/mingw32-make

if [ ! -f "$MAKE" ]; then
    echo "ERROR: mingw32-make not found at $MAKE"
    echo ""
    echo "Please either:"
    echo "  1. Open 'MSYS2 MinGW 64-bit' terminal (not Git Bash)"
    echo "  2. Or install MSYS2 from: https://www.msys2.org/"
    exit 1
fi

echo "Using: $MAKE"
echo ""

# Force use of bash shell for make (not CMD)
export SHELL=/bin/bash

# Build components
echo "[1/4] Building Compiler..."
cd compiler
$MAKE clean > /dev/null 2>&1
# Build with bash shell
$MAKE SHELL=/bin/bash
if [ ! -f "algo-compiler.exe" ]; then
    echo "ERROR: Failed to build compiler"
    exit 1
fi
echo "✓ Built: algo-compiler.exe"
cd ..

echo ""
echo "[2/4] Building Assembler..."
cd assembler
$MAKE clean > /dev/null 2>&1
$MAKE SHELL=/bin/bash
if [ ! -f "a1m-asm.exe" ]; then
    echo "ERROR: Failed to build assembler"
    exit 1
fi
echo "✓ Built: a1m-asm.exe"
cd ..

echo ""
echo "[3/4] Building Emulator..."
cd emulator
$MAKE clean > /dev/null 2>&1
$MAKE SHELL=/bin/bash
if [ ! -f "a1m-emu.exe" ]; then
    echo "ERROR: Failed to build emulator"
    exit 1
fi
echo "✓ Built: a1m-emu.exe"
cd ..

echo ""
echo "[4/4] Building Console..."
cd gui-console
$MAKE clean > /dev/null 2>&1
$MAKE SHELL=/bin/bash
if [ ! -f "a1m-console.exe" ]; then
    echo "ERROR: Failed to build console"
    exit 1
fi
echo "✓ Built: a1m-console.exe"
cd ..

echo ""
echo "========================================="
echo "Build Complete!"
echo "========================================="
echo ""
echo "Built executables:"
echo "  - compiler/algo-compiler.exe"
echo "  - assembler/a1m-asm.exe"
echo "  - emulator/a1m-emu.exe"
echo "  - gui-console/a1m-console.exe"
echo ""

# Test
echo "Testing with hello_world.algo..."
./compiler/algo-compiler.exe examples/algo/01_hello_world.algo -o test.asm
./assembler/a1m-asm.exe test.asm -o test.bin
echo ""
echo "Program output:"
echo "---"
./emulator/a1m-emu.exe test.bin
echo "---"
echo ""
rm -f test.asm test.bin

echo "✓ Test successful!"
echo ""

# Optional: Install to MSYS2's /usr/local/bin
echo "Would you like to install globally? (y/n)"
read -r response

if [[ "$response" =~ ^[Yy]$ ]]; then
    echo ""
    echo "Installing to /c/msys64/usr/local/bin..."
    
    INSTALL_DIR="/c/msys64/usr/local/bin"
    mkdir -p "$INSTALL_DIR"
    
    cp compiler/algo-compiler.exe "$INSTALL_DIR/"
    cp assembler/a1m-asm.exe "$INSTALL_DIR/"
    cp emulator/a1m-emu.exe "$INSTALL_DIR/"
    cp gui-console/a1m-console.exe "$INSTALL_DIR/"
    
    echo ""
    echo "✓ Installed to $INSTALL_DIR"
    echo ""
    echo "Add this to your PATH to use from anywhere:"
    echo "  export PATH=\"$INSTALL_DIR:\$PATH\""
    echo ""
    echo "Or add to ~/.bashrc for permanent access"
else
    echo ""
    echo "Skipping global installation."
    echo "You can run tools from their directories:"
    echo "  ./compiler/algo-compiler.exe"
    echo "  ./assembler/a1m-asm.exe"
    echo "  ./emulator/a1m-emu.exe"
fi

echo ""
echo "Done!"
echo ""
