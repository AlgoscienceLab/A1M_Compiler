# Windows Build & Install - Complete Summary

## Current Status

✅ **Makefiles Updated** - All Makefiles support Windows/MSYS2  
✅ **Build Scripts Created** - PowerShell and Batch scripts ready  
✅ **Install Scripts Ready** - install.sh and uninstall.sh support Windows  
✅ **VS Extension Scripts** - install-extension.bat and .sh created  
⚠️ **MSYS2 Make Required** - Need to install make in MSYS2  

---

## Installation Instructions for You

### Step 1: Install Make in MSYS2

Open **MSYS2 MinGW 64-bit** terminal and run:

```bash
pacman -S make mingw-w64-x86_64-make
```

### Step 2: Build All Components

#### Option A: From MSYS2 Terminal (Recommended)
```bash
cd /c/Users/shahrear/Downloads/A1M_Compiler
./build-windows.bat
```

#### Option B: From PowerShell
```powershell
cd C:\Users\shahrear\Downloads\A1M_Compiler
PowerShell -ExecutionPolicy Bypass -File .\build-windows.ps1
```

### Step 3: Install Globally (Optional)

From MSYS2 terminal:
```bash
cd /c/Users/shahrear/Downloads/A1M_Compiler
./install.sh
```

This installs to `/usr/local/bin` (accessible in MSYS2).

### Step 4: Install VS Code Extension

#### Option A: From PowerShell/CMD
```batch
cd vsextension
install-extension.bat
```

#### Option B: From MSYS2
```bash
cd vsextension
bash install-extension.sh
```

---

## What Was Updated

### 1. All Makefiles (✅ Complete)

**Files Updated:**
- `compiler/Makefile`
- `assembler/Makefile`
- `emulator/Makefile`  
- `gui-console/Makefile`
- `verilog/Makefile`

**Features Added:**
- ✅ Platform detection (Windows/macOS/Linux)
- ✅ Automatic `.exe` extension on Windows
- ✅ Windows-compatible commands (`del`, `mkdir`, `rmdir`)
- ✅ `make install` target for all platforms
- ✅ `make uninstall` target for all platforms
- ✅ `make info` to show platform details
- ✅ Custom `PREFIX` support for install location

**Usage:**
```bash
# Build
make

# See platform info
make info

# Install (MSYS2 - no sudo needed)
make install

# Install to custom location
make install PREFIX=$HOME/.local

# Uninstall
make uninstall

# Clean
make clean
```

### 2. Build Scripts (✅ Complete)

**Created:**
- `build-windows.ps1` - PowerShell script for Windows
- `build-windows.bat` - Batch script for MSYS2 terminal
- `build-macos.sh` - macOS-specific build script
- `build.sh` - Universal Unix build script (works on Linux/macOS/MSYS2)

**Features:**
- ✅ Automatic MSYS2 detection
- ✅ GCC and Make verification
- ✅ Builds all 4 components sequentially
- ✅ Error checking and helpful messages
- ✅ Colored output (PowerShell and bash)

### 3. Install Scripts (✅ Complete)

**Updated:**
- `install.sh` - Now supports Windows/MSYS2
- `uninstall.sh` - Now supports Windows/MSYS2

**Features:**
- ✅ Platform auto-detection
- ✅ No sudo required on Windows/MSYS2
- ✅ Uses Makefile install targets
- ✅ Installs to `/usr/local/bin`
- ✅ Supports custom PREFIX

### 4. VS Code Extension (✅ Complete)

**Updated:**
- `vsextension/src/extension.ts` - Platform-aware executable detection
- `vsextension/package.json` - Version 1.3.0, updated description
- `vsextension/CHANGELOG.md` - Documented changes

**Created:**
- `vsextension/install-extension.sh` - Unix/MSYS2 installer
- `vsextension/install-extension.bat` - Windows batch installer

**Features:**
- ✅ Auto-detects platform (Windows/macOS/Linux)
- ✅ Auto-adds `.exe` extension on Windows
- ✅ Smart executable path resolution (workspace → global)
- ✅ Platform-specific terminal commands:
  - Windows: PowerShell syntax
  - Unix: Bash syntax
- ✅ Works with both local and global installations

### 5. Documentation (✅ Complete)

**Created:**
- `BUILD_GUIDE.md` - Comprehensive cross-platform build guide
- `CROSS_PLATFORM_UPDATE.md` - Detailed update summary
- `PLATFORM_QUICK_REF.md` - Quick reference for all platforms
- `WINDOWS_INSTALL.md` - Detailed Windows-specific guide
- `BUILD_WINDOWS_QUICK.md` - Quick Windows build instructions
- `INSTALL.md` - Complete installation guide
- `vsextension/README-CROSSPLATFORM.md` - Extension platform guide

**Updated:**
- `README.md` - Added platform badges and updated build section

---

## Build and Install Workflow

### For Windows Users

