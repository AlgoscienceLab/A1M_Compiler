#!/bin/bash

# Global Installation Script for A1M CPU Toolchain
# This script builds and installs the Algo compiler, assembler, and emulator globally
# Supports: Linux, macOS, Windows (MSYS2/MinGW64)

set -e  # Exit on error

# Detect platform
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "mingw"* ]]; then
    PLATFORM="Windows"
    # Use user's home bin directory which doesn't need admin rights
    # Create it if it doesn't exist and add to PATH if needed
    INSTALL_DIR="$HOME/.local/bin"
    REQUIRES_SUDO=false
    MAKE_CMD="mingw32-make"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
    INSTALL_DIR="/usr/local/bin"
    REQUIRES_SUDO=true
    MAKE_CMD="make"
else
    PLATFORM="Linux"
    INSTALL_DIR="/usr/local/bin"
    REQUIRES_SUDO=true
    MAKE_CMD="make"
fi

COLOR_GREEN='\033[0;32m'
COLOR_BLUE='\033[0;34m'
COLOR_RED='\033[0;31m'
COLOR_YELLOW='\033[1;33m'
COLOR_RESET='\033[0m'

echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_BLUE}A1M CPU Toolchain Global Installation${COLOR_RESET}"
echo -e "${COLOR_BLUE}Platform: ${PLATFORM}${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo

# Check if running with sudo (only on Linux/macOS)
if [ "$REQUIRES_SUDO" = true ]; then
    if [ "$EUID" -ne 0 ]; then
        echo -e "${COLOR_RED}Error: This script must be run with sudo on ${PLATFORM}${COLOR_RESET}"
        echo "Please run: sudo ./install.sh"
        exit 1
    fi
fi

# Get the actual user (not root when using sudo)
ACTUAL_USER="${SUDO_USER:-$USER}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "${COLOR_BLUE}Installation directory: ${COLOR_RESET}${INSTALL_DIR}"
echo -e "${COLOR_BLUE}Source directory: ${COLOR_RESET}${SCRIPT_DIR}"
echo

# Ensure installation directory exists
mkdir -p "${INSTALL_DIR}"

# Build and install each component
echo -e "${COLOR_GREEN}[1/4] Building and Installing Compiler...${COLOR_RESET}"
cd "${SCRIPT_DIR}/compiler"
$MAKE_CMD clean > /dev/null 2>&1 || true
$MAKE_CMD
if [ "$PLATFORM" = "Windows" ]; then
    $MAKE_CMD install PREFIX="$HOME/.local"
else
    $MAKE_CMD install PREFIX=/usr/local
fi
echo

echo -e "${COLOR_GREEN}[2/4] Building and Installing Assembler...${COLOR_RESET}"
cd "${SCRIPT_DIR}/assembler"
$MAKE_CMD clean > /dev/null 2>&1 || true
$MAKE_CMD
if [ "$PLATFORM" = "Windows" ]; then
    $MAKE_CMD install PREFIX="$HOME/.local"
else
    $MAKE_CMD install PREFIX=/usr/local
fi
echo

echo -e "${COLOR_GREEN}[3/4] Building and Installing Emulator...${COLOR_RESET}"
cd "${SCRIPT_DIR}/emulator"
$MAKE_CMD clean > /dev/null 2>&1 || true
$MAKE_CMD
if [ "$PLATFORM" = "Windows" ]; then
    $MAKE_CMD install PREFIX="$HOME/.local"
else
    $MAKE_CMD install PREFIX=/usr/local
fi
echo

echo -e "${COLOR_GREEN}[4/4] Building and Installing Console...${COLOR_RESET}"
cd "${SCRIPT_DIR}/gui-console"
$MAKE_CMD clean > /dev/null 2>&1 || true
$MAKE_CMD
if [ "$PLATFORM" = "Windows" ]; then
    $MAKE_CMD install PREFIX="$HOME/.local"
else
    $MAKE_CMD install PREFIX=/usr/local
fi
echo

cd "${SCRIPT_DIR}"

echo
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_GREEN}Installation Complete!${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo
echo "The following commands are now available globally:"
if [ "$PLATFORM" = "Windows" ]; then
    echo -e "  ${COLOR_GREEN}algo-compiler.exe${COLOR_RESET}  - Algo language compiler"
    echo -e "  ${COLOR_GREEN}a1m-asm.exe${COLOR_RESET}        - A1M assembler"
    echo -e "  ${COLOR_GREEN}a1m-emu.exe${COLOR_RESET}        - A1M emulator"
    echo -e "  ${COLOR_GREEN}a1m-console.exe${COLOR_RESET}    - A1M interactive console"
else
    echo -e "  ${COLOR_GREEN}algo-compiler${COLOR_RESET}  - Algo language compiler"
    echo -e "  ${COLOR_GREEN}a1m-asm${COLOR_RESET}        - A1M assembler"
    echo -e "  ${COLOR_GREEN}a1m-emu${COLOR_RESET}        - A1M emulator"
    echo -e "  ${COLOR_GREEN}a1m-console${COLOR_RESET}    - A1M interactive console"
fi
echo
echo "Example usage:"
if [ "$PLATFORM" = "Windows" ]; then
    echo -e "  ${COLOR_BLUE}algo-compiler.exe myprogram.algo -o myprogram.asm${COLOR_RESET}"
    echo -e "  ${COLOR_BLUE}a1m-asm.exe myprogram.asm -o myprogram.bin${COLOR_RESET}"
    echo -e "  ${COLOR_BLUE}a1m-emu.exe myprogram.bin${COLOR_RESET}"
else
    echo -e "  ${COLOR_BLUE}algo-compiler myprogram.algo -o myprogram.asm${COLOR_RESET}"
    echo -e "  ${COLOR_BLUE}a1m-asm myprogram.asm -o myprogram.bin${COLOR_RESET}"
    echo -e "  ${COLOR_BLUE}a1m-emu myprogram.bin${COLOR_RESET}"
fi
echo
if [ "$PLATFORM" = "Windows" ]; then
    echo -e "${COLOR_YELLOW}Note: Installed to $INSTALL_DIR${COLOR_RESET}"
    # Check if directory is in PATH
    if [[ ":$PATH:" != *":$INSTALL_DIR:"* ]]; then
        echo -e "${COLOR_YELLOW}Warning: $INSTALL_DIR is not in your PATH${COLOR_RESET}"
        echo -e "${COLOR_YELLOW}Add the following to your ~/.bashrc or ~/.bash_profile:${COLOR_RESET}"
        echo -e "${COLOR_BLUE}export PATH=\"\$HOME/.local/bin:\$PATH\"${COLOR_RESET}"
        echo
        echo -e "${COLOR_YELLOW}Then reload your shell with: source ~/.bashrc${COLOR_RESET}"
    else
        echo -e "${COLOR_GREEN}$INSTALL_DIR is already in your PATH${COLOR_RESET}"
    fi
fi
echo