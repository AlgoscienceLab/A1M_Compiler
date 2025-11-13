# Float and Double Implementation Status

## Overview
This document describes the current state of floating-point (float and double) support in the Algo compiler for the A1M CPU architecture.

## Completed Features ✅

### 1. Lexer Support
- **Float Literals**: Parses decimal numbers with `.` (e.g., `3.14`, `2.5`)
- **Scientific Notation**: Supports exponent notation (e.g., `1.23e10`, `4.56e-5`)
- **Type Suffixes**: 
  - `f` or `F` suffix for float (e.g., `3.14f`)
  - `d` or `D` suffix for double (e.g., `3.14d`)
  - Default: decimals without suffix are treated as `double`

### 2. Parser Support
- **Type Declarations**: Variables can be declared as `float` or `double`
  ```algo
  let x:float = 3.14f;
  let y:double = 2.718;
  ```
- **Function Parameters**: Functions can accept float/double parameters
  ```algo
  func calculate(a:float, b:double) -> float { ... }
  ```
- **Return Types**: Functions can return float/double values
- **sizeof Operator**: `sizeof(float)` returns 4, `sizeof(double)` returns 8

### 3. Code Generator Support
- **IEEE 754 Storage**: Correctly converts float/double literals to IEEE 754 format
  - Float: 32-bit IEEE 754 single precision
  - Double: 64-bit IEEE 754 double precision
- **Type Tracking**: Symbol table now tracks variable types
- **Library Functions**: Generates floating-point arithmetic library functions:
  - `__float_add`: Addition
  - `__float_sub`: Subtraction
  - `__float_mul`: Multiplication
  - `__float_div`: Division

### 4. Type-Aware Code Generation
- Detects when operands are float/double types
- Generates function calls to FP library instead of using integer ALU
- Properly passes arguments in R1, R2 and receives result in R1

## Partially Implemented ⚠️

### Floating-Point Arithmetic
The code generator now:
1. ✅ Detects float/double types in expressions
2. ✅ Generates calls to software FP library functions
3. ⚠️ Library functions are **stubbed** - they currently just do integer operations

**Current Behavior**:
```algo
let a:float = 5.5f;
let b:float = 2.2f;
let c:float = a + b;  // Calls __float_add, but result is still incorrect
```

The generated assembly will call `__float_add`, but the function itself still uses:
```assembly
ADD R1, R1, R2  ; Integer addition on IEEE 754 bit patterns (WRONG)
```

**Why It's Wrong**:
- `5.5f` → IEEE 754 = `0x40B00000` (1084227584 as integer)
- `2.2f` → IEEE 754 = `0x400CCCCD` (1074399437 as integer)
- Integer ADD: `1084227584 + 1074399437 = 2158627021` ❌
- Correct IEEE 754 result for `5.5 + 2.2` should be `7.7` → `0x40F66666`

## Not Yet Implemented ❌

### 1. Full IEEE 754 Arithmetic
The library functions need proper implementations that:
- Extract sign, exponent, and mantissa from operands
- Align exponents for addition/subtraction
- Add/subtract mantissas
- Normalize results
- Handle special cases (NaN, Infinity, denormals, rounding)

### 2. Float-Aware Print Function
Currently `print()` treats all values as integers. Need:
```algo
print(3.14f);  // Should print "3.14", currently prints as integer
```

### 3. Float Comparison Operators
Comparison operators (`<`, `>`, `<=`, `>=`, `==`, `!=`) need float-aware implementations.

### 4. Type Casting
No implicit or explicit casting between int, float, double yet:
```algo
let x:int = 5;
let y:float = x;  // Not supported
```

## Implementation Approaches

### Option 1: Software Floating-Point Library (Recommended for Compatibility)
Implement full IEEE 754 arithmetic in assembly:
- **Pros**: Works on any CPU, portable
- **Cons**: Slow (~10-100x slower than hardware FP), complex (~1000s of lines)
- **Reference**: Use GCC's libgcc `__addsf3`, `__subsf3`, etc. as reference

### Option 2: Hardware FPU Instructions
Add floating-point instructions to the A1M CPU:
- **Pros**: Fast, simple compiler code
- **Cons**: Requires Verilog changes, FPGA resynthesis, not backward compatible
- **Instructions needed**: FADD, FSUB, FMUL, FDIV, FCMP, FMOV

### Option 3: Scaled Fixed-Point (Quick Workaround)
Use scaled integers (multiply by 10000, do int math, divide):
- **Pros**: Simple, works now
- **Cons**: Limited precision, not IEEE 754 compatible, loses range

### Option 4: External Library Linking
Link with existing FP library (e.g., compiler-rt, libgcc):
- **Pros**: Full IEEE 754 compliance, well-tested
- **Cons**: Requires linker support, binary compatibility

## Current Recommendation

For immediate functionality:
1. Implement software FP library functions in `__float_add`, etc.
2. Use simplified algorithm (ignore rounding modes, special values)
3. Handle basic cases: normal numbers, zero, sign

For production:
1. Add hardware FPU to A1M architecture
2. Or link with standard FP library (libgcc/compiler-rt)

## Testing

### Test Cases Needed
```algo
// Basic arithmetic
let sum = 5.5f + 2.2f;        // Should be 7.7
let diff = 5.5f - 2.2f;       // Should be 3.3
let prod = 5.5f * 2.2f;       // Should be 12.1
let quot = 5.5f / 2.2f;       // Should be 2.5

// Edge cases
let zero = 0.0f;
let neg = -3.14f;
let small = 1.0e-10;
let large = 1.0e10;

// Mixed operations
let mixed = 5 + 2.5f;         // Requires type promotion
```

## VS Code Extension Support
✅ Already implemented:
- Syntax highlighting for `float` and `double` keywords
- Autocomplete suggestions for `float` and `double` types
- Version 0.2.0 includes full float/double support

## Conclusion

The infrastructure for floating-point support is now in place:
- ✅ Lexer can parse float/double literals
- ✅ Parser understands float/double types
- ✅ Code generator tracks types and calls FP library
- ⚠️ Library functions are stubbed (still use integer operations)
- ❌ Full IEEE 754 arithmetic not yet implemented

**Next steps**: Implement proper IEEE 754 arithmetic in the library functions, or add hardware FPU support to the A1M CPU.

---

**Author**: Algo Compiler Development Team  
**Date**: November 13, 2025  
**Version**: 0.2.0