```
1. Install MSYS2
   ↓
2. Install build tools
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make make
   ↓
3. Build toolchain
   ./build-windows.bat (from MSYS2)
   OR
   .\build-windows.ps1 (from PowerShell)
   ↓
4. [Optional] Install globally
   ./install.sh (from MSYS2)
   ↓
5. [Optional] Install VS Extension
   vsextension\install-extension.bat
   ↓
6. Test
   algo-compiler.exe examples\algo\01_hello_world.algo
```

---

## Command Reference

### Building

| Task | Command (MSYS2) | Command (PowerShell) |
|------|----------------|---------------------|
| Build All | `./build-windows.bat` | `.\build-windows.ps1` |
| Build Compiler | `cd compiler && make` | `cd compiler ; make` |
| Clean | `make clean` | `make clean` |
| Platform Info | `make info` | `make info` |

### Installing

| Task | Command (MSYS2) | Notes |
|------|----------------|-------|
| Install All | `./install.sh` | No sudo on Windows |
| Install Compiler | `cd compiler && make install` | |
| Custom Location | `make install PREFIX=$HOME/.local` | |
| Uninstall | `./uninstall.sh` | |

### VS Code Extension

| Task | Command | Platform |
|------|---------|----------|
| Build & Package | `install-extension.bat` | Windows |
| Build & Package | `bash install-extension.sh` | MSYS2 |
| Install | Auto-prompted | All |
| Manual Install | `code --install-extension *.vsix` | All |

---

## File Structure After Build

```
A1M_Compiler/
├── compiler/
│   ├── algo-compiler.exe       ← Built executable
│   ├── obj/                    ← Build artifacts
│   ├── src/                    ← Source files
│   ├── include/                ← Headers
│   └── Makefile                ← ✅ Updated
│
├── assembler/
│   ├── a1m-asm.exe             ← Built executable
│   ├── obj/                    ← Build artifacts
│   ├── src/                    ← Source files
│   └── Makefile                ← ✅ Updated
│
├── emulator/
│   ├── a1m-emu.exe             ← Built executable
│   ├── obj/                    ← Build artifacts
│   ├── src/                    ← Source files
│   ├── include/                ← Headers
│   └── Makefile                ← ✅ Updated
│
├── gui-console/
│   ├── a1m-console.exe         ← Built executable
│   ├── src/                    ← Source files
│   └── Makefile                ← ✅ Updated
│
├── vsextension/
│   ├── out/                    ← Compiled TypeScript
│   ├── algo-language-1.3.0.vsix ← Packaged extension
│   ├── install-extension.bat   ← ✅ New
│   ├── install-extension.sh    ← ✅ New
│   ├── src/extension.ts        ← ✅ Updated
│   ├── package.json            ← ✅ Updated
│   └── CHANGELOG.md            ← ✅ Updated
│
├── build-windows.ps1           ← ✅ New
├── build-windows.bat           ← ✅ Updated
├── build-macos.sh              ← ✅ New
├── build.sh                    ← Existing
├── install.sh                  ← ✅ Updated
├── uninstall.sh                ← ✅ Updated
│
└── Documentation:
    ├── BUILD_GUIDE.md          ← ✅ New
    ├── BUILD_WINDOWS_QUICK.md  ← ✅ New
    ├── CROSS_PLATFORM_UPDATE.md ← ✅ New
    ├── INSTALL.md              ← ✅ New
    ├── PLATFORM_QUICK_REF.md   ← ✅ New
    ├── WINDOWS_INSTALL.md      ← ✅ New
    └── README.md               ← ✅ Updated
```

---

## Next Steps for You

1. **Install Make** (if not done):
   ```bash
   # In MSYS2 MinGW 64-bit terminal
   pacman -S make mingw-w64-x86_64-make
   ```

2. **Build the Toolchain**:
   ```bash
   # In MSYS2
   cd /c/Users/shahrear/Downloads/A1M_Compiler
   ./build-windows.bat
   ```

3. **Test the Build**:
   ```bash
   ./compiler/algo-compiler.exe examples/algo/01_hello_world.algo -o test.asm
   ./assembler/a1m-asm.exe test.asm -o test.bin
   ./emulator/a1m-emu.exe test.bin
   ```

4. **[Optional] Install Globally**:
   ```bash
   ./install.sh
   ```

5. **[Optional] Build VS Extension**:
   ```bash
   cd vsextension
   bash install-extension.sh
   ```

---

## Verification Checklist

After completing the steps above:

- [ ] All 4 executables built (compiler, assembler, emulator, console)
- [ ] Can run `algo-compiler.exe --version`
- [ ] Can compile and run example programs
- [ ] [Optional] Tools installed to /usr/local/bin
- [ ] [Optional] VS Code extension installed and working

---

## Getting Help

All documentation files are ready:

- Quick start: `BUILD_WINDOWS_QUICK.md`
- Detailed guide: `WINDOWS_INSTALL.md`
- All platforms: `BUILD_GUIDE.md`
- Installation: `INSTALL.md`
- Platform reference: `PLATFORM_QUICK_REF.md`

---

**Status**: ✅ All scripts and Makefiles ready for Windows/MSYS2  
**Action Required**: Install make in MSYS2, then run build script  
**Last Updated**: November 16, 2025
