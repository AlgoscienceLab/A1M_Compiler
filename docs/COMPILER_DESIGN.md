# Algo Compiler Design Documentation

## Architecture Overview

The Algo compiler is a multi-stage compiler that translates Algo source code into A1M assembly language, which is then assembled into executable binary code.

```
┌─────────────────────────────────────────────────────────────┐
│                    COMPILATION PIPELINE                     │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  .algo Source  →  Lexer  →  Parser  →  Code Gen  →  .asm    │
│                     ↓         ↓           ↓                 │
│                  Tokens     AST       Assembly              │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Components

### 1. Lexer (Tokenizer)

**Purpose:** Break source code into tokens

**Input:** Raw source code string
**Output:** Stream of tokens

**Token Types:**
```c
typedef enum {
    TOKEN_EOF,
    TOKEN_ERROR,
    
    // Literals
    TOKEN_INTEGER,
    TOKEN_STRING,
    TOKEN_TRUE,
    TOKEN_FALSE,
    
    // Identifiers and keywords
    TOKEN_IDENTIFIER,
    TOKEN_FUNC,
    TOKEN_RETURN,
    TOKEN_LET,
    TOKEN_CONST,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    
    // Types
    TOKEN_INT,
    TOKEN_STRING_TYPE,
    TOKEN_BOOL,
    TOKEN_VOID,
    
    // Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_BANG,
    TOKEN_BANG_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_AMPERSAND,
    TOKEN_AMPERSAND_AMPERSAND,
    TOKEN_PIPE,
    TOKEN_PIPE_PIPE,
    TOKEN_CARET,
    TOKEN_TILDE,
    TOKEN_LEFT_SHIFT,
    TOKEN_RIGHT_SHIFT,
    
    // Punctuation
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,
    TOKEN_COLON,
    TOKEN_ARROW,
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    int length;
    int line;
} Token;
```

**Example:**
```algo
let x = 42;
```
Produces tokens:
```
TOKEN_LET, TOKEN_IDENTIFIER("x"), TOKEN_EQUAL, TOKEN_INTEGER("42"), TOKEN_SEMICOLON
```

---

### 2. Parser

**Purpose:** Build Abstract Syntax Tree (AST) from tokens

**Input:** Token stream
**Output:** AST

**AST Node Types:**
```c
typedef enum {
    AST_PROGRAM,
    AST_FUNCTION,
    AST_BLOCK,
    AST_DECLARATION,
    AST_ASSIGNMENT,
    AST_IF_STMT,
    AST_WHILE_STMT,
    AST_FOR_STMT,
    AST_RETURN_STMT,
    AST_EXPRESSION_STMT,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_CALL,
    AST_LITERAL,
    AST_IDENTIFIER,
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    int line;
    
    union {
        // Literals
        struct { int64_t value; } integer;
        struct { char* value; } string;
        
        // Identifier
        struct { char* name; } identifier;
        
        // Binary operation
        struct {
            struct ASTNode* left;
            struct ASTNode* right;
            TokenType op;
        } binary;
        
        // Unary operation
        struct {
            struct ASTNode* operand;
            TokenType op;
        } unary;
        
        // Function call
        struct {
            char* name;
            struct ASTNode** args;
            int arg_count;
        } call;
        
        // Variable declaration
        struct {
            char* name;
            char* type;
            struct ASTNode* initializer;
            bool is_const;
        } declaration;
        
        // Assignment
        struct {
            char* name;
            struct ASTNode* value;
        } assignment;
        
        // If statement
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_branch;
            struct ASTNode* else_branch;
        } if_stmt;
        
        // While loop
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } while_stmt;
        
        // For loop
        struct {
            struct ASTNode* init;
            struct ASTNode* condition;
            struct ASTNode* increment;
            struct ASTNode* body;
        } for_stmt;
        
        // Return statement
        struct {
            struct ASTNode* value;
        } return_stmt;
        
        // Function
        struct {
            char* name;
            char** param_names;
            char** param_types;
            int param_count;
            char* return_type;
            struct ASTNode* body;
        } function;
        
        // Block
        struct {
            struct ASTNode** statements;
            int statement_count;
        } block;
        
        // Program
        struct {
            struct ASTNode** functions;
            int function_count;
        } program;
    };
} ASTNode;
```

**Parsing Algorithm:**
- Recursive Descent Parser
- Operator Precedence Climbing for expressions
- Left-to-right, top-down parsing

---

### 3. Code Generator

**Purpose:** Generate A1M assembly from AST

**Input:** AST
**Output:** A1M assembly code

**Register Allocation:**
```
R0:  Always zero (hardware)
R1:  Return value / syscall argument
R2:  Temporary / function arg 1
R3:  Temporary / function arg 2
R4:  Temporary / function arg 3
R5:  Temporary / function arg 4
R6-R10: Local variables
R11-R20: Temporary registers
R21-R30: Saved registers
R31: Frame pointer
SP:  Stack pointer (special register)
```

**Code Generation Strategies:**

#### Variables
```algo
let x = 42;
```
Generates:
```asm
MOVI R6, 42    ; R6 = variable 'x'
```

#### Arithmetic
```algo
let c = a + b;
```
Generates:
```asm
; Assume a in R6, b in R7
ADD R8, R6, R7    ; c = a + b
```

#### Function Calls
```algo
result = add(10, 20);
```
Generates:
```asm
; Save context
PUSH R1
PUSH R2

