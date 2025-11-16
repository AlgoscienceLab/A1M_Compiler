# Quick Build Instructions for Windows

## Option 1: PowerShell (Recommended for Windows users)

### Enable Script Execution (One-time setup)
```powershell
# Run PowerShell as Administrator
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### Build
```powershell
cd C:\Users\shahrear\Downloads\A1M_Compiler
.\build-windows.ps1
```

---

## Option 2: MSYS2 MinGW64 Terminal (Best compatibility)

### Open MSYS2 MinGW 64-bit
1. Press **Windows Key**
2. Type **"MSYS2 MinGW 64-bit"**
3. Open the terminal

### Build
```bash
cd ~/Downloads/A1M_Compiler
# Or if cloned elsewhere:
cd /c/Users/shahrear/Downloads/A1M_Compiler

# Build all components
./build-windows.bat
# Or use:
bash build.sh
```

---

## Option 3: Manual Build from PowerShell

If you can't run scripts, manually compile each component:

### 1. Set up MSYS2 PATH
```powershell
$env:PATH = "C:\msys64\mingw64\bin;C:\msys64\usr\bin;$env:PATH"
```

### 2. Build Compiler
```powershell
cd compiler
make clean
make
cd ..
```

### 3. Build Assembler
```powershell
cd assembler
make clean
make
cd ..
```

### 4. Build Emulator
```powershell
cd emulator
make clean
make
cd ..
```

### 5. Build Console
```powershell
cd gui-console
make clean
make
cd ..
```

---

## Verification

After building, verify executables exist:

### PowerShell
```powershell
ls compiler\algo-compiler.exe
ls assembler\a1m-asm.exe
ls emulator\a1m-emu.exe
ls gui-console\a1m-console.exe
```

### Test
```powershell
.\compiler\algo-compiler.exe examples\algo\01_hello_world.algo -o test.asm
.\assembler\a1m-asm.exe test.asm -o test.bin
.\emulator\a1m-emu.exe test.bin
```

---

## Troubleshooting

### "make is not recognized"
**Problem**: MSYS2 not in PATH or not installed.

**Solution**:
1. Install MSYS2 from: https://www.msys2.org/
2. Open **MSYS2 MinGW 64-bit** terminal
3. Run: `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make make`
4. Use MSYS2 terminal for building

### PowerShell Script Blocked
**Problem**: Execution policy restricts scripts.

**Solution**:
```powershell
# Run as Administrator
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
```

Or bypass for one command:
```powershell
PowerShell -ExecutionPolicy Bypass -File .\build-windows.ps1
```

---

## What Gets Built

After successful build:

```
A1M_Compiler/
├── compiler/
│   ├── algo-compiler.exe    ✓ Built
│   └── obj/                 (build artifacts)
├── assembler/
│   ├── a1m-asm.exe          ✓ Built
│   └── obj/                 (build artifacts)
├── emulator/
│   ├── a1m-emu.exe          ✓ Built
│   └── obj/                 (build artifacts)
└── gui-console/
    └── a1m-console.exe      ✓ Built
```

---

## Next Steps

1. **Test the Build**: Run the verification commands above
2. **Install Globally** (optional): Open MSYS2 terminal and run `./install.sh`
3. **Install VS Code Extension**: Run `vsextension\install-extension.bat`

---

**Need Help?** See [WINDOWS_INSTALL.md](WINDOWS_INSTALL.md) for detailed instructions.
