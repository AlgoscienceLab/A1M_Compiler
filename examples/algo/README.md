# Algo Language Examples

This directory contains example programs written in the Algo programming language for the A1M CPU.

## Working Examples

### demo_working.algo
Demonstrates basic arithmetic operations (addition, subtraction, multiplication).
```bash
./compiler/algo-compiler examples/algo/demo_working.algo -o examples/asm/demo_working.asm
./assembler/a1m-asm examples/asm/demo_working.asm -o examples/bin/demo_working.bin
./emulator/a1m-emu examples/bin/demo_working.bin
# Output: 8 2 15
```

## Current Limitations

The compiler currently supports:
- ✅ Variables (let declarations)
- ✅ Arithmetic operators: +, -, *
- ✅ Print function for integers
- ✅ Print function for string literals
- ✅ Return statements
- ✅ Main function

Not yet implemented:
- ❌ Division (DIV instruction issues)
- ❌ Comparison operators (BEQ, SETGT not in assembler)
- ❌ If/else statements (requires comparisons)
- ❌ While/for loops (requires comparisons)
- ❌ User-defined functions with parameters
- ❌ Arrays

## Compilation Steps

1. **Compile Algo to Assembly**:
   ```bash
   ./compiler/algo-compiler input.algo -o output.asm
   ```

2. **Assemble to Binary**:
   ```bash
   ./assembler/a1m-asm output.asm -o output.bin
   ```

3. **Run on Emulator**:
   ```bash
   ./emulator/a1m-emu output.bin
   ```

## Algo Language Syntax

### Variables
```algo
let x: int = 10;
let name: int = 42;
```

### Arithmetic
```algo
let sum: int = a + b;
let diff: int = a - b;
let prod: int = a * b;
```

### Print
```algo
print(42);              // Print integer
print("Hello");         // Print string literal
```

### Functions
```algo
func main() -> int {
    // Your code here
    return 0;
}
```

## Example Program

```algo
func main() -> int {
    let x: int = 10;
    let y: int = 5;
    let result: int = x + y;
    print(result);  // Prints: 15
    return 0;
}
```
