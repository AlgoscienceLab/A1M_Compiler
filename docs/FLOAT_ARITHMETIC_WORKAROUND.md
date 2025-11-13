# Float/Double Arithmetic Limitation and Workaround

## Current Status

### ✅ What Works
- Float and double **type declarations**: `let x: float = 3.14f;`
- Float and double **literal parsing**: `1.5f`, `3.14159`, `1.23e10`
- Float and double **storage**: Values stored as IEEE 754 format in registers
- **Type checking**: Compiler recognizes float/double as valid types

### ❌ What Doesn't Work Yet
- **Arithmetic operations**: `a + b`, `a - b`, `a * b`, `a / b`
- **Comparisons**: `a > b`, `a == b`, etc.
- **Type conversion**: Can't convert between int, float, double

## The Problem

When you write:
```algo
let a: float = 5.5f;
let b: float = 2.2f;
let c: float = a + b;
print(c);
```

The compiler:
1. ✅ Stores `5.5f` as IEEE 754 bits: `1085276160`
2. ✅ Stores `2.2f` as IEEE 754 bits: `1074580685`
3. ❌ **Uses integer ADD instruction**: `1085276160 + 1074580685 = 2159856845`
4. ❌ Prints the integer result: `2159856845` (meaningless as a float)

**Why?** The A1M CPU only has integer ALU instructions. It doesn't have:
- `FADD` (floating-point add)
- `FSUB` (floating-point subtract)
- `FMUL` (floating-point multiply)
- `FDIV` (floating-point divide)

## Workaround: Fixed-Point Arithmetic

Until we implement floating-point support, use **fixed-point arithmetic**:

### Example: Addition
```algo
func main() -> void {
    // Represent 5.5 as 550 (multiply by 100)
    let a: int = 550;  // Represents 5.5
    let b: int = 220;  // Represents 2.2
    
    let sum: int = a + b;  // 770 = 7.7 * 100
    
    // To display: divide by 100 to get integer part
    let integer_part: int = sum / 100;  // 7
    let decimal_part: int = sum % 100;  // 70
    
    print(integer_part);  // 7
    print(46);  // '.'
    print(decimal_part);  // 70
    print(10);  // newline → "7.70"
}
```

### Example: Division
```algo
func divide_floats() -> void {
    let a: int = 550;  // 5.5 * 100
    let b: int = 220;  // 2.2 * 100
    
    // For accurate division, scale up numerator
    let result: int = (a * 100) / b;  // (550 * 100) / 220 = 250
    
    // Result: 250 represents 2.50
    print(result / 100);  // Integer part: 2
    print(46);  // '.'
    print(result % 100);  // Decimal: 50
    print(10);  // → "2.50"
}
```

### Scaling Factors

| Precision | Scale Factor | Range | Example |
|-----------|--------------|-------|---------|
| 0.1 | 10 | ±214748364.8 | 55 = 5.5 |
| 0.01 | 100 | ±21474836.48 | 550 = 5.50 |
| 0.001 | 1000 | ±2147483.648 | 5500 = 5.500 |
| 0.0001 | 10000 | ±214748.3648 | 55000 = 5.5000 |

## Solutions (Future Implementation)

### Option 1: Software Floating-Point Library

Implement IEEE 754 operations in software:

```c
// Pseudo-code for float addition
int float_add(int a_bits, int b_bits) {
    // 1. Extract sign, exponent, mantissa from both
    // 2. Align mantissas based on exponents
    // 3. Add/subtract mantissas
    // 4. Normalize result
    // 5. Pack back into IEEE 754 format
    return result_bits;
}
```

**Pros**: Works on current hardware
**Cons**: Very slow (100-1000x slower than hardware)

### Option 2: Hardware FPU

Add floating-point instructions to A1M architecture:

```verilog
// New ALU operations
FADD R1, R2, R3   // R1 = float(R2) + float(R3)
FSUB R1, R2, R3   // R1 = float(R2) - float(R3)
FMUL R1, R2, R3   // R1 = float(R2) * float(R3)
FDIV R1, R2, R3   // R1 = float(R2) / float(R3)
FCMP R2, R3       // Compare floats, set flags
```

**Pros**: Fast, native support
**Cons**: Requires hardware redesign, more gates/complexity

### Option 3: Hybrid Approach

Use integer instructions creatively:

```algo
// Fast approximate float multiply (for small ranges)
func approx_mul(a: int, b: int) -> int {
    // Assuming a and b are scaled by 100
    // Result scaled by 100
    return (a * b) / 100;
}
```

## Current Recommendations

### For Now: Use Integers with Scaling

```algo
// ❌ DON'T (doesn't work correctly)
let x: float = 3.14f;
let y: float = 2.0f;
let z: float = x * y;

// ✅ DO (works correctly)
let x: int = 314;  // 3.14 * 100
let y: int = 200;  // 2.00 * 100
let z: int = (x * y) / 100;  // (314 * 200) / 100 = 628 = 6.28 * 100
```

### Future: Wait for FPU or Soft-Float Library

Once implemented, your original code will work:

```algo
// Will work after FPU implementation
let a: float = 5.5f;
let b: float = 2.2f;
let c: float = a + b;  // Will correctly compute 7.7
print(c);  // Will print 7.7 (or IEEE bits if needed)
```

## Testing Your Example

Your code:
```algo
let a: float = 5.5;
let b: float = 2.2;
let c: float = a + b;
print(c);  // Currently prints garbage
```

**Why it fails**: 
- `5.5` stored as `0x40B00000` (hex) = `1085276160` (decimal)
- `2.2` stored as `0x400CCCCD` (hex) = `1074580685` (decimal)  
- Integer ADD: `1085276160 + 1074580685 = 2159856845`
- This is **not** the IEEE 754 representation of `7.7`

**Correct approach (until FPU)**:
```algo
func main() -> void {
    let a: int = 550;    // 5.5 * 100
    let b: int = 220;    // 2.2 * 100
    let c: int = a + b;  // 770
    
    // Print as "7.70"
    print(c / 100);   // 7
    print(46);        // '.'
    print(c % 100);   // 70
    print(10);        // newline
}
```

## Status Summary

| Feature | Status | Notes |
|---------|--------|-------|
| Float type parsing | ✅ Complete | Can declare `float` variables |
| Double type parsing | ✅ Complete | Can declare `double` variables |
| Float literals | ✅ Complete | `3.14f`, `1.5e10f` |
| Double literals | ✅ Complete | `3.14`, `1.5e10` |
| Storage (IEEE 754) | ✅ Complete | Values stored correctly |
| Arithmetic (+,-,*,/) | ❌ Not working | Uses integer ALU |
| Comparisons | ❌ Not working | Uses integer comparison |
| Type casting | ❌ Not implemented | Can't convert types |
| FPU instructions | ❌ Not implemented | Hardware limitation |
| Soft-float library | ❌ Not implemented | Planned for future |

## Next Steps

1. **Short term**: Use fixed-point integer arithmetic (documented above)
2. **Medium term**: Implement software floating-point library
3. **Long term**: Design and implement FPU in A1M architecture

For questions or to contribute to FPU implementation, see `/docs/FLOAT_DOUBLE_IMPLEMENTATION.md`
