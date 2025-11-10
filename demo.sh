#!/bin/bash

# Quick Demo Script for A1M CPU

echo "╔════════════════════════════════════════════╗"
echo "║   A1M CPU - Quick Demo                     ║"
echo "╔════════════════════════════════════════════╗"
echo ""

# Check if built
if [ ! -f "emulator/a1m-emu" ] || [ ! -f "assembler/a1m-asm" ]; then
    echo "Building project first..."
    ./build.sh
    echo ""
fi

echo "Demo 1: Hello World"
echo "-------------------"
echo "Assembling hello.asm..."
./assembler/a1m-asm examples/asm/hello.asm -o demo_hello.bin
echo ""
echo "Running in emulator:"
./emulator/a1m-emu demo_hello.bin
echo ""

echo "Demo 2: Fibonacci (with register dump)"
echo "--------------------------------------"
echo "Assembling fibonacci.asm..."
./assembler/a1m-asm examples/asm/fibonacci.asm -o demo_fib.bin
echo ""
echo "Running in emulator:"
./emulator/a1m-emu demo_fib.bin -r
echo ""

echo "Demo 3: Array Sum"
echo "-----------------"
echo "Assembling array_sum.asm..."
./assembler/a1m-asm examples/asm/array_sum.asm -o demo_sum.bin
echo ""
echo "Running in emulator:"
./emulator/a1m-emu demo_sum.bin
echo ""

# Cleanup
rm -f demo_*.bin

echo "╔════════════════════════════════════════════╗"
echo "║   Demo Complete!                           ║"
echo "╚════════════════════════════════════════════╝"
echo ""
echo "Try these commands yourself:"
echo "  ./assembler/a1m-asm examples/asm/fibonacci.asm -o fib.bin"
echo "  ./emulator/a1m-emu fib.bin -d"
echo ""
echo "Or launch the GUI:"
echo "  ./gui/a1m-gui"
echo ""
