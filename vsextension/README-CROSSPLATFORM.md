# Algo Language Extension - Cross-Platform Support

This VS Code extension provides full support for the Algo programming language on **Linux**, **macOS**, and **Windows**.

## Platform Support

### ✅ Linux
- Full support for all distributions
- Auto-detects executables without `.exe` extension
- Uses bash/sh for terminal commands

### ✅ macOS
- Full support for Intel and Apple Silicon Macs
- Auto-detects executables without `.exe` extension
- Uses zsh/bash for terminal commands

### ✅ Windows
- Full support via MSYS2/MinGW64 or native Windows builds
- Auto-detects executables with `.exe` extension
- Uses PowerShell or Command Prompt for terminal commands

## Installation

### 1. Install the A1M Toolchain

#### Windows (MSYS2/MinGW64)
```bash
cd A1M_Compiler
./build-windows.bat
```

#### macOS
```bash
cd A1M_Compiler
chmod +x build-macos.sh
./build-macos.sh
```

#### Linux
```bash
cd A1M_Compiler
chmod +x build.sh
./build.sh
```

### 2. Build the Extension

```bash
cd vsextension
npm install
npm run compile
```

### 3. Package the Extension (Optional)

```bash
npm install -g @vscode/vsce
vsce package
```

This creates a `.vsix` file that can be installed in VS Code.

### 4. Install in VS Code

**Method 1: From VSIX**
1. Press `Ctrl+Shift+P` (Windows/Linux) or `Cmd+Shift+P` (macOS)
2. Type "Extensions: Install from VSIX"
3. Select the generated `.vsix` file

**Method 2: Development Mode**
1. Open the `vsextension` folder in VS Code
2. Press `F5` to launch Extension Development Host
3. Open an `.algo` file to test

## Features

### Auto-Detection
- **Automatic platform detection** (Windows, macOS, Linux)
- **Automatic executable detection** with proper extensions
- **Smart path resolution** for local and global installations

### Executable Resolution Order

The extension looks for executables in this order:

1. **User-configured paths** (in VS Code settings)
2. **Workspace-local builds**:
   - `{workspace}/compiler/algo-compiler[.exe]`
   - `{workspace}/assembler/a1m-asm[.exe]`
   - `{workspace}/emulator/a1m-emu[.exe]`
3. **System PATH** (globally installed tools)

### Terminal Integration

The extension creates platform-appropriate terminal commands:

**Windows (PowerShell)**:
```powershell
& ".\compiler\algo-compiler.exe" "file.algo" -o "file.asm"
& ".\assembler\a1m-asm.exe" "file.asm" -o "file.bin"
& ".\emulator\a1m-emu.exe" "file.bin"
```

**Unix (Linux/macOS)**:
```bash
./compiler/algo-compiler file.algo -o file.asm
./assembler/a1m-asm file.asm -o file.bin
./emulator/a1m-emu file.bin
```

## Configuration

Open VS Code Settings and search for "Algo" to configure:

```json
{
  "algo.compilerPath": "",    // Leave empty for auto-detection
  "algo.assemblerPath": "",   // Leave empty for auto-detection
  "algo.emulatorPath": ""     // Leave empty for auto-detection
}
```

### Custom Paths (Optional)

If tools are installed in non-standard locations:

**Windows**:
```json
{
  "algo.compilerPath": "C:\\tools\\a1m\\compiler\\algo-compiler.exe",
  "algo.assemblerPath": "C:\\tools\\a1m\\assembler\\a1m-asm.exe",
  "algo.emulatorPath": "C:\\tools\\a1m\\emulator\\a1m-emu.exe"
}
```

**macOS/Linux**:
```json
{
  "algo.compilerPath": "/usr/local/bin/algo-compiler",
  "algo.assemblerPath": "/usr/local/bin/a1m-asm",
  "algo.emulatorPath": "/usr/local/bin/a1m-emu"
}
```

## Usage

### Running Algo Programs

1. Open any `.algo` file
2. Click the **▶ Run** button in the title bar
3. Or press `Ctrl+Shift+P` and select "Run Algo Program"

The extension will:
1. Compile the `.algo` file to assembly (`.asm`)
2. Assemble to binary (`.bin`)
3. Execute in the emulator
4. Show output in an integrated terminal

### Compiling Only

1. Open any `.algo` file
2. Press `Ctrl+Shift+P` and select "Compile Algo Program"

This only compiles to assembly without running.

## Platform-Specific Notes

### Windows

**MSYS2/MinGW64**:
- Terminal commands work in both PowerShell and MSYS2 terminals
- Extension auto-detects `.exe` extensions
- Paths use Windows format (`C:\path\to\file`)

**Native Windows Builds**:
- If you build outside MSYS2, extension still works
- Ensure executables are in PATH or workspace

### macOS

**Apple Silicon (M1/M2)**:
- Native ARM64 executables supported
- Rosetta 2 x86_64 executables also work
- Extension works with both architectures

**Intel Macs**:
- Full x86_64 support
- No compatibility issues

### Linux

**All Distributions**:
- Tested on Ubuntu, Debian, Arch, Fedora
- Works with any distribution that has GCC
- No distribution-specific requirements

## Troubleshooting

### "Compiler not found" Error

**Check installation**:
```bash
# Windows (MSYS2)
where algo-compiler.exe

# macOS/Linux
which algo-compiler
```

**Verify workspace structure**:
```
A1M_Compiler/
  ├── compiler/algo-compiler[.exe]
  ├── assembler/a1m-asm[.exe]
  ├── emulator/a1m-emu[.exe]
  └── examples/
```

**Set explicit paths** in VS Code settings if auto-detection fails.

### Windows: Terminal Commands Don't Work

1. Make sure you're using PowerShell 5.1+ or Command Prompt
2. Check that executables have `.exe` extension
3. Try running commands manually in terminal:
   ```powershell
   & ".\compiler\algo-compiler.exe" --version
   ```

### macOS: "Permission Denied"

```bash
# Make executables executable
chmod +x compiler/algo-compiler
chmod +x assembler/a1m-asm
chmod +x emulator/a1m-emu
```

### Linux: Missing Dependencies

```bash
# Install build tools
sudo apt-get install build-essential  # Debian/Ubuntu
sudo dnf install gcc make              # Fedora
sudo pacman -S base-devel              # Arch
```

## Development

### Testing the Extension

1. Open `vsextension` folder in VS Code
2. Press `F5` to launch Extension Development Host
3. Open workspace with A1M Compiler
4. Open an `.algo` file and test features

### Building Changes

```bash
cd vsextension
npm run compile
```

### Packaging for Distribution

```bash
vsce package
```

This creates `algo-language-{version}.vsix`.

## Contributing

When contributing platform-specific improvements:

1. Test on all platforms (Windows, macOS, Linux)
2. Use `os.platform()` for platform detection
3. Use `path` module for cross-platform paths
4. Handle both `.exe` and non-`.exe` executables

## License

MIT License - See LICENSE file for details
