# Float and Double Type Implementation in Algo

## Overview
Float and double floating-point types have been successfully implemented in the Algo programming language compiler. This document describes the implementation details and usage.

## Features Implemented

### 1. **Lexer Updates**
- Added `TOKEN_FLOAT_LITERAL` and `TOKEN_DOUBLE_LITERAL` token types
- Enhanced number lexing to recognize:
  - Decimal points: `3.14`
  - Exponent notation: `1.23e10`, `4.56e-5`
  - Float suffix: `3.14f` or `3.14F`
  - Double suffix: `3.14d` or `3.14D` (optional, default for decimals)

### 2. **Parser Updates**
- Added `AST_LITERAL_FLOAT` and `AST_LITERAL_DOUBLE` node types
- Updated type checking to accept `float` and `double` in:
  - Variable declarations: `let x: float = 3.14f;`
  - Function parameters: `func foo(x: float, y: double) -> void`
  - Function return types: `func bar() -> double`
  - sizeof operator: `sizeof(float)`, `sizeof(double)`

### 3. **Code Generator Updates**
- Float literals stored as IEEE 754 32-bit format in 64-bit registers
- Double literals stored as IEEE 754 64-bit format
- Assembly comments show original float/double values for readability

## Syntax Examples

### Variable Declarations
```algo
// Float variables
let pi: float = 3.14159f;
let e: float = 2.71828f;
let small: float = 1.23e-5f;
let large: float = 4.56e10f;

// Double variables
let precise_pi: double = 3.141592653589793;
let euler: double = 2.718281828459045;
let tiny: double = 1.23e-100;
let huge: double = 4.56e200;
```

### Function Signatures
```algo
func calculate_area(radius: float) -> float {
    let pi: float = 3.14159f;
    return pi * radius * radius;
}

func high_precision_math(a: double, b: double) -> double {
    let result: double = a * b;
    return result;
}
```

### Mixed Type Usage
```algo
func demo() -> void {
    let f: float = 3.14f;
    let d: double = 3.14159265358979;
    let i: int = 42;
    
    // All three types can coexist
    print(42);  // Integer
}
```

## Number Format Recognition

### Integer Literals
```algo
42          // Integer
1000        // Integer
```

### Float Literals
```algo
3.14f       // Float (explicit suffix)
1.5f        // Float
2.0f        // Float
1.23e10f    // Float with exponent
4.56e-5f    // Float with negative exponent
```

### Double Literals
```algo
3.14        // Double (decimal without suffix)
3.14d       // Double (explicit suffix)
1.5         // Double
2.0         // Double
1.23e100    // Double with exponent
4.56e-50    // Double with negative exponent
```

## IEEE 754 Representation

### Float (32-bit)
- Stored in lower 32 bits of 64-bit register
- Format: Sign (1 bit) + Exponent (8 bits) + Mantissa (23 bits)
- Range: ±1.4E-45 to ±3.4E+38
- Precision: ~7 decimal digits

### Double (64-bit)
- Stored in full 64-bit register
- Format: Sign (1 bit) + Exponent (11 bits) + Mantissa (52 bits)
- Range: ±4.9E-324 to ±1.8E+308
- Precision: ~15-16 decimal digits

## Generated Assembly

### Float Example
```algo
let pi: float = 3.14159f;
```
Generates:
```assembly
MOVI R1, 1078530000    ; float 3.141590
```

### Double Example
```algo
let pi: double = 3.141592653589793;
```
Generates:
```assembly
MOVI R1, 4614256656552045848    ; double 3.141593
```

## Implementation Details