; Load arguments
MOVI R2, 10
MOVI R3, 20

; Call function
CALL add

; Get return value
MOV R10, R1

; Restore context
POP R2
POP R1
```

#### If Statements
```algo
if (x > 10) {
    print("large");
} else {
    print("small");
}
```
Generates:
```asm
    MOVI R1, 10
    CMP R6, R1         ; Compare x with 10
    JLE .else_branch
.then_branch:
    ; print("large")
    MOVI R1, str_large
    SYSCALL 0x04
    JMP .end_if
.else_branch:
    ; print("small")
    MOVI R1, str_small
    SYSCALL 0x04
.end_if:
```

#### While Loops
```algo
while (i < 10) {
    i = i + 1;
}
```
Generates:
```asm
.loop_start:
    MOVI R1, 10
    CMP R6, R1         ; Compare i with 10
    JGE .loop_end
    
    ADDI R6, R6, 1     ; i = i + 1
    JMP .loop_start
.loop_end:
```

---

## Symbol Table

**Purpose:** Track variables, functions, and their properties

```c
typedef struct {
    char* name;
    char* type;
    int register_num;  // Which register holds this variable
    int offset;        // Stack offset if spilled
    bool is_const;
    bool is_global;
} Symbol;

typedef struct {
    Symbol* symbols;
    int count;
    int capacity;
} SymbolTable;
```

**Scoping:**
- Global scope for functions
- Local scope for variables within functions
- Block scope for variables in { }

---

## Type System

**Type Checking Rules:**

1. **Assignment:** RHS type must match LHS type
```algo
let x: int = 42;     // ✓ Valid
let y: int = "hi";   // ✗ Error: type mismatch
```

2. **Arithmetic:** Both operands must be int
```algo
let z = 10 + 20;     // ✓ Valid
let w = 10 + "hi";   // ✗ Error: invalid operands
```

3. **Comparison:** Both operands must be same type
```algo
if (x > 10) { }      // ✓ Valid
if (x > "hi") { }    // ✗ Error: type mismatch
```

4. **Function calls:** Argument types must match parameters
```algo
func add(a: int, b: int) -> int { return a + b; }
add(10, 20);         // ✓ Valid
add(10, "hi");       // ✗ Error: argument type mismatch
```

---

## Optimization Opportunities

### Constant Folding
```algo
let x = 10 + 20;     // Compile-time: x = 30
```
Generates:
```asm
MOVI R6, 30          ; Direct constant instead of ADD
```

### Dead Code Elimination
```algo
if (false) {
    // This code is never executed
}
```
Generates:
```asm
; Nothing - eliminated at compile time
```

### Register Allocation
- Use registers instead of memory when possible
- Spill to stack only when registers exhausted

### Peephole Optimization
```asm
MOVI R1, 0
ADD R2, R1, R3       ; Optimize to: MOV R2, R3
```

---

## Error Handling

### Lexical Errors
```
Error at line 5: Unterminated string
Error at line 12: Invalid character '@'
```

### Syntax Errors
```
Error at line 3: Expected ';' after statement
Error at line 8: Unexpected token 'else' without matching 'if'
```

### Semantic Errors
```
Error at line 10: Undefined variable 'x'
Error at line 15: Type mismatch: cannot assign string to int
Error at line 20: Function 'foo' expects 2 arguments, got 3
```

---

## Standard Library Implementation

### print() Function
```asm
; print(value) implementation
print:
    ; Check if integer or string
    ; For integer:
    SYSCALL 0x01       ; print_int
    RET
    
    ; For string:
    SYSCALL 0x04       ; print_string
    RET
