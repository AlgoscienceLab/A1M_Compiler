#!/bin/bash
# A1M Console Demo - Shows off all examples with colorful interface

clear

echo -e "\033[1;36m"
cat << "EOF"
╔══════════════════════════════════════════════════════════════════╗
║                  A1M CPU CONSOLE DEMONSTRATION                   ║
║              Colorful Interactive Development Environment        ║
╚══════════════════════════════════════════════════════════════════╝
EOF
echo -e "\033[0m"

echo ""
echo -e "\033[1;33mThis demo will showcase the A1M Console with various examples\033[0m"
echo ""
echo -e "\033[1;32mPress Enter to continue...\033[0m"
read

# Demo 1: Addition
echo -e "\n\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo -e "\033[1;33m DEMO 1: Addition (15 + 27 = 42)\033[0m"
echo -e "\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo ""
echo -e "\033[0;37mRunning: \033[1;32m./console.sh examples/asm/addition.asm\033[0m"
echo ""
sleep 1
./console.sh examples/asm/addition.asm
echo -e "\n\033[1;32mPress Enter to continue...\033[0m"
read

# Demo 2: Multiplication
echo -e "\n\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo -e "\033[1;33m DEMO 2: Multiplication (6 × 7 = 42)\033[0m"
echo -e "\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo ""
echo -e "\033[0;37mRunning: \033[1;32m./console.sh examples/asm/multiply.asm\033[0m"
echo ""
sleep 1
./console.sh examples/asm/multiply.asm
echo -e "\n\033[1;32mPress Enter to continue...\033[0m"
read

# Demo 3: Sum Loop
echo -e "\n\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo -e "\033[1;33m DEMO 3: Sum of 1 to 10 (1+2+3+...+10 = 55)\033[0m"
echo -e "\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo ""
echo -e "\033[0;37mRunning: \033[1;32m./console.sh examples/asm/sum_loop.asm\033[0m"
echo ""
sleep 1
./console.sh examples/asm/sum_loop.asm
echo -e "\n\033[1;32mPress Enter to continue...\033[0m"
read

# Demo 4: Power
echo -e "\n\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo -e "\033[1;33m DEMO 4: Power Calculation (2^8 = 256)\033[0m"
echo -e "\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo ""
echo -e "\033[0;37mRunning: \033[1;32m./console.sh examples/asm/power.asm\033[0m"
echo ""
sleep 1
./console.sh examples/asm/power.asm
echo -e "\n\033[1;32mPress Enter to continue...\033[0m"
read

# Demo 5: Fibonacci
echo -e "\n\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo -e "\033[1;33m DEMO 5: Fibonacci Sequence\033[0m"
echo -e "\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
echo ""
echo -e "\033[0;37mRunning: \033[1;32m./console.sh examples/asm/fibonacci.asm\033[0m"
echo ""
sleep 1
./console.sh examples/asm/fibonacci.asm
echo ""

# Summary
clear
echo -e "\033[1;36m"
cat << "EOF"
╔══════════════════════════════════════════════════════════════════╗
║                    DEMONSTRATION COMPLETE!                       ║
╚══════════════════════════════════════════════════════════════════╝
EOF
echo -e "\033[0m"

echo ""
echo -e "\033[1;32mAll examples demonstrated successfully!\033[0m"
echo ""
echo -e "\033[1;33mA1M Console Features:\033[0m"
echo -e "  ✓ Colorful, interactive interface"
echo -e "  ✓ Progress bars and animations"
echo -e "  ✓ Support for .algo, .asm, and .bin files"
echo -e "  ✓ Integrated compilation pipeline"
echo -e "  ✓ Real-time execution feedback"
echo -e "  ✓ 100% custom C implementation"
echo ""
echo -e "\033[1;36mExamples Available:\033[0m"
echo -e "  • examples/asm/addition.asm    - Basic addition"
echo -e "  • examples/asm/multiply.asm    - Multiplication"
echo -e "  • examples/asm/sum_loop.asm    - Sum with loops"
echo -e "  • examples/asm/power.asm       - Power calculation"
echo -e "  • examples/asm/fibonacci.asm   - Fibonacci sequence"
echo -e "  • examples/algo/*.algo         - Algo language examples"
echo ""
echo -e "\033[1;33mTry it yourself:\033[0m"
echo -e "  \033[1;32m./console.sh\033[0m                        - Interactive mode"
echo -e "  \033[1;32m./console.sh examples/asm/<file>\033[0m    - Quick run mode"
echo ""
