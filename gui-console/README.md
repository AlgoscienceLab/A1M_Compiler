# A1M CPU Console

A lightweight, custom terminal-based console for running Algo programs on the A1M CPU emulator.

## Features

✨ **100% Custom C Implementation** - No third-party languages or frameworks
🚀 **Integrated Workflow** - Automatically compiles, assembles, and runs programs
💻 **Pure Terminal UI** - Works in any terminal, no graphics libraries needed
📝 **Supports All Formats** - Run .algo, .asm, or .bin files
🎯 **Built for A1M CPU** - Designed specifically for the A1M architecture

## Quick Start

### Interactive Mode
```bash
./console.sh
```

This opens the A1M Console menu where you can:
- Run Algo programs (.algo files)
- Run Assembly programs (.asm files)
- Run Binary programs (.bin files)
- View previous execution output
- Get help

### Quick Run Mode
```bash
./console.sh <filename>
```

Automatically detects file type and runs it:
```bash
./console.sh examples/asm/hello.asm
./console.sh examples/algo/hello.algo
./console.sh output.bin
```

## Menu Options

```
┌────────────────────────────────────────────────────────────────────┐
│ [1] Run Algo Program    [2] Run Assembly    [3] Run Binary         │
│ [4] View Last Output    [5] Help            [6] Exit               │
└────────────────────────────────────────────────────────────────────┘
```

### [1] Run Algo Program
Compile and run a .algo file:
1. Enter filename (e.g., `examples/algo/hello.algo`)
2. Console compiles .algo → .asm
3. Console assembles .asm → .bin
4. Console runs .bin on A1M emulator
5. View output

### [2] Run Assembly
Assemble and run a .asm file:
1. Enter filename (e.g., `examples/asm/hello.asm`)
2. Console assembles .asm → .bin
3. Console runs .bin on A1M emulator
4. View output

### [3] Run Binary
Run a pre-assembled .bin file:
1. Enter filename
2. Console runs .bin on A1M emulator
3. View output

### [4] View Last Output
Display the output from the last program execution.

### [5] Help
Display detailed help information about the A1M CPU and console usage.

### [6] Exit
Close the console.

## Example Workflow

### Running an Algo Program
```
1. Start console: ./console.sh
2. Select option: 1
3. Enter filename: examples/algo/hello.algo
4. Watch the compilation process
5. See the output
```

### Running Assembly
```
1. Start console: ./console.sh
2. Select option: 2
3. Enter filename: examples/asm/fibonacci.asm
4. See the output
```

## Architecture

The console integrates three components:

```
.algo file
    ↓
[Algo Compiler] → .asm file
    ↓
[A1M Assembler] → .bin file
    ↓
[A1M Emulator] → Output
```

All components are custom-built for the A1M CPU:
- **Algo Compiler**: `compiler/algo-compiler`
- **A1M Assembler**: `assembler/a1m-asm`
- **A1M Emulator**: `emulator/a1m-emu`

## Building

The console is built automatically by `./build.sh` or manually:

```bash
make -C gui-console
```

Or use the convenience script:
```bash
./console.sh
```

## What Makes It Custom?

🔧 **No External Dependencies**
- Written in pure C using only standard libraries
- No GTK, Qt, ncurses, or other GUI frameworks
- No Python, JavaScript, or other scripting languages
- Completely self-contained

🎯 **Designed for A1M**
- Understands A1M architecture
- Integrates with custom toolchain
- Optimized for Algo language workflow
- Shows A1M-specific execution details

## Files

- `gui-console/a1m_console.c` - Main console source (pure C)
- `gui-console/Makefile` - Build configuration
- `console.sh` - Launch script

## Troubleshooting

**Console shows "A1M emulator not found!"**
- Run `./build.sh` to build all components first

**Cannot run .algo files**
- Check that `compiler/algo-compiler` exists
- Verify the .algo file syntax

**Assembly fails**
- Check the .asm file for syntax errors
- View assembler output for details

**Binary won't execute**
- Ensure the .bin file is valid A1M machine code
- Check file permissions

## Examples Included

### Assembly Examples
- `examples/asm/hello.asm` - Basic program
- `examples/asm/fibonacci.asm` - Fibonacci sequence
- `examples/asm/math.asm` - Math operations

### Algo Examples
- `examples/algo/hello.algo` - Hello world
- `examples/algo/variables.algo` - Variable usage
- `examples/algo/functions.algo` - Function definitions

## Technical Details

- **Language**: Pure C (C99)
- **Compiler**: GCC with -Wall -Wextra
- **Dependencies**: None (standard C library only)
- **Platform**: Linux (should work on any POSIX system)
- **Size**: ~700 lines of code
- **Binary**: ~20KB

## Comparison with Other Interfaces

| Interface | Language | Dependencies | Status |
|-----------|----------|--------------|--------|
| A1M Console | C | None | ✅ Working |
| GTK IDE | C | GTK3 | ⚠️ Library conflict |
| Terminal Scripts | Bash | None | ✅ Working |

## Future Enhancements

Potential improvements (keeping it custom):
- [ ] Interactive code editor (in-console editing)
- [ ] Register/memory viewer during execution
- [ ] Breakpoint support
- [ ] Step-through debugging
- [ ] Syntax highlighting (terminal colors)

## License

Part of the A1M CPU project. All custom implementation.

## Contributing

This console is designed to be simple and maintainable. When contributing:
- Keep it pure C (no external dependencies)
- Maintain the simple menu-driven interface
- Test with all three file types (.algo, .asm, .bin)
- Update this README with new features

## Questions?

Press [5] in the console menu for detailed help, or check:
- `FLOW_GUIDE.md` - Complete A1M workflow documentation
- `USAGE.md` - Detailed usage examples
- `README.md` - Main project README
