# Cross-Platform Quick Reference

Quick commands for building and using A1M Compiler on different platforms.

---

## 🚀 Quick Start

### Windows (MSYS2/MinGW64)
```bash
# Install MSYS2, then in MinGW64 terminal:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make make
cd A1M_Compiler
./build-windows.bat

# Test
./compiler/algo-compiler.exe --version
```

### macOS
```bash
# Install Xcode tools:
xcode-select --install

cd A1M_Compiler
chmod +x build-macos.sh
./build-macos.sh

# Test
./compiler/algo-compiler --version
```

### Linux
```bash
# Install gcc and make (if needed)
sudo apt-get install build-essential  # Ubuntu/Debian
cd A1M_Compiler
chmod +x build.sh
./build.sh

# Test
./compiler/algo-compiler --version
```

---

## 📦 Build Commands

| Command | Windows | macOS | Linux |
|---------|---------|-------|-------|
| **Build All** | `./build-windows.bat` | `./build-macos.sh` | `./build.sh` |
| **Build Compiler** | `cd compiler && make` | `cd compiler && make` | `cd compiler && make` |
| **Build Assembler** | `cd assembler && make` | `cd assembler && make` | `cd assembler && make` |
| **Build Emulator** | `cd emulator && make` | `cd emulator && make` | `cd emulator && make` |
| **Clean** | `make clean` | `make clean` | `make clean` |
| **Platform Info** | `make info` | `make info` | `make info` |

---

## 🔧 Executables

| Tool | Windows | macOS/Linux |
|------|---------|-------------|
| Compiler | `algo-compiler.exe` | `algo-compiler` |
| Assembler | `a1m-asm.exe` | `a1m-asm` |
| Emulator | `a1m-emu.exe` | `a1m-emu` |
| Console | `a1m-console.exe` | `a1m-console` |

---

## 💻 Running Programs

### Windows
```bash
# Compile
./compiler/algo-compiler.exe examples/algo/01_hello_world.algo -o output.asm

# Assemble
./assembler/a1m-asm.exe output.asm -o output.bin

# Run
./emulator/a1m-emu.exe output.bin
```

### macOS/Linux
```bash
# Compile
./compiler/algo-compiler examples/algo/01_hello_world.algo -o output.asm

# Assemble
./assembler/a1m-asm output.asm -o output.bin

# Run
./emulator/a1m-emu output.bin
```

---

## 🎯 VS Code Extension

### Build Extension
```bash
cd vsextension
npm install
npm run compile
```

### Package Extension
```bash
npm install -g @vscode/vsce
vsce package
```

### Install Extension
1. Press `Ctrl+Shift+P` (Windows/Linux) or `Cmd+Shift+P` (macOS)
2. Type "Extensions: Install from VSIX"
3. Select `algo-language-1.3.0.vsix`

---

## ⚙️ Makefile Variables

### Platform Detection
```makefile
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    EXE_EXT := .exe
else
    DETECTED_OS := $(shell uname -s)
    EXE_EXT :=
endif
```

### See Detection
```bash
cd compiler
make info
```

Output:
```
Detected OS: Windows  (or Darwin for macOS, Linux for Linux)
Compiler: gcc
Target: algo-compiler.exe  (or algo-compiler on Unix)
```

---

## 🐛 Troubleshooting

### Windows: "gcc not found"
```bash
# Make sure you're in MSYS2 MinGW 64-bit terminal (NOT MSYS2 MSYS)
# Install GCC:
pacman -S mingw-w64-x86_64-gcc
```

### macOS: "xcode-select error"
```bash
xcode-select --install
```

### Linux: "make not found"
```bash
sudo apt-get install build-essential make  # Ubuntu/Debian
sudo dnf install gcc make                  # Fedora
sudo pacman -S base-devel                  # Arch
```

### VS Code: "Compiler not found"
1. Build the toolchain first
2. Extension auto-detects executables
3. Check workspace has `compiler/`, `assembler/`, `emulator/` folders
4. Or set paths in VS Code settings

---

## 📚 Documentation Files

| File | Description |
|------|-------------|
| `BUILD_GUIDE.md` | Complete build instructions for all platforms |
| `README.md` | Project overview and quick start |
| `CROSS_PLATFORM_UPDATE.md` | Detailed update changelog |
| `vsextension/README-CROSSPLATFORM.md` | Extension platform guide |

---

## 🔍 Quick Checks

### Verify Installation
```bash
# Check all tools are built:
ls -la compiler/algo-compiler*
ls -la assembler/a1m-asm*
ls -la emulator/a1m-emu*
ls -la gui-console/a1m-console*
```

### Test Full Toolchain
```bash
# Linux/macOS
./demo.sh

# Windows (in MSYS2 terminal)
bash demo.sh
```

---

## 🌐 Platform-Specific Commands

### Windows (PowerShell)
```powershell
# List executables
Get-ChildItem -Recurse -Filter "*.exe" | Select-Object FullName

# Run program
& ".\compiler\algo-compiler.exe" "file.algo"
```

### macOS/Linux (Bash/Zsh)
```bash
# List executables
find . -type f -executable

# Run program
./compiler/algo-compiler file.algo
```

---

## ✅ Platform Support Matrix

| Feature | Windows | macOS | Linux |
|---------|---------|-------|-------|
| Build Tools | ✅ MSYS2 | ✅ Xcode | ✅ GCC |
| Compiler | ✅ | ✅ | ✅ |
| Assembler | ✅ | ✅ | ✅ |
| Emulator | ✅ | ✅ | ✅ |
| Console | ✅ | ✅ | ✅ |
| VS Extension | ✅ | ✅ | ✅ |
| Auto-detection | ✅ | ✅ | ✅ |
| Verilog Sim | ✅* | ✅ | ✅ |

*Requires GTKWave for Windows

---

**Last Updated**: November 16, 2025
