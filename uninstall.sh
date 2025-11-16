#!/bin/bash

# Uninstall Script for A1M CPU Toolchain
# Removes globally installed binaries
# Supports: Linux, macOS, Windows (MSYS2/MinGW64)

set -e

# Detect platform
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "mingw"* ]]; then
    PLATFORM="Windows"
    INSTALL_DIR="/usr/local/bin"
    REQUIRES_SUDO=false
    EXE_EXT=".exe"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
    INSTALL_DIR="/usr/local/bin"
    REQUIRES_SUDO=true
    EXE_EXT=""
else
    PLATFORM="Linux"
    INSTALL_DIR="/usr/local/bin"
    REQUIRES_SUDO=true
    EXE_EXT=""
fi

COLOR_GREEN='\033[0;32m'
COLOR_BLUE='\033[0;34m'
COLOR_RED='\033[0;31m'
COLOR_RESET='\033[0m'

echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_BLUE}A1M CPU Toolchain Uninstallation${COLOR_RESET}"
echo -e "${COLOR_BLUE}Platform: ${PLATFORM}${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo

# Check if running with sudo (only on Linux/macOS)
if [ "$REQUIRES_SUDO" = true ]; then
    if [ "$EUID" -ne 0 ]; then
        echo -e "${COLOR_RED}Error: This script must be run with sudo on ${PLATFORM}${COLOR_RESET}"
        echo "Please run: sudo ./uninstall.sh"
        exit 1
    fi
fi

# Remove binaries
for binary in algo-compiler a1m-asm a1m-emu a1m-console; do
    binary_with_ext="${binary}${EXE_EXT}"
    if [ -f "${INSTALL_DIR}/${binary_with_ext}" ]; then
        rm -f "${INSTALL_DIR}/${binary_with_ext}"
        echo -e "${COLOR_GREEN}✓ Removed: ${binary_with_ext}${COLOR_RESET}"
    else
        echo -e "${COLOR_BLUE}  ${binary_with_ext} not found (already removed)${COLOR_RESET}"
    fi
done

echo
echo -e "${COLOR_GREEN}Uninstallation complete!${COLOR_RESET}"
echo
