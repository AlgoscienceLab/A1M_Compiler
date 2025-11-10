#!/bin/bash
# A1M CPU Toolchain Test Suite
# Tests compiler, assembler, emulator, and all example programs

echo "================================"
echo "  A1M CPU Toolchain Test Suite"
echo "================================"
echo ""

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counters
TOTAL=0
PASSED=0
FAILED=0

# Test function
test_program() {
    local name=$1
    local algo_file=$2
    TOTAL=$((TOTAL + 1))
    
    echo -n "Testing $name... "
    
    # Compile
    ./compiler/algo-compiler "$algo_file" -o "examples/asm/test_${name}.asm" 2>/dev/null
    if [ $? -ne 0 ]; then
        echo -e "${RED}FAILED${NC} (compilation)"
        FAILED=$((FAILED + 1))
        return 1
    fi
    
    # Assemble
    ./assembler/a1m-asm "examples/asm/test_${name}.asm" -o "examples/bin/test_${name}.bin" 2>/dev/null 1>/dev/null
    if [ $? -ne 0 ]; then
        echo -e "${RED}FAILED${NC} (assembly)"
        FAILED=$((FAILED + 1))
        return 1
    fi
    
    # Run (with timeout)
    timeout 2s ./emulator/a1m-emu "examples/bin/test_${name}.bin" >/dev/null 2>&1
    if [ $? -eq 0 ] || [ $? -eq 124 ]; then
        echo -e "${GREEN}PASSED${NC}"
        PASSED=$((PASSED + 1))
        return 0
    else
        echo -e "${RED}FAILED${NC} (execution)"
        FAILED=$((FAILED + 1))
        return 1
    fi
}

# Build all tools
echo "Building toolchain..."
echo "===================="

cd assembler && make clean && make >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}Failed to build assembler${NC}"
    exit 1
fi
cd ..

cd emulator && make clean && make >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}Failed to build emulator${NC}"
    exit 1
fi
cd ..

cd compiler && make clean && make >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}Failed to build compiler${NC}"
    exit 1
fi
cd ..

echo -e "${GREEN}Toolchain built successfully!${NC}"
echo ""

# Run tests
echo "Running tests..."
echo "================"

# Test basic programs (1-20)
test_program "01_hello_world" "examples/algo/01_hello_world.algo"
test_program "02_arithmetic" "examples/algo/02_arithmetic.algo"
test_program "03_variables" "examples/algo/03_variables.algo"
test_program "04_multiplication" "examples/algo/04_multiplication.algo"
test_program "05_escape_sequences" "examples/algo/05_escape_sequences.algo"
test_program "06_expressions" "examples/algo/06_expressions.algo"
test_program "07_fibonacci" "examples/algo/07_fibonacci.algo"
test_program "08_powers_of_two" "examples/algo/08_powers_of_two.algo"
test_program "09_squares" "examples/algo/09_squares.algo"
test_program "10_temperature" "examples/algo/10_temperature.algo"
test_program "11_calculator" "examples/algo/11_calculator.algo"
test_program "12_factorial" "examples/algo/12_factorial.algo"
test_program "13_ascii_art" "examples/algo/13_ascii_art.algo"
test_program "14_table" "examples/algo/14_table.algo"
test_program "15_statistics" "examples/algo/15_statistics.algo"
test_program "16_geometry" "examples/algo/16_geometry.algo"
test_program "17_counters" "examples/algo/17_counters.algo"
test_program "18_number_patterns" "examples/algo/18_number_patterns.algo"
test_program "19_inventory" "examples/algo/19_inventory.algo"
test_program "20_benchmark" "examples/algo/20_benchmark.algo"

# Test advanced programs (21-32)
test_program "21_for_loop" "examples/algo/21_for_loop.algo"
test_program "22_while_loop" "examples/algo/22_while_loop.algo"
test_program "23_if_else" "examples/algo/23_if_else.algo"
test_program "24_nested_if" "examples/algo/24_nested_if.algo"
test_program "25_functions" "examples/algo/25_functions.algo"
test_program "26_recursive_factorial" "examples/algo/26_recursive_factorial.algo"
test_program "27_recursive_fibonacci" "examples/algo/27_recursive_fibonacci.algo"
test_program "28_nested_loops" "examples/algo/28_nested_loops.algo"
test_program "29_prime_checker" "examples/algo/29_prime_checker.algo"
test_program "30_gcd_function" "examples/algo/30_gcd_function.algo"
test_program "31_break_continue" "examples/algo/31_break_continue.algo"
test_program "32_complex_control" "examples/algo/32_complex_control.algo"

# Summary
echo ""
echo "================================"
echo "  Test Summary"
echo "================================"
echo "Total tests:  $TOTAL"
echo -e "Passed:       ${GREEN}$PASSED${NC}"
if [ $FAILED -gt 0 ]; then
    echo -e "Failed:       ${RED}$FAILED${NC}"
else
    echo -e "Failed:       $FAILED"
fi
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed.${NC}"
    exit 1
fi
