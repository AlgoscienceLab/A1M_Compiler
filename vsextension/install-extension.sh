#!/bin/bash

# VS Code Extension Installation Script
# Builds and installs the Algo Language extension for VS Code
# Supports: Linux, macOS, Windows (MSYS2/MinGW64)

set -e

# Detect platform
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "mingw"* ]]; then
    PLATFORM="Windows"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
else
    PLATFORM="Linux"
fi

COLOR_GREEN='\033[0;32m'
COLOR_BLUE='\033[0;34m'
COLOR_RED='\033[0;31m'
COLOR_YELLOW='\033[1;33m'
COLOR_RESET='\033[0m'

echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_BLUE}Algo Language VS Code Extension Setup${COLOR_RESET}"
echo -e "${COLOR_BLUE}Platform: ${PLATFORM}${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo

# Check if Node.js is installed
if ! command -v node &> /dev/null; then
    echo -e "${COLOR_RED}Error: Node.js is not installed${COLOR_RESET}"
    echo
    echo "Please install Node.js:"
    if [ "$PLATFORM" = "Windows" ]; then
        echo "  - Download from: https://nodejs.org/"
        echo "  - Or in MSYS2: pacman -S mingw-w64-x86_64-nodejs"
    elif [ "$PLATFORM" = "macOS" ]; then
        echo "  - Download from: https://nodejs.org/"
        echo "  - Or with Homebrew: brew install node"
    else
        echo "  - Ubuntu/Debian: sudo apt-get install nodejs npm"
        echo "  - Fedora: sudo dnf install nodejs npm"
        echo "  - Arch: sudo pacman -S nodejs npm"
    fi
    exit 1
fi

# Check if npm is installed
if ! command -v npm &> /dev/null; then
    echo -e "${COLOR_RED}Error: npm is not installed${COLOR_RESET}"
    echo "npm is usually installed with Node.js. Please reinstall Node.js."
    exit 1
fi

echo -e "${COLOR_GREEN}✓ Node.js found: $(node --version)${COLOR_RESET}"
echo -e "${COLOR_GREEN}✓ npm found: $(npm --version)${COLOR_RESET}"
echo

# Navigate to extension directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${SCRIPT_DIR}"

# Install dependencies
echo -e "${COLOR_BLUE}[1/3] Installing dependencies...${COLOR_RESET}"
npm install
echo

# Compile TypeScript
echo -e "${COLOR_BLUE}[2/3] Compiling TypeScript...${COLOR_RESET}"
npm run compile
echo

# Check if vsce is installed
if ! command -v vsce &> /dev/null && ! [ -f "node_modules/.bin/vsce" ]; then
    echo -e "${COLOR_YELLOW}vsce not found. Installing @vscode/vsce locally...${COLOR_RESET}"
    npm install --save-dev @vscode/vsce
    echo
fi

# Use local vsce if available, otherwise use global
if [ -f "node_modules/.bin/vsce" ]; then
    VSCE_CMD="node_modules/.bin/vsce"
else
    VSCE_CMD="vsce"
fi

# Package extension
echo -e "${COLOR_BLUE}[3/3] Packaging extension...${COLOR_RESET}"
$VSCE_CMD package
echo

# Find the generated .vsix file
VSIX_FILE=$(ls -t *.vsix 2>/dev/null | head -1)

if [ -z "$VSIX_FILE" ]; then
    echo -e "${COLOR_RED}Error: Failed to create .vsix package${COLOR_RESET}"
    exit 1
fi

echo
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_GREEN}Extension built successfully!${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo
echo -e "Package: ${COLOR_GREEN}${VSIX_FILE}${COLOR_RESET}"
echo
echo "To install in VS Code:"
echo
if [ "$PLATFORM" = "Windows" ]; then
    echo "  Method 1: Using VS Code GUI"
    echo "    1. Open VS Code"
    echo "    2. Press Ctrl+Shift+P"
    echo "    3. Type 'Extensions: Install from VSIX'"
    echo "    4. Select: vsextension/${VSIX_FILE}"
    echo
    echo "  Method 2: Using command line"
    echo "    code --install-extension vsextension/${VSIX_FILE}"
elif [ "$PLATFORM" = "macOS" ]; then
    echo "  Method 1: Using VS Code GUI"
    echo "    1. Open VS Code"
    echo "    2. Press Cmd+Shift+P"
    echo "    3. Type 'Extensions: Install from VSIX'"
    echo "    4. Select: vsextension/${VSIX_FILE}"
    echo
    echo "  Method 2: Using command line"
    echo "    code --install-extension vsextension/${VSIX_FILE}"
else
    echo "  Method 1: Using VS Code GUI"
    echo "    1. Open VS Code"
    echo "    2. Press Ctrl+Shift+P"
    echo "    3. Type 'Extensions: Install from VSIX'"
    echo "    4. Select: vsextension/${VSIX_FILE}"
    echo
    echo "  Method 2: Using command line"
    echo "    code --install-extension vsextension/${VSIX_FILE}"
fi
echo
echo -e "${COLOR_YELLOW}Note: You may need to reload VS Code after installation${COLOR_RESET}"
echo

# Offer to install automatically if code command is available
if command -v code &> /dev/null; then
    echo -e "${COLOR_BLUE}Would you like to install the extension now? (y/n)${COLOR_RESET}"
    read -r response
    if [[ "$response" =~ ^[Yy]$ ]]; then
        echo -e "${COLOR_BLUE}Installing extension...${COLOR_RESET}"
        code --install-extension "${VSIX_FILE}"
        echo
        echo -e "${COLOR_GREEN}✓ Extension installed!${COLOR_RESET}"
        echo -e "${COLOR_YELLOW}Please reload VS Code to activate the extension${COLOR_RESET}"
    fi
fi

echo
echo -e "${COLOR_GREEN}Done!${COLOR_RESET}"
echo
