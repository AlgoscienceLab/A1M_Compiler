#!/bin/bash

# Global Installation Script for A1M CPU Toolchain
# This script builds and installs the Algo compiler, assembler, and emulator globally
# Supports: Linux, macOS, Windows (MSYS2/MinGW64)

set -e  # Exit on error

# Default behavior: install user-local build. Use --global to install system-wide.
GLOBAL_INSTALL=false
UPDATE_SOURCE=false
VERIFY=false
PREFIX_OVERRIDE=""

usage() {
    echo "Usage: $0 [--global] [--update] [--prefix <path>]"
    echo "  --global      Install to system-wide location (requires admin/root)"
    echo "  --update      Perform git pull to update repository before build"
    echo "  --prefix PATH Use PATH as the installation prefix"
    exit 1
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --global) GLOBAL_INSTALL=true; shift ;;
        --update) UPDATE_SOURCE=true; shift ;;
        --prefix) shift; PREFIX_OVERRIDE="$1"; shift ;;
        --verify) VERIFY=true; shift ;;
        -h|--help) usage ;;
        *) usage ;;
    esac
done

# Detect platform
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "mingw"* ]]; then
    PLATFORM="Windows"
    MAKE_CMD="mingw32-make"
    if [[ -n "$PREFIX_OVERRIDE" ]]; then
        INSTALL_PREFIX="$PREFIX_OVERRIDE"
    elif [[ "$GLOBAL_INSTALL" == true ]]; then
        # System-wide location - prefer MSYS2 MinGW-w64 bin if present
        if [[ -d "/mingw64" ]]; then
            INSTALL_PREFIX="/mingw64"
        elif [[ -d "/usr/local" ]]; then
            INSTALL_PREFIX="/usr/local"
        else
            # Fallback to Program Files
            INSTALL_PREFIX="/c/Program Files/A1M_Compiler"
        fi
    else
        INSTALL_PREFIX="$HOME/.local"
    fi
    INSTALL_DIR="$INSTALL_PREFIX/bin"
    REQUIRES_SUDO=false
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
    MAKE_CMD="make"
    if [[ -n "$PREFIX_OVERRIDE" ]]; then
        INSTALL_PREFIX="$PREFIX_OVERRIDE"
    elif [[ "$GLOBAL_INSTALL" == true ]]; then
        INSTALL_PREFIX="/usr/local"
    else
        INSTALL_PREFIX="$HOME/.local"
    fi
    INSTALL_DIR="$INSTALL_PREFIX/bin"
    REQUIRES_SUDO=true
else
    PLATFORM="Linux"
    MAKE_CMD="make"
    if [[ -n "$PREFIX_OVERRIDE" ]]; then
        INSTALL_PREFIX="$PREFIX_OVERRIDE"
    elif [[ "$GLOBAL_INSTALL" == true ]]; then
        INSTALL_PREFIX="/usr/local"
    else
        INSTALL_PREFIX="$HOME/.local"
    fi
    INSTALL_DIR="$INSTALL_PREFIX/bin"
    REQUIRES_SUDO=true
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

# Determine the script directory early so we can use it for update or other operations
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# If user requested to update the repo, run git pull first
if [ "$UPDATE_SOURCE" = true ]; then
    echo "Updating repository (git pull)..."
    cd "$SCRIPT_DIR"
    if git rev-parse --git-dir > /dev/null 2>&1; then
        git pull --rebase
    else
        echo "Not a git repository, skipping update"
    fi
fi

# If a system-wide install was requested, require sudo on non-Windows platforms
if [[ "$GLOBAL_INSTALL" == true && "$PLATFORM" != "Windows" ]]; then
    REQUIRES_SUDO=true
else
    REQUIRES_SUDO=false
fi

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

echo -e "${COLOR_BLUE}Installation directory: ${COLOR_RESET}${INSTALL_DIR}"
echo -e "${COLOR_BLUE}Source directory: ${COLOR_RESET}${SCRIPT_DIR}"
echo

if [[ "$PLATFORM" == "Windows" && "$GLOBAL_INSTALL" == true ]]; then
    # When doing system-wide install on Windows we require admin; check using PowerShell
    ADMIN_OK=true
    if ! powershell.exe -Command "[bool](([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator))" | grep -q True; then
        ADMIN_OK=false
    fi
    if [[ "$ADMIN_OK" == false ]]; then
        echo "Error: Global install on Windows requires running this script in an elevated (Administrator) shell. Re-run PowerShell as Administrator and try again." >&2
        echo "Falling back to user-local installation: $HOME/.local" >&2
        INSTALL_PREFIX="$HOME/.local"
        INSTALL_DIR="$INSTALL_PREFIX/bin"
    fi
fi

# Ensure installation directory exists
mkdir -p "${INSTALL_DIR}"

# Select a temporary directory with free space to avoid /tmp overflow errors
choose_tmpdir() {
    local candidates=("/var/tmp" "/tmp" "$SCRIPT_DIR/tmp" "$HOME/tmp" "/home/$ACTUAL_USER/tmp")
    for d in "${candidates[@]}"; do
        if mkdir -p "$d" 2>/dev/null; then
            # Obtain available kilobytes (portable across most Linux distros)
            avail_kb=$(df -k --output=avail "$d" 2>/dev/null | tail -n1 || df -k "$d" | awk 'NR==2{print $4}')
            avail_kb=${avail_kb:-0}
            # Require at least 100MB free for safe compilation
            if [ "$avail_kb" -ge 102400 ]; then
                echo "$d"
                return 0
            fi
        fi
    done
    # If none have 100MB, fallback to /var/tmp (still likely usable)
    if mkdir -p "/var/tmp" 2>/dev/null; then
        echo "/var/tmp"
        return 0
    fi
    # Last resort: use /tmp
    echo "/tmp"
    return 0
}

