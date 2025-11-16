# Windows Installation Guide (MSYS2/MinGW64)

Complete step-by-step guide for setting up the A1M Compiler toolchain on Windows.

---

## Prerequisites

- **Windows 10** or **Windows 11** (64-bit)
- **500 MB** free disk space for MSYS2
- **Internet connection** for downloading packages

---

## Step 1: Install MSYS2

### Download MSYS2

1. Go to https://www.msys2.org/
2. Download the installer: `msys2-x86_64-YYYYMMDD.exe`
3. Run the installer

### Installation Steps

1. **Run the installer**
   - Accept the default installation path: `C:\msys64`
   - Click "Next" through the installation

2. **Finish installation**
   - Check "Run MSYS2 now"
   - Click "Finish"

3. **Initial Setup**
   - A terminal window will open
   - Run this command to update the package database:
     ```bash
     pacman -Syu
     ```
   - Press `Y` when prompted
   - **Close the terminal when it says to** (this is important!)

---

## Step 2: Install Development Tools

### Open MSYS2 MinGW 64-bit Terminal

**Important**: You must use **MSYS2 MinGW 64-bit**, not "MSYS2 MSYS"

1. Press **Windows Key**
2. Type **"MSYS2 MinGW 64-bit"**
3. Open the terminal (it should have a blue icon)

### Install GCC and Make

In the MSYS2 MinGW 64-bit terminal, run:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make make git
```

Press `Y` to confirm installation.

### Verify Installation

```bash
gcc --version
make --version
```

You should see version information for both tools.

---

## Step 3: Download A1M Compiler

### Option 1: Using Git (Recommended)

```bash
cd ~
git clone https://github.com/algoscienceacademy/A1M_Compiler.git
cd A1M_Compiler
```

### Option 2: Download ZIP

1. Go to https://github.com/algoscienceacademy/A1M_Compiler
2. Click "Code" → "Download ZIP"
3. Extract to a location (e.g., `C:\Users\YourName\A1M_Compiler`)
4. In MSYS2 terminal:
   ```bash
   cd /c/Users/YourName/A1M_Compiler
   ```

---

## Step 4: Build the Toolchain

### Quick Build (Recommended)

```bash
./build-windows.bat
```

This will build all components automatically.

### Manual Build (Alternative)

Build each component individually:

```bash
# Compiler
cd compiler
make
cd ..

# Assembler
cd assembler
make
cd ..

# Emulator
cd emulator
make
cd ..

# Console
cd gui-console
make
cd ..
```

### Verify Build

Check that executables were created:

```bash
ls -la compiler/algo-compiler.exe
ls -la assembler/a1m-asm.exe
ls -la emulator/a1m-emu.exe
ls -la gui-console/a1m-console.exe
```

---

## Step 5: Test the Installation

### Run a Test Program

```bash
# Compile an example
./compiler/algo-compiler.exe examples/algo/01_hello_world.algo -o test.asm

# Assemble it
./assembler/a1m-asm.exe test.asm -o test.bin

# Run it
./emulator/a1m-emu.exe test.bin
```

You should see output from the program!

### Run the Demo

```bash
bash demo.sh
```

This will run several example programs.

---

## Step 6: Install VS Code Extension (Optional)

### Prerequisites

1. **Install Node.js** from https://nodejs.org/
   - Download the LTS version
   - Run the installer with default settings

2. **Install Visual Studio Code** from https://code.visualstudio.com/

### Build the Extension

In MSYS2 terminal:

```bash
cd vsextension
npm install
npm run compile
```

### Package the Extension

```bash
npm install -g @vscode/vsce
vsce package
```

This creates `algo-language-1.3.0.vsix`

### Install in VS Code

1. Open VS Code
2. Press `Ctrl+Shift+P`
3. Type "Extensions: Install from VSIX"
4. Navigate to `A1M_Compiler/vsextension/`
5. Select `algo-language-1.3.0.vsix`
6. Click "Install"
7. Reload VS Code

### Test the Extension

1. Open the `A1M_Compiler` folder in VS Code
2. Open `examples/algo/01_hello_world.algo`
3. Click the **▶ Run** button in the title bar
4. Watch the program compile and run in the terminal!

---

## Using Outside MSYS2

### Add to Windows PATH (Optional)

To use the tools from Windows Command Prompt or PowerShell:

1. **Copy executables** to a permanent location:
   ```bash
   mkdir -p /c/Tools/A1M
   cp compiler/algo-compiler.exe /c/Tools/A1M/
   cp assembler/a1m-asm.exe /c/Tools/A1M/
   cp emulator/a1m-emu.exe /c/Tools/A1M/
   ```

2. **Add to PATH**:
   - Press **Windows Key + X**
   - Click **"System"**
   - Click **"Advanced system settings"**
   - Click **"Environment Variables"**
   - Under "System variables", find **"Path"**
   - Click **"Edit"**
   - Click **"New"**
   - Add: `C:\Tools\A1M`
   - Click **"OK"** on all dialogs

3. **Test in PowerShell**:
   ```powershell
   algo-compiler.exe --version
   ```

---

## Troubleshooting

### "pacman: command not found"

**Problem**: You're not in an MSYS2 terminal.

**Solution**: Open **MSYS2 MinGW 64-bit** from the Start Menu.

---

### "gcc: command not found"

**Problem**: GCC is not installed or you're in the wrong terminal.

**Solution**: 
1. Make sure you're in **MSYS2 MinGW 64-bit** (not MSYS2 MSYS)
2. Install GCC:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```

