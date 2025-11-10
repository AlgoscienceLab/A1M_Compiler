# Algo Language Support for VS Code

Full language support for the A1M Algo programming language.

## Features

### 🎨 Syntax Highlighting
- Keywords: `func`, `let`, `if`, `else`, `while`, `for`, `return`, `enum`, `struct`, etc.
- Types: `void`, `int`, `char`, `bool`, `i64`, `u64`
- Operators, strings, numbers, and comments
- Preprocessor directives (`#include`)

### 🔍 Real-time Error Detection
- Compile-on-save for instant error feedback
- Real-time diagnostics as you type
- Error messages displayed inline with red squiggles

### 💡 IntelliSense & Code Completion
- Keyword completion
- Type suggestions
- Built-in function completion (`print`, `printInt`, `exit`)
- Function and main templates
- Hover documentation

### ▶️ Run Button
- Click the **▶ Run** button above `func main()` to execute your program
- Automatically compiles, assembles, and runs
- Output displayed in the **Algo** output channel

### 🛠️ Build Commands
- **Run Algo Program**: Compile, assemble, and execute
- **Compile Algo Program**: Just compile and assemble

## Requirements

This extension requires the A1M toolchain:
- `compiler/algo-compiler` - Algo compiler
- `assembler/a1m-asm` - A1M assembler
- `emulator/a1m-emu` - A1M emulator

## Extension Settings

Configure paths in VS Code settings:

* `algo.compilerPath`: Path to algo-compiler (default: `compiler/algo-compiler`)
* `algo.assemblerPath`: Path to a1m-asm (default: `assembler/a1m-asm`)
* `algo.emulatorPath`: Path to a1m-emu (default: `emulator/a1m-emu`)

## Usage

1. Open or create a `.algo` file
2. Write your Algo code
3. Click the **▶ Run** button above `func main()` or use Command Palette: `Run Algo Program`
4. View output in the **Algo** output channel

### Example

```algo
func main() -> void {
    print("Hello, Algo!\n");
    let x = 42;
    print("Answer: ");
    print(x);
    print("\n");
}
```

## Icon

The extension uses a distinctive **gold triangle** icon for `.algo` files.

## Release Notes

### 1.0.0

Initial release:
- Syntax highlighting
- Real-time error detection
- Code completion
- Run button integration
- Hover documentation

## License

MIT
