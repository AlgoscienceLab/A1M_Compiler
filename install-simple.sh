#!/bin/bash
# Simple Install Script - No color codes, minimal checks
# Run from A1M_Compiler directory

echo "========================================="
echo "A1M Compiler Installation"
echo "========================================="
echo ""

# Install make if needed
if ! command -v make &> /dev/null; then
    echo "Installing make..."
    pacman -S --noconfirm make mingw-w64-x86_64-make
fi

# Build components
echo ""
echo "[1/4] Building Compiler..."
cd compiler && make clean 2>&1 | head -1 && make && cd ..

echo ""
echo "[2/4] Building Assembler..."
cd assembler && make clean 2>&1 | head -1 && make && cd ..

echo ""
echo "[3/4] Building Emulator..."
cd emulator && make clean 2>&1 | head -1 && make && cd ..

echo ""
echo "[4/4] Building Console..."
cd gui-console && make clean 2>&1 | head -1 && make && cd ..

echo ""
echo "========================================="
echo "Installing to /usr/local/bin..."
echo "========================================="
echo ""

cd compiler && make install && cd ..
cd assembler && make install && cd ..
cd emulator && make install && cd ..
cd gui-console && make install && cd ..

echo ""
echo "========================================="
echo "Installation Complete!"
echo "========================================="
echo ""
echo "Testing..."
algo-compiler.exe examples/algo/01_hello_world.algo -o test.asm
a1m-asm.exe test.asm -o test.bin
a1m-emu.exe test.bin
rm -f test.asm test.bin

echo ""
echo "Done! Tools are now available globally."
echo ""