```

### input() Function
```asm
input:
    SYSCALL 0x03       ; read_int
    RET                ; Result in R1
```

---

## Memory Layout

```
┌─────────────────────────┐ 0x000000
│    Reserved (4KB)       │
├─────────────────────────┤ 0x001000
│    Code Section         │ ← Program instructions
│    (.text)              │
├─────────────────────────┤ 0x008000
│    Data Section         │ ← Global variables, strings
│    (.data)              │
├─────────────────────────┤ 0x100000
│    Heap                 │ ← Dynamic allocation (future)
│    (grows upward)       │
│         ↓               │
│                         │
│         ↑               │
│    Stack                │ ← Local variables, call frames
│    (grows downward)     │
└─────────────────────────┘ 0xFFFFFF (16MB)
```

---

## Example Compilation

### Source Code
```algo
func add(a: int, b: int) -> int {
    return a + b;
}

func main() -> int {
    let result = add(10, 20);
    print(result);
    return 0;
}
```

### Generated Assembly
```asm
; Generated from Algo source
; A1M Assembly Code

.text
main:
    ; let result = add(10, 20)
    PUSH R1
    PUSH R2
    PUSH R3
    
    MOVI R2, 10
    MOVI R3, 20
    CALL add
    MOV R6, R1          ; result = return value
    
    POP R3
    POP R2
    POP R1
    
    ; print(result)
    MOV R1, R6
    SYSCALL 0x01        ; print_int
    
    ; return 0
    MOVI R1, 0
    SYSCALL 0x00
    HALT

add:
    ; a in R2, b in R3
    ADD R1, R2, R3      ; return a + b
    RET
```

---

## Compiler Phases

### Phase 1: Initialization
1. Open source file
2. Read entire file into memory
3. Initialize lexer, parser, code generator

### Phase 2: Lexical Analysis
1. Scan source code character by character
2. Identify tokens
3. Build token stream

### Phase 3: Syntax Analysis
1. Parse token stream
2. Build AST
3. Check for syntax errors

### Phase 4: Semantic Analysis
1. Build symbol table
2. Type checking
3. Scope resolution
4. Check for semantic errors

### Phase 5: Code Generation
1. Traverse AST
2. Allocate registers
3. Generate assembly instructions
4. Optimize code

### Phase 6: Output
1. Write assembly to .asm file
2. Report errors if any
3. Exit with status code

---

## Future Enhancements

1. **Optimizer Pass**
   - Constant folding
   - Dead code elimination
   - Common subexpression elimination
   - Loop unrolling

2. **Advanced Features**
   - Array support
   - Structure types
   - Pointer arithmetic
   - Function pointers

3. **Better Error Messages**
   - Show source code context
   - Suggest fixes
   - Warning levels

4. **Debugger Support**
   - Generate debug symbols
   - Line number mapping
   - Variable inspection

---

## Building the Compiler

```bash
cd compiler
make clean
make
./algo-compiler source.algo output.asm
```

## Testing

```bash
cd compiler/tests
./run_tests.sh
```

---

## References

- Dragon Book: "Compilers: Principles, Techniques, and Tools"
- A1M CPU Architecture Specification
- RISC-V ISA Specification
- Crafting Interpreters by Robert Nystrom

---

Copyright (c) 2025 A1M CPU Project
