#!/bin/bash

# Global Installation Script for A1M CPU Toolchain
# This script builds and installs the Algo compiler, assembler, and emulator globally

set -e  # Exit on error

INSTALL_DIR="/usr/local/bin"
COLOR_GREEN='\033[0;32m'
COLOR_BLUE='\033[0;34m'
COLOR_RED='\033[0;31m'
COLOR_RESET='\033[0m'

echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_BLUE}A1M CPU Toolchain Global Installation${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo

# Check if running with sudo
if [ "$EUID" -ne 0 ]; then
    echo -e "${COLOR_RED}Error: This script must be run with sudo${COLOR_RESET}"
    echo "Please run: sudo ./install.sh"
    exit 1
fi

# Get the actual user (not root when using sudo)
ACTUAL_USER="${SUDO_USER:-$USER}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "${COLOR_BLUE}Installation directory: ${COLOR_RESET}${INSTALL_DIR}"
echo -e "${COLOR_BLUE}Source directory: ${COLOR_RESET}${SCRIPT_DIR}"
echo

# Build and install Algo Compiler
echo -e "${COLOR_GREEN}[1/3] Building Algo Compiler...${COLOR_RESET}"
cd "${SCRIPT_DIR}/compiler"
make clean > /dev/null 2>&1 || true
make
if [ -f "algo-compiler" ]; then
    cp algo-compiler "${INSTALL_DIR}/algo"
    chmod 755 "${INSTALL_DIR}/algo"
    echo -e "${COLOR_GREEN}✓ Installed: algo${COLOR_RESET}"
else
    echo -e "${COLOR_RED}✗ Failed to build Algo compiler${COLOR_RESET}"
    exit 1
fi

# Build and install A1M Assembler
echo -e "${COLOR_GREEN}[2/3] Building A1M Assembler...${COLOR_RESET}"
cd "${SCRIPT_DIR}/assembler"
make clean > /dev/null 2>&1 || true
make
if [ -f "a1m-asm" ]; then
    cp a1m-asm "${INSTALL_DIR}/a1m-asm"
    chmod 755 "${INSTALL_DIR}/a1m-asm"
    echo -e "${COLOR_GREEN}✓ Installed: a1m-asm${COLOR_RESET}"
else
    echo -e "${COLOR_RED}✗ Failed to build A1M assembler${COLOR_RESET}"
    exit 1
fi

# Build and install A1M Emulator
echo -e "${COLOR_GREEN}[3/3] Building A1M Emulator...${COLOR_RESET}"
cd "${SCRIPT_DIR}/emulator"
make clean > /dev/null 2>&1 || true
make
if [ -f "a1m-emu" ]; then
    cp a1m-emu "${INSTALL_DIR}/a1m-emu"
    chmod 755 "${INSTALL_DIR}/a1m-emu"
    echo -e "${COLOR_GREEN}✓ Installed: a1m-emu${COLOR_RESET}"
else
    echo -e "${COLOR_RED}✗ Failed to build A1M emulator${COLOR_RESET}"
    exit 1
fi

echo
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_GREEN}Installation Complete!${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo
echo "The following commands are now available globally:"
echo -e "  ${COLOR_GREEN}algo${COLOR_RESET}      - Algo language compiler"
echo -e "  ${COLOR_GREEN}a1m-asm${COLOR_RESET}   - A1M assembler"
echo -e "  ${COLOR_GREEN}a1m-emu${COLOR_RESET}   - A1M emulator"
echo
echo "Example usage:"
echo -e "  ${COLOR_BLUE}algo myprogram.algo -o myprogram.asm${COLOR_RESET}"
echo -e "  ${COLOR_BLUE}a1m-asm myprogram.asm myprogram.bin${COLOR_RESET}"
echo -e "  ${COLOR_BLUE}a1m-emu myprogram.bin${COLOR_RESET}"
echo
echo "Or use the full pipeline:"
echo -e "  ${COLOR_BLUE}algo myprogram.algo -o myprogram.asm && a1m-asm myprogram.asm myprogram.bin && a1m-emu myprogram.bin${COLOR_RESET}"
echo