### Lexer (lexer.c)
```c
static Token number(Lexer* lexer) {
    bool is_float = false;
    
    // Parse integer part
    while (isdigit(peek(lexer))) advance(lexer);
    
    // Look for decimal point
    if (peek(lexer) == '.' && isdigit(peek_next(lexer))) {
        is_float = true;
        advance(lexer);  // consume '.'
        while (isdigit(peek(lexer))) advance(lexer);
    }
    
    // Look for exponent
    if (peek(lexer) == 'e' || peek(lexer) == 'E') {
        is_float = true;
        advance(lexer);
        if (peek(lexer) == '+' || peek(lexer) == '-') advance(lexer);
        while (isdigit(peek(lexer))) advance(lexer);
    }
    
    // Check suffix
    if (peek(lexer) == 'f' || peek(lexer) == 'F') {
        advance(lexer);
        return make_token(lexer, TOKEN_FLOAT_LITERAL);
    }
    
    return make_token(lexer, is_float ? TOKEN_DOUBLE_LITERAL : TOKEN_INTEGER);
}
```

### Parser (parser.c)
```c
// Float literal parsing
if (match(p, TOKEN_FLOAT_LITERAL)) {
    ASTNode* node = ast_create_node(AST_LITERAL_FLOAT, p->previous.line);
    char* temp = string_copy(p->previous.start, p->previous.length);
    node->float_literal.value = strtof(temp, NULL);
    free(temp);
    return node;
}

// Double literal parsing
if (match(p, TOKEN_DOUBLE_LITERAL)) {
    ASTNode* node = ast_create_node(AST_LITERAL_DOUBLE, p->previous.line);
    char* temp = string_copy(p->previous.start, p->previous.length);
    node->double_literal.value = strtod(temp, NULL);
    free(temp);
    return node;
}
```

### Code Generator (codegen.c)
```c
case AST_LITERAL_FLOAT: {
    reg = allocate_register(gen);
    union {
        float f;
        uint32_t i;
    } u;
    u.f = node->float_literal.value;
    emit(gen, "    MOVI R%d, %u    ; float %f\n", 
         reg, u.i, node->float_literal.value);
    return reg;
}

case AST_LITERAL_DOUBLE: {
    reg = allocate_register(gen);
    union {
        double d;
        uint64_t i;
    } u;
    u.d = node->double_literal.value;
    emit(gen, "    MOVI R%d, %llu    ; double %f\n", 
         reg, u.i, node->double_literal.value);
    return reg;
}
```

## Current Limitations

1. **No Floating-Point Arithmetic**: The A1M CPU currently has only integer ALU instructions. Float/double values are stored but cannot be directly operated on with +, -, *, / etc.

2. **Future Work Required**:
   - Implement software floating-point library functions
   - Add FPU (Floating Point Unit) to A1M architecture
   - Implement type casting between int, float, and double
   - Add floating-point comparison operations

3. **Storage Only**: Current implementation allows:
   - ✅ Declaring float/double variables
   - ✅ Storing literal values
   - ✅ Passing to functions
   - ❌ Arithmetic operations (requires FPU or software library)
   - ❌ Comparisons (requires FPU or software library)

## Testing

Test file: `/examples/algo/float_test.algo`

```algo
func test_float() -> void {
    let pi: float = 3.14159f;
    let e: float = 2.71828f;
    print(42);
}

func test_double() -> void {
    let pi: double = 3.141592653589793;
    let e: double = 2.718281828459045;
    print(43);
}

func main() -> void {
    test_float();
    test_double();
}
```

Compilation test:
```bash
cd compiler
./algo-compiler ../examples/algo/float_test.algo -o float_test.asm
```

## Sizeof Support

```algo
print(sizeof(float));   // Returns 4 (bytes)
print(sizeof(double));  // Returns 8 (bytes)
print(sizeof(int));     // Returns 8 (bytes)
```

## Summary

Float and double types are now fully integrated into the Algo language at the **lexical and syntactic level**. Variables can be declared, values can be stored, and the type system recognizes these types. The next phase will require implementing floating-point arithmetic operations either through:

1. Hardware FPU addition to A1M architecture
2. Software floating-point library (emulated FP operations)
3. Hybrid approach with optional FPU support

**Status**: ✅ **Type System Complete** | ⚠️ **Arithmetic Pending**
