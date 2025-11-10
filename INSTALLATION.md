# A1M CPU Toolchain - Global Installation Guide

This guide explains how to install and use the A1M CPU toolchain globally on Ubuntu.

## Quick Installation

```bash
cd /home/shahrear/Documents/A1MCPU
sudo ./install.sh
```

This will install three commands globally:
- `algo` - Algo language compiler
- `a1m-asm` - A1M assembler
- `a1m-run` - A1M emulator
- `algo-run` - One-command wrapper for the complete workflow

## Installed Commands

### 1. `algo` - Algo Compiler
Compiles `.algo` source files to `.asm` assembly files.

**Usage:**
```bash
algo <input.algo> -o <output.asm>
```

**Example:**
```bash
algo myprogram.algo -o myprogram.asm
```

### 2. `a1m-asm` - A1M Assembler
Assembles `.asm` assembly files to `.bin` binary files.

**Usage:**
```bash
a1m-asm <input.asm> -o <output.bin>
```

**Example:**
```bash
a1m-asm myprogram.asm -o myprogram.bin
```

### 3. `a1m-emu` - A1M Emulator
Runs `.bin` binary files on the A1M CPU emulator.

**Usage:**
```bash
a1m-emu <input.bin>
```

**Example:**
```bash
a1m-emu myprogram.bin
```

### 4. `algo-run` - Complete Workflow Wrapper
Compiles, assembles, and runs an Algo program in one command.

**Usage:**
```bash
algo-run <input.algo> [options]
```

**Options:**
- `--keep-files` - Keep intermediate .asm and .bin files
- `--asm-only` - Only compile to assembly (don't assemble or run)
- `--bin-only` - Compile and assemble (don't run)

**Examples:**
```bash
# Run a program (cleans up intermediate files)
algo-run myprogram.algo

# Run and keep intermediate files
algo-run myprogram.algo --keep-files

# Only compile to assembly
algo-run myprogram.algo --asm-only

# Compile and assemble but don't run
algo-run myprogram.algo --bin-only
```

## Complete Workflow Examples

### Manual Pipeline
```bash
# Step by step
algo myprogram.algo -o myprogram.asm
a1m-asm myprogram.asm -o myprogram.bin
a1m-emu myprogram.bin

# Or in one line
algo myprogram.algo -o myprogram.asm && \
  a1m-asm myprogram.asm -o myprogram.bin && \
  a1m-emu myprogram.bin
```

### Using algo-run (Recommended)
```bash
# Simplest way - one command does everything
algo-run myprogram.algo
```

## Testing the Installation

Test from anywhere in your system:

```bash
# Create a test file
cd /tmp
cat > hello.algo << 'EOF'
func main() -> void {
    print("Hello from Algo!");
    print("The toolchain is working globally!");
}
EOF

# Run it
algo-run hello.algo
```

You should see:
```
[1/3] Compiling...
Compiling hello.algo...
Successfully generated hello.asm
[2/3] Assembling...
First pass: collecting labels...
Found 1 labels
Second pass: generating code...
Generated 135 instructions
Assembly complete: hello.asm -> hello.bin
[3/3] Running...
────────────────────────────────
Hello from Algo!
The toolchain is working globally!
────────────────────────────────
✓ Cleaned up intermediate files
```

## Running Examples from Anywhere

You can run any example from anywhere on your system:

```bash
# From your home directory
cd ~
algo-run /home/shahrear/Documents/A1MCPU/examples/algo/03_variables.algo

# From any directory
cd /tmp
algo-run ~/Documents/A1MCPU/examples/algo/fibonacci_new.algo
```

## File Locations

The installed binaries are located in:
```
/usr/local/bin/algo
/usr/local/bin/a1m-asm
/usr/local/bin/a1m-emu
/usr/local/bin/algo-run
```

These directories are in your system PATH, so the commands work from anywhere.

## Uninstallation

To remove the globally installed toolchain:

```bash
cd /home/shahrear/Documents/A1MCPU
sudo ./uninstall.sh
```

This will remove all four commands from `/usr/local/bin`.

## Reinstallation

To reinstall or update the toolchain:

```bash
cd /home/shahrear/Documents/A1MCPU
sudo ./uninstall.sh  # Optional: clean up old installation
sudo ./install.sh    # Install fresh version
```

## Troubleshooting

### Command not found
If you get "command not found" errors:
1. Make sure `/usr/local/bin` is in your PATH:
   ```bash
   echo $PATH | grep "/usr/local/bin"
   ```
2. If not, add it to your `~/.bashrc`:
   ```bash
   echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.bashrc
   source ~/.bashrc
   ```

### Permission denied
If you get permission errors:
- Make sure you ran `install.sh` with `sudo`
- Check file permissions:
  ```bash
  ls -l /usr/local/bin/algo*
  ls -l /usr/local/bin/a1m-*
  ```
  All should be executable (have `x` permission)

### Compilation errors
If you get compilation errors during installation:
- Make sure you have `gcc` installed:
  ```bash
  sudo apt update
  sudo apt install build-essential
  ```

## VS Code Integration

The A1M toolchain also has a VS Code extension that provides:
- Syntax highlighting for `.algo` files
- Real-time error detection
- Code suggestions
- Run button in `func main()`
- Automatic compile → assemble → emulate workflow

The extension uses these global commands, so make sure they're installed first.

## Quick Reference

| Task | Command |
|------|---------|
| Compile only | `algo file.algo -o file.asm` |
| Assemble only | `a1m-asm file.asm -o file.bin` |
| Run only | `a1m-emu file.bin` |
| Full pipeline (manual) | `algo file.algo -o file.asm && a1m-asm file.asm -o file.bin && a1m-emu file.bin` |
| Full pipeline (simple) | `algo-run file.algo` |
| Keep intermediate files | `algo-run file.algo --keep-files` |
| Compile to assembly only | `algo-run file.algo --asm-only` |

## Support

For more information:
- Check the main README: `/home/shahrear/Documents/A1MCPU/README.md`
- View examples: `/home/shahrear/Documents/A1MCPU/examples/algo/`
- Read documentation: `/home/shahrear/Documents/A1MCPU/docs/`
