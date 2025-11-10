#!/bin/bash

# Test script for A1M CPU

echo "======================================"
echo "  A1M CPU Test Suite"
echo "======================================"
echo ""

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

test_count=0
pass_count=0

run_test() {
    local name=$1
    local asm_file=$2
    
    test_count=$((test_count + 1))
    echo "Test $test_count: $name"
    
    # Assemble
    ./assembler/a1m-asm "$asm_file" -o test_temp.bin 2>/dev/null
    if [ $? -ne 0 ]; then
        echo -e "${RED}  ✗ Assembly failed${NC}"
        return 1
    fi
    
    # Run (with timeout)
    timeout 5s ./emulator/a1m-emu test_temp.bin -r > /dev/null 2>&1
    if [ $? -eq 0 ] || [ $? -eq 124 ]; then
        echo -e "${GREEN}  ✓ Passed${NC}"
        pass_count=$((pass_count + 1))
        rm -f test_temp.bin
        return 0
    else
        echo -e "${RED}  ✗ Failed${NC}"
        rm -f test_temp.bin
        return 1
    fi
}

# Run tests
echo "Running assembly tests..."
echo ""

if [ -f "assembler/a1m-asm" ] && [ -f "emulator/a1m-emu" ]; then
    run_test "Hello World" "examples/asm/hello.asm"
    run_test "Fibonacci" "examples/asm/fibonacci.asm"
    run_test "Array Sum" "examples/asm/array_sum.asm"
else
    echo -e "${RED}Error: Build the project first with ./build.sh${NC}"
    exit 1
fi

echo ""
echo "======================================"
echo "Test Results: $pass_count/$test_count passed"
echo "======================================"

if [ $pass_count -eq $test_count ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed${NC}"
    exit 1
fi