---

### Build Errors: "No such file or directory"

**Problem**: Path issues or files not extracted properly.

**Solution**:
1. Make sure you extracted all files
2. Navigate to the correct directory:
   ```bash
   cd ~/A1M_Compiler
   pwd  # Should show /home/YourName/A1M_Compiler
   ```

---

### VS Code Extension Not Working

**Problem**: Tools not found or wrong paths.

**Solution**:
1. Make sure you built the toolchain in the workspace
2. Open **A1M_Compiler** as the workspace folder
3. Check VS Code settings (Ctrl+,) for "Algo"
4. Leave paths empty for auto-detection

---

### "Permission Denied" Errors

**Problem**: Script is not executable.

**Solution**:
```bash
chmod +x build.sh
chmod +x demo.sh
chmod +x build-windows.bat
```

---

### MSYS2 Terminal Closes Immediately

**Problem**: Happens during initial update.

**Solution**: This is normal! Just reopen **MSYS2 MinGW 64-bit** from Start Menu.

---

## Alternative: Using WSL (Windows Subsystem for Linux)

If you prefer, you can use WSL instead of MSYS2:

### Install WSL

```powershell
# In PowerShell (Admin)
wsl --install
```

### Build in WSL

```bash
# In WSL terminal
sudo apt-get update
sudo apt-get install build-essential git
git clone https://github.com/algoscienceacademy/A1M_Compiler.git
cd A1M_Compiler
chmod +x build.sh
./build.sh
```

---

## Uninstallation

### Remove MSYS2

1. Uninstall from **Settings** → **Apps** → **MSYS2**
2. Delete `C:\msys64` folder if it remains

### Remove A1M Compiler

Just delete the `A1M_Compiler` folder.

### Remove VS Code Extension

1. Open VS Code
2. Press `Ctrl+Shift+X`
3. Find "Algo Language Support"
4. Click the gear icon → "Uninstall"

---

## Next Steps

- Read [QUICK_REFERENCE.md](QUICK_REFERENCE.md) for language guide
- Browse [examples/algo/](examples/algo/) for example programs
- Check [docs/](docs/) for detailed documentation
- Try the interactive console: `./gui-console/a1m-console.exe`

---

## Getting Help

- **Documentation**: See [BUILD_GUIDE.md](BUILD_GUIDE.md)
- **Issues**: https://github.com/algoscienceacademy/A1M_Compiler/issues
- **Quick Ref**: [PLATFORM_QUICK_REF.md](PLATFORM_QUICK_REF.md)

---

## Useful MSYS2 Commands

```bash
# Update MSYS2 packages
pacman -Syu

# Search for a package
pacman -Ss packagename

# Install a package
pacman -S packagename

# Remove a package
pacman -R packagename

# List installed packages
pacman -Q

# Navigate to Windows directories
cd /c/Users/YourName/Desktop    # Your Desktop
cd /c/                          # C drive
cd ~                            # Your MSYS2 home
```

---

**Last Updated**: November 16, 2025  
**Platform**: Windows 10/11 with MSYS2/MinGW64
