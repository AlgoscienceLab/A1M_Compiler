# Installation Guide - All Platforms

Complete installation instructions for the A1M Compiler toolchain on Linux, macOS, and Windows.

---

## Table of Contents

1. [Quick Installation](#quick-installation)
2. [Manual Installation](#manual-installation)
3. [VS Code Extension](#vs-code-extension)
4. [Verification](#verification)
5. [Uninstallation](#uninstallation)

---

## Quick Installation

### Linux / macOS

```bash
# Build and install globally (requires sudo)
sudo ./install.sh

# Verify installation
algo-compiler --version
a1m-asm --version
a1m-emu --version
```

### Windows (MSYS2 MinGW64)

```bash
# Build and install (no sudo needed in MSYS2)
./install.sh

# Verify installation
algo-compiler.exe --version
a1m-asm.exe --version
a1m-emu.exe --version
```

**Installation Location**: `/usr/local/bin` (accessible from MSYS2 terminal)

---

## Manual Installation

### Step 1: Build Components

#### All Platforms
```bash
# Build all components
cd compiler && make && cd ..
cd assembler && make && cd ..
cd emulator && make && cd ..
cd gui-console && make && cd ..
```

### Step 2: Install Components

#### Linux / macOS
```bash
# Install each component (requires sudo)
cd compiler && sudo make install && cd ..
cd assembler && sudo make install && cd ..
cd emulator && sudo make install && cd ..
cd gui-console && sudo make install && cd ..
```

#### Windows (MSYS2 MinGW64)
```bash
# Install each component (no sudo needed)
cd compiler && make install && cd ..
cd assembler && make install && cd ..
cd emulator && make install && cd ..
cd gui-console && make install && cd ..
```

### Custom Installation Directory

You can specify a custom installation prefix:

```bash
# Example: Install to ~/.local/bin
cd compiler
make install PREFIX=$HOME/.local
cd ..
cd assembler
make install PREFIX=$HOME/.local
cd ..
# ... repeat for other components

# Add to PATH (add to ~/.bashrc or ~/.zshrc)
export PATH="$HOME/.local/bin:$PATH"
```

---

## VS Code Extension

### Prerequisites

1. **Node.js** must be installed:
   - **Windows**: Download from https://nodejs.org/ or `pacman -S mingw-w64-x86_64-nodejs`
   - **macOS**: Download from https://nodejs.org/ or `brew install node`
   - **Linux**: `sudo apt-get install nodejs npm` (Ubuntu/Debian)

2. **VS Code** must be installed: https://code.visualstudio.com/

### Automatic Installation

#### Linux / macOS
```bash
cd vsextension
chmod +x install-extension.sh
./install-extension.sh
```

#### Windows (MSYS2)
```bash
cd vsextension
bash install-extension.sh
```

#### Windows (PowerShell/CMD)
```batch
cd vsextension
install-extension.bat
```

### Manual Installation

```bash
cd vsextension

# Install dependencies
npm install

# Compile TypeScript
npm run compile

# Package extension
npm install -g @vscode/vsce
vsce package

# Install in VS Code
code --install-extension algo-language-1.3.0.vsix
```

---

## Verification

### Test Toolchain Installation

#### Linux / macOS
```bash
# Check versions
algo-compiler --version
a1m-asm --version
a1m-emu --version
a1m-console --version

# Test with example
algo-compiler examples/algo/01_hello_world.algo -o test.asm
a1m-asm test.asm -o test.bin
a1m-emu test.bin
```

#### Windows (MSYS2)
```bash
# Check versions
algo-compiler.exe --version
a1m-asm.exe --version
a1m-emu.exe --version
a1m-console.exe --version

# Test with example
algo-compiler.exe examples/algo/01_hello_world.algo -o test.asm
a1m-asm.exe test.asm -o test.bin
a1m-emu.exe test.bin
```

### Test VS Code Extension

1. Open VS Code
2. Open the `A1M_Compiler` folder
3. Open `examples/algo/01_hello_world.algo`
4. Click the **▶ Run** button in the title bar
5. Check the terminal for output

---

## Installation Locations

### Default Paths

| Platform | Installation Directory | Executables |
|----------|----------------------|-------------|
| **Linux** | `/usr/local/bin` | `algo-compiler`, `a1m-asm`, `a1m-emu`, `a1m-console` |
| **macOS** | `/usr/local/bin` | `algo-compiler`, `a1m-asm`, `a1m-emu`, `a1m-console` |
| **Windows (MSYS2)** | `/usr/local/bin` | `algo-compiler.exe`, `a1m-asm.exe`, `a1m-emu.exe`, `a1m-console.exe` |

### Checking Installation

```bash
# Find where executables are installed
which algo-compiler        # Linux/macOS
which algo-compiler.exe    # Windows (MSYS2)

# Or use whereis
whereis algo-compiler

# List all installed A1M tools
ls -la /usr/local/bin/a1m*
ls -la /usr/local/bin/algo*
```

---

## Uninstallation

### Automatic Uninstallation

#### Linux / macOS
```bash
sudo ./uninstall.sh
```

#### Windows (MSYS2)
```bash
./uninstall.sh
```

### Manual Uninstallation

#### Remove Executables

**Linux / macOS**:
```bash
sudo rm /usr/local/bin/algo-compiler
sudo rm /usr/local/bin/a1m-asm
sudo rm /usr/local/bin/a1m-emu
sudo rm /usr/local/bin/a1m-console
```

**Windows (MSYS2)**:
```bash
rm /usr/local/bin/algo-compiler.exe
rm /usr/local/bin/a1m-asm.exe
rm /usr/local/bin/a1m-emu.exe
rm /usr/local/bin/a1m-console.exe
```

#### Remove VS Code Extension

1. Open VS Code
2. Press `Ctrl+Shift+X` (Windows/Linux) or `Cmd+Shift+X` (macOS)
3. Find "Algo Language Support"
4. Click gear icon → **Uninstall**

Or via command line:
```bash
code --uninstall-extension a1m.algo-language
```

---

## Troubleshooting

### "Permission denied" on Linux/macOS

**Problem**: Can't install without sudo permissions.

**Solution**: Use sudo for installation:
```bash
sudo ./install.sh
```

Or install to user directory:
```bash
cd compiler
make install PREFIX=$HOME/.local
# Add ~/.local/bin to PATH
```

### "Command not found" after installation

**Problem**: Installation directory not in PATH.

**Solution**:

**Linux/macOS**: Add to `~/.bashrc` or `~/.zshrc`:
```bash
export PATH="/usr/local/bin:$PATH"
```

**Windows (MSYS2)**: Check PATH:
```bash
echo $PATH | grep /usr/local/bin
```

If not found, add to `~/.bashrc`:
```bash
export PATH="/usr/local/bin:$PATH"
```

### VS Code Extension Not Working

**Problem**: Extension doesn't detect compiler.

**Solutions**:
1. Make sure toolchain is installed (run `which algo-compiler`)
2. Open the A1M_Compiler folder as workspace in VS Code
3. Check VS Code settings for "Algo" - paths should be auto-detected
4. Reload VS Code window (`Ctrl+Shift+P` → "Reload Window")

### Windows: Executables work in MSYS2 but not PowerShell

**Problem**: Installed in MSYS2's `/usr/local/bin`, not Windows PATH.

**Solutions**:

**Option 1**: Use MSYS2 terminal for running commands

**Option 2**: Copy to Windows-accessible location:
```bash
# In MSYS2
mkdir -p /c/Tools/A1M
cp /usr/local/bin/*.exe /c/Tools/A1M/
```

Then add `C:\Tools\A1M` to Windows PATH:
1. Press Windows Key + X → System
2. Advanced system settings → Environment Variables
3. Edit "Path" → New → `C:\Tools\A1M`

---

## Advanced Options

### Install to Custom Location

```bash
# Install to specific directory
make install PREFIX=/opt/a1m

# Or to user directory
make install PREFIX=$HOME/local

# Add to PATH
export PATH="/opt/a1m/bin:$PATH"  # Add to ~/.bashrc
```

### Install Only Specific Components

```bash
# Install only compiler
cd compiler
sudo make install
cd ..

# Install only assembler
cd assembler
sudo make install
cd ..
```

### Parallel Installation with Different Versions

Install to different directories:

```bash
# Version 1.0
make install PREFIX=/opt/a1m-1.0

# Version 2.0
make install PREFIX=/opt/a1m-2.0

# Switch versions by changing PATH
export PATH="/opt/a1m-2.0/bin:$PATH"
```

---

## Post-Installation

### Configuration

The toolchain works out-of-the-box with no configuration needed.

For VS Code extension configuration, see [vsextension/README-CROSSPLATFORM.md](vsextension/README-CROSSPLATFORM.md).

### Testing

Run the test suite:
```bash
# Test examples
./demo.sh

# Test specific programs
./run.sh examples/algo/07_fibonacci.algo
```

### Documentation

- **Language Guide**: [QUICK_REFERENCE.md](QUICK_REFERENCE.md)
- **Build Guide**: [BUILD_GUIDE.md](BUILD_GUIDE.md)
- **VS Code Extension**: [vsextension/README-CROSSPLATFORM.md](vsextension/README-CROSSPLATFORM.md)
- **Platform Guide**: [PLATFORM_QUICK_REF.md](PLATFORM_QUICK_REF.md)

---

## Getting Help

If you encounter issues:

1. Check this installation guide
2. Read [BUILD_GUIDE.md](BUILD_GUIDE.md)
3. Run `make info` in any component directory
4. Check existing issues: https://github.com/algoscienceacademy/A1M_Compiler/issues
5. Open a new issue with:
   - Your OS and version
   - Output of `gcc --version` or `clang --version`
   - Output of `make info`
   - Full error messages

---

**Last Updated**: November 16, 2025
