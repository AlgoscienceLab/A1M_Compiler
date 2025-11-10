#!/bin/bash

# Test all the new C keyword implementations

echo "=== Testing New C Keywords ==="
echo ""

tests=(
    "41_goto_labels"
    "42_sizeof"
    "44_increment_decrement"
    "45_compound_assignment"
    "46_enum"
    "47_struct"
    "48_typedef"
    "49_misc"
    "50_struct_enum_combined"
    "51_struct_enum_simple"
    "52_rpg_game"
    "53_include_test"
    "54_simple_include"
)

passed=0
failed=0

for test in "${tests[@]}"; do
    echo "Testing $test..."
    ./compiler/algo-compiler examples/algo/${test}.algo -o examples/algo/${test}.asm > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        ./assembler/a1m-asm examples/algo/${test}.asm a.out > /dev/null 2>&1
        if [ $? -eq 0 ]; then
            ./emulator/a1m-emu a.out > /tmp/${test}_output.txt 2>&1
            if [ $? -eq 0 ]; then
                echo "  ✓ PASSED"
                ((passed++))
            else
                echo "  ✗ FAILED (runtime error)"
                ((failed++))
            fi
        else
            echo "  ✗ FAILED (assembly error)"
            ((failed++))
        fi
    else
        echo "  ✗ FAILED (compilation error)"
        ((failed++))
    fi
done

echo ""
echo "=== Results ==="
echo "Passed: $passed / ${#tests[@]}"
echo "Failed: $failed / ${#tests[@]}"

if [ $failed -eq 0 ]; then
    echo "All tests passed! ✓"
    exit 0
else
    echo "Some tests failed."
    exit 1
fi
