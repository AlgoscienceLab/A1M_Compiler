# Simple Installation Instructions for Windows

## The Easiest Way 🚀

### Open MSYS2 MinGW 64-bit Terminal

1. Press **Windows Key**
2. Type: **"MSYS2 MinGW 64-bit"**
3. Press Enter

### Run the Setup Script

```bash
cd /c/Users/shahrear/Downloads/A1M_Compiler
bash setup-windows.sh
```

**That's it!** The script will:
- ✅ Install make (if needed)
- ✅ Build all 4 components
- ✅ Ask if you want to install globally
- ✅ Test the installation
- ✅ Optionally build VS Code extension

---

## Alternative: From PowerShell

If you prefer PowerShell:

```powershell
cd C:\Users\shahrear\Downloads\A1M_Compiler
PowerShell -ExecutionPolicy Bypass -File .\setup-windows-launcher.ps1
```

This will open MSYS2 and run the setup automatically.

---

## Manual Installation (Step by Step)

If you want full control:

### 1. Open MSYS2 MinGW 64-bit

### 2. Install Make (if needed)
```bash
pacman -S make mingw-w64-x86_64-make
```

### 3. Navigate to Project
```bash
cd /c/Users/shahrear/Downloads/A1M_Compiler
```

### 4. Build All Components
```bash
# Compiler
cd compiler && make && cd ..

# Assembler
cd assembler && make && cd ..

# Emulator
cd emulator && make && cd ..

# Console
cd gui-console && make && cd ..
```

### 5. Install Globally (Optional)
```bash
cd compiler && make install && cd ..
cd assembler && make install && cd ..
cd emulator && make install && cd ..
cd gui-console && make install && cd ..
```

### 6. Build VS Code Extension (Optional)
```bash
cd vsextension
npm install
npm run compile
npm install -g @vscode/vsce
vsce package
code --install-extension *.vsix
```

---

## What You'll Get

After installation:

```
✓ compiler/algo-compiler.exe       - Algo language compiler
✓ assembler/a1m-asm.exe            - A1M assembler
✓ emulator/a1m-emu.exe             - A1M emulator
✓ gui-console/a1m-console.exe      - Interactive console
✓ vsextension/*.vsix               - VS Code extension (optional)
```

If you chose global installation:
```
✓ /usr/local/bin/algo-compiler.exe  - Available everywhere in MSYS2
✓ /usr/local/bin/a1m-asm.exe
✓ /usr/local/bin/a1m-emu.exe
✓ /usr/local/bin/a1m-console.exe
```

---

## Quick Test

After building:

```bash
# Compile an example
./compiler/algo-compiler.exe examples/algo/01_hello_world.algo -o test.asm

# Assemble it
./assembler/a1m-asm.exe test.asm -o test.bin

# Run it
./emulator/a1m-emu.exe test.bin
```

If globally installed:
```bash
algo-compiler.exe examples/algo/01_hello_world.algo -o test.asm
a1m-asm.exe test.asm -o test.bin
a1m-emu.exe test.bin
```

---

## Troubleshooting

**"pacman: command not found"**
- You're not in MSYS2 terminal
- Open "MSYS2 MinGW 64-bit" from Start Menu

**"make: command not found"**
- Run: `pacman -S make mingw-w64-x86_64-make`

**Build errors**
- Make sure you're in MinGW64 terminal (not MSYS2 MSYS)
- Check GCC is installed: `pacman -S mingw-w64-x86_64-gcc`

---

## Files Created

The automated setup script is: **`setup-windows.sh`**

This single script does everything automatically!

---

**Ready to start?** 

Just open MSYS2 MinGW 64-bit and run:
```bash
cd /c/Users/shahrear/Downloads/A1M_Compiler
bash setup-windows.sh
```

🎉 Done!
