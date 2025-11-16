# A1M Compiler - Cross-Platform Build Guide

This guide explains how to build the A1M Compiler toolchain on different platforms.

## Supported Platforms

- **Linux** (Ubuntu, Debian, Arch, Fedora, etc.)
- **macOS** (10.15 Catalina and later)
- **Windows** (via MSYS2/MinGW64)

---

## Prerequisites

### Linux
```bash
# Debian/Ubuntu
sudo apt-get update
sudo apt-get install build-essential gcc make

# Fedora/RHEL
sudo dnf install gcc make

# Arch Linux
sudo pacman -S base-devel gcc make
```

### macOS
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Or install via Homebrew
brew install gcc make
```

### Windows (MSYS2/MinGW64)

1. **Download MSYS2**: https://www.msys2.org/
2. **Install MSYS2** to `C:\msys64` (default location)
3. **Open "MSYS2 MinGW 64-bit" terminal** from Start Menu
4. **Update package database**:
   ```bash
   pacman -Syu
   ```
5. **Install development tools**:
   ```bash
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make make git
   ```

---

## Building the Toolchain

### Quick Build (All Platforms)

#### Linux
```bash
./build.sh
```

#### macOS
```bash
chmod +x build-macos.sh
./build-macos.sh
```

#### Windows (MSYS2 MinGW64 Terminal)
```bash
./build-windows.bat
# Or use bash script:
./build.sh
```

### Manual Build (Step by Step)

All platforms can use these commands in their respective terminals:

```bash
# 1. Build the compiler
cd compiler
make
cd ..

# 2. Build the assembler
cd assembler
make
cd ..

# 3. Build the emulator
cd emulator
make
cd ..

# 4. Build the GUI console
cd gui-console
make
cd ..
```

---

## Verification

After building, verify the executables:

### Linux/macOS
```bash
./compiler/algo-compiler --version
./assembler/a1m-asm --version
./emulator/a1m-emu --version
./gui-console/a1m-console --version
```

### Windows
```bash
./compiler/algo-compiler.exe --version
./assembler/a1m-asm.exe --version
./emulator/a1m-emu.exe --version
./gui-console/a1m-console.exe --version
```

---

## Running Example Programs

### Linux/macOS
```bash
# Compile and run a program
./compiler/algo-compiler examples/algo/01_hello_world.algo -o output.asm
./assembler/a1m-asm output.asm -o output.bin
./emulator/a1m-emu output.bin
```

### Windows
```bash
# Compile and run a program
./compiler/algo-compiler.exe examples/algo/01_hello_world.algo -o output.asm
./assembler/a1m-asm.exe output.asm -o output.bin
./emulator/a1m-emu.exe output.bin
```

---

## Makefile Information

All Makefiles now support automatic platform detection:
- Detects **Linux**, **macOS**, and **Windows**
- Automatically adds `.exe` extension on Windows
- Uses platform-appropriate commands (`rm` vs `del`, `mkdir` vs `md`)
- Run `make info` in any directory to see platform-specific configuration

### Example Commands

```bash
# See what platform was detected
cd compiler
make info

# Clean build artifacts
make clean

# Rebuild everything
make clean && make
```

---

## VS Code Extension

The VS Code extension now supports all platforms:

1. **Extension auto-detects platform** and uses correct executable extensions
2. **Finds local or global tools** automatically
3. **Terminal commands** adapt to Windows PowerShell or Unix shells

### Building the Extension

```bash
cd vsextension
npm install
npm run compile
```

### Installing the Extension

1. Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on macOS)
2. Type "Extensions: Install from VSIX"
3. Select the generated `.vsix` file

---

## Troubleshooting

### Windows: "gcc: command not found"
- Make sure you're using **MSYS2 MinGW 64-bit** terminal (not MSYS2 MSYS)
- Verify gcc is installed: `pacman -S mingw-w64-x86_64-gcc`

### macOS: "xcrun: error: invalid active developer path"
- Install Xcode Command Line Tools: `xcode-select --install`

### Linux: "make: command not found"
- Install build tools for your distribution (see Prerequisites)

### Permission Denied (Linux/macOS)
```bash
chmod +x build.sh
chmod +x build-macos.sh
```

---

## Platform-Specific Notes

### Windows
- Executables have `.exe` extension
- Use MSYS2 MinGW64 terminal for building
- Windows Command Prompt and PowerShell can run the executables after building
- Path separators are handled automatically by the Makefiles

### macOS
- May use either GCC or Clang (Apple's default compiler)
- Both work equally well for this project
- Universal binaries for Apple Silicon (M1/M2) supported

### Linux
- Tested on Ubuntu 20.04+, Debian 11+, Arch Linux, Fedora 35+
- Should work on any Linux distribution with GCC 7.0+

---

## Clean Build

To perform a complete clean rebuild:

### Linux/macOS
```bash
# Clean all components
cd compiler && make clean && cd ..
cd assembler && make clean && cd ..
cd emulator && make clean && cd ..
cd gui-console && make clean && cd ..

# Rebuild everything
./build.sh
```

### Windows
```bash
# Clean all components
cd compiler && make clean && cd ..
cd assembler && make clean && cd ..
cd emulator && make clean && cd ..
cd gui-console && make clean && cd ..

# Rebuild everything
./build-windows.bat
```

---

## Getting Help

If you encounter issues:
1. Check the troubleshooting section above
2. Verify prerequisites are installed correctly
3. Run `make info` to see platform detection
4. Open an issue on GitHub with:
   - Your OS and version
   - Output of `gcc --version`
   - Output of `make info`
   - Full error message

---

## License

MIT License - See LICENSE file for details
