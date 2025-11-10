#!/bin/bash

# Uninstall Script for A1M CPU Toolchain
# Removes globally installed binaries

set -e

INSTALL_DIR="/usr/local/bin"
COLOR_GREEN='\033[0;32m'
COLOR_BLUE='\033[0;34m'
COLOR_RED='\033[0;31m'
COLOR_RESET='\033[0m'

echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_BLUE}A1M CPU Toolchain Uninstallation${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo

# Check if running with sudo
if [ "$EUID" -ne 0 ]; then
    echo -e "${COLOR_RED}Error: This script must be run with sudo${COLOR_RESET}"
    echo "Please run: sudo ./uninstall.sh"
    exit 1
fi

# Remove binaries
for binary in algo a1m-asm a1m-emu algo-run; do
    if [ -f "${INSTALL_DIR}/${binary}" ]; then
        rm -f "${INSTALL_DIR}/${binary}"
        echo -e "${COLOR_GREEN}✓ Removed: ${binary}${COLOR_RESET}"
    else
        echo -e "${COLOR_BLUE}  ${binary} not found (already removed)${COLOR_RESET}"
    fi
done

echo
echo -e "${COLOR_GREEN}Uninstallation complete!${COLOR_RESET}"
echo
