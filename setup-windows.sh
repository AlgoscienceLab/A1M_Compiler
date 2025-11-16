#!/bin/bash
# Complete Build and Install Script for Windows (MSYS2/MinGW64)
# This script installs make if needed, builds all components, and installs them

set -e

COLOR_GREEN='\033[0;32m'
COLOR_BLUE='\033[0;34m'
COLOR_RED='\033[0;31m'
COLOR_YELLOW='\033[1;33m'
COLOR_RESET='\033[0m'

echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_BLUE}A1M Compiler - Complete Setup (Windows)${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo ""

# Check if we're in a Unix-like environment (MSYS2, Linux, macOS)
# For Windows, just verify we have basic tools
if command -v gcc &> /dev/null || command -v pacman &> /dev/null; then
    echo -e "${COLOR_GREEN}✓ Running in compatible environment${COLOR_RESET}"
else
    echo -e "${COLOR_YELLOW}Warning: Cannot verify environment, continuing anyway...${COLOR_RESET}"
fi

# Check and install make if needed
if ! command -v make &> /dev/null; then
    echo -e "${COLOR_YELLOW}Make not found. Installing...${COLOR_RESET}"
    echo ""
    pacman -S --noconfirm make mingw-w64-x86_64-make
    echo ""
    echo -e "${COLOR_GREEN}✓ Make installed${COLOR_RESET}"
else
    echo -e "${COLOR_GREEN}✓ Make already installed${COLOR_RESET}"
fi

# Check GCC
if ! command -v gcc &> /dev/null; then
    echo -e "${COLOR_YELLOW}GCC not found. Installing...${COLOR_RESET}"
    echo ""
    pacman -S --noconfirm mingw-w64-x86_64-gcc
    echo ""
    echo -e "${COLOR_GREEN}✓ GCC installed${COLOR_RESET}"
else
    echo -e "${COLOR_GREEN}✓ GCC already installed: $(gcc --version | head -1)${COLOR_RESET}"
fi

echo ""
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_BLUE}Building All Components${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo ""

# Build Compiler
echo -e "${COLOR_CYAN}[1/4] Building Compiler...${COLOR_RESET}"
cd compiler
make clean > /dev/null 2>&1 || true
make
if [ ! -f "algo-compiler.exe" ]; then
    echo -e "${COLOR_RED}Error: Failed to build compiler${COLOR_RESET}"
    exit 1
fi
echo -e "${COLOR_GREEN}✓ Built: algo-compiler.exe${COLOR_RESET}"
cd ..
echo ""

# Build Assembler
echo -e "${COLOR_CYAN}[2/4] Building Assembler...${COLOR_RESET}"
cd assembler
make clean > /dev/null 2>&1 || true
make
if [ ! -f "a1m-asm.exe" ]; then
    echo -e "${COLOR_RED}Error: Failed to build assembler${COLOR_RESET}"
    exit 1
fi
echo -e "${COLOR_GREEN}✓ Built: a1m-asm.exe${COLOR_RESET}"
cd ..
echo ""

# Build Emulator
echo -e "${COLOR_CYAN}[3/4] Building Emulator...${COLOR_RESET}"
cd emulator
make clean > /dev/null 2>&1 || true
make
if [ ! -f "a1m-emu.exe" ]; then
    echo -e "${COLOR_RED}Error: Failed to build emulator${COLOR_RESET}"
    exit 1
fi
echo -e "${COLOR_GREEN}✓ Built: a1m-emu.exe${COLOR_RESET}"
cd ..
echo ""

# Build Console
echo -e "${COLOR_CYAN}[4/4] Building Console...${COLOR_RESET}"
cd gui-console
make clean > /dev/null 2>&1 || true
make
if [ ! -f "a1m-console.exe" ]; then
    echo -e "${COLOR_RED}Error: Failed to build console${COLOR_RESET}"
    exit 1
fi
echo -e "${COLOR_GREEN}✓ Built: a1m-console.exe${COLOR_RESET}"
cd ..
echo ""

echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_GREEN}Build Complete!${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo ""

# Ask about installation
echo -e "${COLOR_YELLOW}Would you like to install the toolchain globally? (y/n)${COLOR_RESET}"
read -r install_response

if [[ "$install_response" =~ ^[Yy]$ ]]; then
    echo ""
    echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
    echo -e "${COLOR_BLUE}Installing to /usr/local/bin${COLOR_RESET}"
    echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
    echo ""
    
    # Install each component
    echo -e "${COLOR_CYAN}Installing Compiler...${COLOR_RESET}"
    cd compiler && make install PREFIX=/usr/local && cd ..
    
    echo -e "${COLOR_CYAN}Installing Assembler...${COLOR_RESET}"
    cd assembler && make install PREFIX=/usr/local && cd ..
    
    echo -e "${COLOR_CYAN}Installing Emulator...${COLOR_RESET}"
    cd emulator && make install PREFIX=/usr/local && cd ..
    
    echo -e "${COLOR_CYAN}Installing Console...${COLOR_RESET}"
    cd gui-console && make install PREFIX=/usr/local && cd ..
    
    echo ""
    echo -e "${COLOR_GREEN}✓ Installation complete!${COLOR_RESET}"
    echo ""
    echo -e "${COLOR_BLUE}Tools installed to: /usr/local/bin${COLOR_RESET}"
    echo "  - algo-compiler.exe"
    echo "  - a1m-asm.exe"
    echo "  - a1m-emu.exe"
    echo "  - a1m-console.exe"
    echo ""
    echo -e "${COLOR_YELLOW}You can now use these commands from anywhere in MSYS2!${COLOR_RESET}"
else
    echo ""
    echo -e "${COLOR_BLUE}Skipping global installation.${COLOR_RESET}"
    echo ""
    echo "Built executables are in:"
    echo "  - compiler/algo-compiler.exe"
    echo "  - assembler/a1m-asm.exe"
    echo "  - emulator/a1m-emu.exe"
    echo "  - gui-console/a1m-console.exe"
fi

echo ""
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_BLUE}Testing Installation${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo ""

# Test with hello world
echo -e "${COLOR_CYAN}Testing with hello_world.algo...${COLOR_RESET}"

if [[ "$install_response" =~ ^[Yy]$ ]]; then
    # Use globally installed tools
    algo-compiler.exe examples/algo/01_hello_world.algo -o test.asm
    a1m-asm.exe test.asm -o test.bin
    echo ""
    echo -e "${COLOR_CYAN}Program output:${COLOR_RESET}"
    echo "---"
    a1m-emu.exe test.bin
    echo "---"
else
    # Use local tools
    ./compiler/algo-compiler.exe examples/algo/01_hello_world.algo -o test.asm
    ./assembler/a1m-asm.exe test.asm -o test.bin
    echo ""
    echo -e "${COLOR_CYAN}Program output:${COLOR_RESET}"
    echo "---"
    ./emulator/a1m-emu.exe test.bin
    echo "---"
fi

# Clean up test files
rm -f test.asm test.bin

echo ""
echo -e "${COLOR_GREEN}✓ Test successful!${COLOR_RESET}"

echo ""
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_BLUE}VS Code Extension${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo ""

# Check if Node.js is installed
if command -v node &> /dev/null; then
    echo -e "${COLOR_GREEN}✓ Node.js found: $(node --version)${COLOR_RESET}"
    echo ""
    echo -e "${COLOR_YELLOW}Would you like to build and install the VS Code extension? (y/n)${COLOR_RESET}"
    read -r vscode_response
    
    if [[ "$vscode_response" =~ ^[Yy]$ ]]; then
        cd vsextension
        
        echo ""
        echo -e "${COLOR_CYAN}Installing npm dependencies...${COLOR_RESET}"
        npm install
        
        echo ""
        echo -e "${COLOR_CYAN}Compiling TypeScript...${COLOR_RESET}"
        npm run compile
        
        echo ""
        echo -e "${COLOR_CYAN}Packaging extension...${COLOR_RESET}"
        
        # Install vsce if not present
        if ! command -v vsce &> /dev/null; then
            echo -e "${COLOR_YELLOW}Installing @vscode/vsce...${COLOR_RESET}"
            npm install -g @vscode/vsce
        fi
        
        vsce package
        
        VSIX_FILE=$(ls -t *.vsix 2>/dev/null | head -1)
        
        if [ -n "$VSIX_FILE" ]; then
            echo ""
            echo -e "${COLOR_GREEN}✓ Extension packaged: ${VSIX_FILE}${COLOR_RESET}"
            echo ""
            
            # Check if code command is available
            if command -v code &> /dev/null; then
                echo -e "${COLOR_YELLOW}Would you like to install it in VS Code now? (y/n)${COLOR_RESET}"
                read -r install_vscode
                
                if [[ "$install_vscode" =~ ^[Yy]$ ]]; then
                    code --install-extension "$VSIX_FILE"
                    echo ""
                    echo -e "${COLOR_GREEN}✓ Extension installed in VS Code!${COLOR_RESET}"
                    echo -e "${COLOR_YELLOW}Please reload VS Code to activate the extension${COLOR_RESET}"
                else
                    echo ""
                    echo "To install manually:"
                    echo "  1. Open VS Code"
                    echo "  2. Press Ctrl+Shift+P"
                    echo "  3. Type 'Extensions: Install from VSIX'"
                    echo "  4. Select: vsextension/${VSIX_FILE}"
                fi
            else
                echo "To install in VS Code:"
                echo "  1. Open VS Code"
                echo "  2. Press Ctrl+Shift+P"
                echo "  3. Type 'Extensions: Install from VSIX'"
                echo "  4. Select: vsextension/${VSIX_FILE}"
            fi
        else
            echo -e "${COLOR_RED}Error: Failed to create .vsix package${COLOR_RESET}"
        fi
        
        cd ..
    fi
else
    echo -e "${COLOR_YELLOW}Node.js not found. Skipping VS Code extension.${COLOR_RESET}"
    echo ""
    echo "To install Node.js:"
    echo "  pacman -S mingw-w64-x86_64-nodejs"
    echo ""
    echo "Then run: cd vsextension && bash install-extension.sh"
fi

echo ""
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo -e "${COLOR_GREEN}Setup Complete!${COLOR_RESET}"
echo -e "${COLOR_BLUE}========================================${COLOR_RESET}"
echo ""
echo -e "${COLOR_CYAN}Next steps:${COLOR_RESET}"
echo "  1. Try more examples: ls examples/algo/"
echo "  2. Read documentation: cat QUICK_REFERENCE.md"
echo "  3. Open in VS Code: code ."
echo ""
echo -e "${COLOR_GREEN}Happy coding with A1M!${COLOR_RESET}"
echo ""
