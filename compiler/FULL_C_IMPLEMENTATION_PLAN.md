# Full C Implementation Plan for Algo Compiler

## Phase 1: Control Flow (PRIORITY - IN PROGRESS)
### Features to Implement:
1. ✅ if/else statements with proper branching
2. ✅ while loops  
3. ✅ for loops
4. ✅ do-while loops
5. ✅ break/continue statements
6. ✅ Comparison operators: ==, !=, <, <=, >, >=
7. ✅ Logical operators: &&, ||, !

### Assembly Instructions Available:
- CMP Rd, Rs - Compare and set flags
- JZ label - Jump if zero
- JNZ label - Jump if not zero
- JC label - Jump if carry (for unsigned <)
- JNC label - Jump if not carry
- JN label - Jump if negative (for signed <)
- JNN label - Jump if not negative
- JMP label - Unconditional jump

### Implementation Strategy:
**Comparison Operators:**
```c
// a < b  →  CMP Ra, Rb; JN .true_label
// a <= b →  CMP Ra, Rb; JNN .false_label  
// a > b  →  CMP Rb, Ra; JN .true_label
// a >= b →  CMP Rb, Ra; JNN .false_label
// a == b →  SUB Rtemp, Ra, Rb; JZ .true_label
// a != b →  SUB Rtemp, Ra, Rb; JNZ .true_label
```

**If Statement:**
```asm
; if (condition) { then } else { else }
    <evaluate condition>
    JZ .else_label        ; if false, jump to else
.then_label:
    <then statements>
    JMP .end_label
.else_label:
    <else statements>  
.end_label:
```

**While Loop:**
```asm
; while (condition) { body }
.loop_start:
    <evaluate condition>
    JZ .loop_end          ; if false, exit loop
    <body statements>
    JMP .loop_start
.loop_end:
```

**For Loop:**
```asm
; for (init; condition; increment) { body }
    <init statement>
.loop_start:
    <evaluate condition>
    JZ .loop_end
    <body statements>
.loop_continue:
    <increment statement>
    JMP .loop_start
.loop_end:
```

## Phase 2: Pointers and Arrays
### Features:
1. Pointer types: `int*`, `char*`, etc.
2. Address-of operator: `&variable`
3. Dereference operator: `*pointer`
4. Pointer arithmetic: `ptr + offset`
5. Array declarations: `int arr[10];`
6. Array indexing: `arr[i]`
7. Multi-dimensional arrays

### Assembly Instructions:
- LOAD Rd, [Rs + offset] - Load from memory
- STORE Rs, [Rd + offset] - Store to memory
- LOADB/LOADH/LOADW - Load byte/half/word
- STOREB/STOREH/STOREW - Store byte/half/word

### Memory Model:
```
0x0000_0000_0000_1000: .text section (code)
0x0000_0000_0001_0000: .data section (globals)
0x0000_0000_0002_0000: .bss section (uninitialized)
0x0000_0000_1000_0000: heap (malloc)
0x7FFF_FFFF_FFF0_0000: stack (grows down)
```

### Stack Frame Layout:
```
[higher addresses]
    saved R31 (return address)
    saved registers
    local variables
    function parameters
R3 (SP) →  [current stack top]
[lower addresses]
```

## Phase 3: Type System
### Basic Types:
- `char` (8-bit)
- `short` (16-bit)
- `int` (32-bit)
- `long` (64-bit)
- `unsigned` variants of all
- `float` / `double` (software emulation)
- `void`

### Type Qualifiers:
- `const` - immutable
- `volatile` - no optimization
- `static` - file scope
- `extern` - external linkage

### Type Operations:
- `sizeof(type)` - compile-time size
- `(type)expr` - type casting
- Implicit conversions (widening)
- Explicit conversions (narrowing)

## Phase 4: Structs and Unions
### Features:
```c
struct Point {
    int x;
    int y;
};

struct Point p;
p.x = 10;
p.y = 20;

struct Point *ptr = &p;
ptr->x = 30;  // equivalent to (*ptr).x = 30
```

### Implementation:
- Struct layout: sequential field offsets
- Member access: base_address + offset
- Arrow operator: dereference + member access
- Nested structs: recursive offset calculation
- Union: all members share same offset 0

