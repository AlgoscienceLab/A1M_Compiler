#!/bin/bash
# Script to compile and run all Algo examples

echo "=== Testing Algo Compiler ===="
echo ""

# Array of example files
examples=(
    "countdown"
    "sum_range"
)

for example in "${examples[@]}"; do
    echo "--- $example ---"
    ./compiler/algo-compiler examples/algo/${example}.algo -o examples/asm/${example}.asm
    if [ $? -eq 0 ]; then
        ./assembler/a1m-asm examples/asm/${example}.asm -o examples/bin/${example}.bin
        if [ $? -eq 0 ]; then
            echo "Output:"
            ./emulator/a1m-emu examples/bin/${example}.bin
            echo ""
        fi
    fi
    echo ""
done