TMPDIR_SELECTED=$(choose_tmpdir)
export TMPDIR="$TMPDIR_SELECTED"
echo -e "${COLOR_YELLOW}Using temporary build directory: ${TMPDIR}${COLOR_RESET}"

# Build and install each component
echo -e "${COLOR_GREEN}[1/4] Building and Installing Compiler...${COLOR_RESET}"
cd "${SCRIPT_DIR}/compiler"
$MAKE_CMD clean > /dev/null 2>&1 || true
$MAKE_CMD
if [ "$PLATFORM" = "Windows" ]; then
    $MAKE_CMD install PREFIX="$INSTALL_PREFIX"
else
    $MAKE_CMD install PREFIX="$INSTALL_PREFIX"
fi
echo

echo -e "${COLOR_GREEN}[2/4] Building and Installing Assembler...${COLOR_RESET}"
cd "${SCRIPT_DIR}/assembler"
$MAKE_CMD clean > /dev/null 2>&1 || true
$MAKE_CMD
if [ "$PLATFORM" = "Windows" ]; then
    $MAKE_CMD install PREFIX="$INSTALL_PREFIX"
else
    $MAKE_CMD install PREFIX="$INSTALL_PREFIX"
fi
echo

echo -e "${COLOR_GREEN}[3/4] Building and Installing Emulator...${COLOR_RESET}"
cd "${SCRIPT_DIR}/emulator"
$MAKE_CMD clean > /dev/null 2>&1 || true
$MAKE_CMD
if [ "$PLATFORM" = "Windows" ]; then
    $MAKE_CMD install PREFIX="$INSTALL_PREFIX"
else
    $MAKE_CMD install PREFIX="$INSTALL_PREFIX"
fi
echo

echo -e "${COLOR_GREEN}[4/4] Building and Installing Console...${COLOR_RESET}"
cd "${SCRIPT_DIR}/gui-console"
$MAKE_CMD clean > /dev/null 2>&1 || true
$MAKE_CMD
if [ "$PLATFORM" = "Windows" ]; then
    $MAKE_CMD install PREFIX="$INSTALL_PREFIX"
else
    $MAKE_CMD install PREFIX="$INSTALL_PREFIX"
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

if [ "$VERIFY" = true ]; then
    echo -e "${COLOR_BLUE}Running verification example...${COLOR_RESET}"
    examples_dir="${SCRIPT_DIR}/examples/algo"
    if [ -f "${examples_dir}/float_div_test.algo" ]; then
        ${INSTALL_DIR}/algo-compiler $(cygpath -w "${examples_dir}/float_div_test.algo") -o /tmp/verify-float.asm || ${INSTALL_DIR}/algo-compiler "${examples_dir}/float_div_test.algo" -o /tmp/verify-float.asm
        ${INSTALL_DIR}/a1m-asm /tmp/verify-float.asm -o /tmp/verify-float.bin
        ${INSTALL_DIR}/a1m-emu /tmp/verify-float.bin
    else
        echo "Verification example not found: ${examples_dir}/float_div_test.algo"
    fi
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
    
    # If installed system-wide and running as admin, we can add to system PATH
    if [[ "$GLOBAL_INSTALL" == true && "$ADMIN_OK" == true ]]; then
        if command -v cygpath > /dev/null 2>&1; then
            WIN_PREFIX=$(cygpath -w "$INSTALL_PREFIX")
        else
            # Try a basic conversion if cygpath is not available
            WIN_PREFIX="$(echo "$INSTALL_PREFIX" | sed 's|/c|C:|; s|/|\\\\|g')"
        fi
        echo -e "${COLOR_BLUE}Adding $WIN_PREFIX\\bin to system PATH (machine scope)${COLOR_RESET}"
        powershell.exe -NoProfile -Command "[Environment]::SetEnvironmentVariable('Path', ([Environment]::GetEnvironmentVariable('Path','Machine') + ';$WIN_PREFIX\\bin'), 'Machine')"
        echo -e "${COLOR_GREEN}System PATH updated - you may need to log out and back in to apply changes.${COLOR_RESET}"
    fi
fi
    # Install wrapper script algo-run to bin
    if [[ -f "${SCRIPT_DIR}/algo-run.sh" ]]; then
        echo -e "${COLOR_BLUE}Installing algo-run script to ${INSTALL_DIR}${COLOR_RESET}"
        # Copy script; on MSYS use unix path semantics
        cp -f "${SCRIPT_DIR}/algo-run.sh" "${INSTALL_DIR}/algo-run"
        chmod +x "${INSTALL_DIR}/algo-run"

        # Create a simple Windows batch wrapper (for PowerShell/Command Prompt)
        cat > "${INSTALL_DIR}/algo-run.bat" <<-EOL
@echo off
bash "%~dp0/algo-run" %*
EOL
        echo -e "${COLOR_GREEN}Installed algo-run (bash script + .bat wrapper)${COLOR_RESET}"
    fi
echo