## Phase 5: Advanced Operators
### Arithmetic:
- `/` - division (DIV instruction)
- `%` - modulo (MOD instruction)
- `++` - increment (pre/post)
- `--` - decrement (pre/post)

### Assignment:
- `+=`, `-=`, `*=`, `/=`, `%=`
- `&=`, `|=`, `^=`  
- `<<=`, `>>=`

### Bitwise:
- `&` - AND
- `|` - OR
- `^` - XOR
- `~` - NOT (complement)
- `<<` - left shift
- `>>` - right shift (arithmetic)

### Ternary:
- `condition ? true_expr : false_expr`

## Phase 6: Preprocessor
### Directives:
```c
#include <stdio.h>      // system header
#include "myfile.h"     // local header
#define PI 3.14159      // simple macro
#define MAX(a,b) ((a)>(b)?(a):(b))  // function macro
#ifdef DEBUG            // conditional compilation
#ifndef INCLUDED        // include guards
#endif
#undef SYMBOL           // undefine
```

### Implementation:
- Separate preprocessing phase before lexing
- Token replacement for macros
- File inclusion (recursive)
- Conditional compilation (skip tokens)

## Phase 7: Standard Library
### stdio.h:
```c
int printf(const char *format, ...);
int scanf(const char *format, ...);
int putchar(int c);
int getchar(void);
int puts(const char *s);
char *gets(char *s);  // deprecated but common
```

### stdlib.h:
```c
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
int atoi(const char *str);
void exit(int status);
```

### string.h:
```c
size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
```

### math.h (software floating point):
```c
double sin(double x);
double cos(double x);
double sqrt(double x);
double pow(double base, double exp);
```

## Phase 8: Memory Management
### Heap Allocator:
- Free list implementation
- First-fit / best-fit strategy
- Coalescing adjacent free blocks
- Metadata headers for each block

### Stack Management:
- Function prologue: save R31, allocate frame
- Function epilogue: deallocate frame, restore R31
- Register saving convention (caller/callee-saved)

### Calling Convention:
```
Parameters: R4-R10 (first 7), then stack
Return: R2
Caller-saved: R4-R15 (must save before call)
Callee-saved: R16-R30 (must save in function)
```

## Phase 9: Optimizations
### Register Allocation:
- Liveness analysis
- Graph coloring
- Register spilling to stack
- Copy propagation

### Code Optimization:
- Constant folding
- Dead code elimination
- Common subexpression elimination
- Loop optimization (hoisting, unrolling)

### Peephole Optimization:
```asm
; Before:
MOVI R4, 0
ADD R4, R4, R5
; After:
MOVI R4, 0
ADD R4, R0, R5  ; or just: MOV R4, R5
```

## Phase 10: Error Handling and Diagnostics
### Compile-time Errors:
- Type checking
- Undeclared variables
- Multiple definitions
- Type mismatches
- Invalid operations

### Warnings:
- Unused variables
- Implicit conversions
- Missing return statements
- Unreachable code

### Runtime Support:
- NULL pointer detection
- Array bounds checking (debug mode)
- Stack overflow detection
- Division by zero

## Implementation Order:
1. **Week 1**: Control flow (if/while/for) + comparison operators
2. **Week 2**: Pointers + arrays + memory ops
3. **Week 3**: Type system + structs
4. **Week 4**: Remaining operators + preprocessor basics
5. **Week 5**: Standard library (stdio, stdlib, string)
6. **Week 6**: Memory management + calling convention
7. **Week 7**: Optimizations
8. **Week 8**: Error handling + testing + documentation

## Testing Strategy:
- Unit tests for each feature
- Integration tests for combinations
- Edge cases and error conditions
- Performance benchmarks
- Comparison with GCC output

## Success Criteria:
- ✅ Can compile and run all C89 standard programs
- ✅ Passes compliance test suite
- ✅ Generates correct and efficient assembly
- ✅ Good error messages
- ✅ Complete documentation

---
**Status**: Phase 1 in progress  
**Target**: Full C89 compliance within 8 weeks
