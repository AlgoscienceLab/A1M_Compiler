# Algo Language Specification v1.0

## Overview
Algo is a statically-typed, imperative programming language designed for the A1M 64-bit CPU architecture. It features C-like syntax with modern language constructs.

## Table of Contents
1. [Lexical Structure](#lexical-structure)
2. [Data Types](#data-types)
3. [Variables](#variables)
4. [Operators](#operators)
5. [Control Flow](#control-flow)
6. [Functions](#functions)
7. [Standard Library](#standard-library)
8. [Examples](#examples)

---

## Lexical Structure

### Comments
```algo
// Single-line comment

/*
 * Multi-line comment
 * Can span multiple lines
 */
```

### Keywords
```
func, return, let, const, if, else, while, for, break, continue,
int, string, bool, true, false, void
```

### Identifiers
- Start with letter or underscore
- Can contain letters, digits, underscores
- Case-sensitive
- Examples: `myVar`, `_temp`, `count1`

### Literals
```algo
42          // Integer literal
-17         // Negative integer
0x2A        // Hexadecimal literal
"Hello"     // String literal
'A'         // Character literal
true        // Boolean literal
false       // Boolean literal
```

### String Escape Sequences
String literals support the following escape sequences:
```algo
"\n"        // Newline (ASCII 10)
"\t"        // Tab (ASCII 9)
"\r"        // Carriage return (ASCII 13)
"\\"        // Backslash
"\""        // Double quote
"\0"        // Null character
```

Example usage:
```algo
print("Line 1\nLine 2");     // Prints on two lines
print("Name:\tJohn");         // Tab-separated output
print("He said \"Hello\"");   // Quotes in string
```

---

## Data Types

### Primitive Types
| Type | Size | Range | Description |
|------|------|-------|-------------|
| `int` | 64-bit | -2^63 to 2^63-1 | Signed integer |
| `bool` | 1-bit | true/false | Boolean value |
| `string` | Variable | N/A | UTF-8 string |
| `void` | 0 | N/A | No return value |

### Type Declarations
```algo
let age: int = 25;
let name: string = "Alice";
let isActive: bool = true;
const PI: int = 314;  // Fixed-point representation
```

### Type Inference
```algo
let x = 42;           // Inferred as int
let message = "Hi";   // Inferred as string
let flag = true;      // Inferred as bool
```

---

## Variables

### Declaration
```algo
let variableName: type = value;
let x: int = 10;
let y = 20;  // Type inferred
```

### Constants
```algo
const MAX_SIZE: int = 100;
const APP_NAME: string = "MyApp";
```

### Assignment
```algo
x = 15;
y = x + 5;
```

---

## Operators

### Arithmetic Operators
| Operator | Description | Example |
|----------|-------------|---------|
| `+` | Addition | `a + b` |
| `-` | Subtraction | `a - b` |
| `*` | Multiplication | `a * b` |
| `/` | Division | `a / b` |
| `%` | Modulus | `a % b` |
| `-` | Unary minus | `-a` |

### Comparison Operators
| Operator | Description | Example |
|----------|-------------|---------|
| `==` | Equal to | `a == b` |
| `!=` | Not equal to | `a != b` |
| `<` | Less than | `a < b` |
| `<=` | Less than or equal | `a <= b` |
| `>` | Greater than | `a > b` |
| `>=` | Greater than or equal | `a >= b` |

### Logical Operators
| Operator | Description | Example |
|----------|-------------|---------|
| `&&` | Logical AND | `a && b` |
| `||` | Logical OR | `a || b` |
| `!` | Logical NOT | `!a` |

### Bitwise Operators
| Operator | Description | Example |
|----------|-------------|---------|
| `&` | Bitwise AND | `a & b` |
| `|` | Bitwise OR | `a | b` |
| `^` | Bitwise XOR | `a ^ b` |
| `<<` | Left shift | `a << 2` |
| `>>` | Right shift | `a >> 2` |
| `~` | Bitwise NOT | `~a` |

### Assignment Operators
```algo
=    +=    -=    *=    /=    %=
&=   |=    ^=    <<=   >>=
```

---

## Control Flow

### If Statement
```algo
if (condition) {
    // code
}

if (x > 10) {
    print("x is large");
} else if (x > 5) {
    print("x is medium");
} else {
    print("x is small");
}
```

### While Loop
```algo
while (condition) {
    // code
}

let i = 0;
while (i < 10) {
    print(i);
    i = i + 1;
}
```

### For Loop
```algo
for (init; condition; increment) {
    // code
}

for (let i = 0; i < 10; i = i + 1) {
    print(i);
}
```

### Break and Continue
```algo
while (true) {
    if (condition1) {
        break;     // Exit loop
    }
    if (condition2) {
        continue;  // Skip to next iteration
    }
}
```

---

## Functions

### Function Definition
```algo
func functionName(param1: type1, param2: type2) -> returnType {
    // function body
    return value;
}
```

### Examples
```algo
// Function with return value
func add(a: int, b: int) -> int {
    return a + b;
}

// Function without return value
func printMessage(msg: string) -> void {
    print(msg);
}

// Function without parameters
func getAnswer() -> int {
    return 42;
}
```

### Function Calls
```algo
let result = add(10, 20);
printMessage("Hello, World!");
let answer = getAnswer();
```

### Main Function
Every program must have a `main` function:
```algo
func main() -> int {
    // program code
    return 0;
}
```

---

## Standard Library

### I/O Functions

#### print
```algo
print(value);           // Print any value
print("Hello");         // Print string
print(42);              // Print integer
print(x);               // Print variable
```

#### input
```algo
let x = input();        // Read integer from stdin
let name = input_str(); // Read string from stdin
```

### Math Functions

```algo
let abs_val = abs(-5);           // Absolute value → 5
let min_val = min(3, 7);         // Minimum → 3
let max_val = max(3, 7);         // Maximum → 7
let pow_val = pow(2, 10);        // Power → 1024
```

### String Functions

```algo
let len = strlen("Hello");       // String length → 5
let upper = toupper("hello");    // To uppercase → "HELLO"
let lower = tolower("HELLO");    // To lowercase → "hello"
```

### Utility Functions

```algo
exit(0);                         // Exit program with code
sleep(1000);                     // Sleep for milliseconds
```

---

## Examples

### Hello World
```algo
func main() -> int {
    print("Hello, World!");
    return 0;
}
```

### Variables and Arithmetic
```algo
func main() -> int {
    let a = 10;
    let b = 20;
    let sum = a + b;
    let product = a * b;
    
    print("Sum: ");
    print(sum);
    print("Product: ");
    print(product);
    
    return 0;
}
```

### Conditionals
```algo
func main() -> int {
    let age = 18;
    
    if (age >= 18) {
        print("Adult");
    } else {
        print("Minor");
    }
    
    return 0;
}
```

### Loops
```algo
func main() -> int {
    // Print numbers 1 to 10
    for (let i = 1; i <= 10; i = i + 1) {
        print(i);
    }
    
    return 0;
}
```

### Functions
```algo
func factorial(n: int) -> int {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

func main() -> int {
    let result = factorial(5);
    print("5! = ");
    print(result);  // Output: 120
    return 0;
}
```

### Fibonacci
```algo
func fibonacci(n: int) -> int {
    if (n <= 1) {
        return n;
    }
    
    let prev = 0;
    let curr = 1;
    
    for (let i = 2; i <= n; i = i + 1) {
        let next = prev + curr;
        prev = curr;
        curr = next;
    }
    
    return curr;
}

func main() -> int {
    for (let i = 0; i < 10; i = i + 1) {
        print(fibonacci(i));
    }
    return 0;
}
```

---

## Grammar (BNF)

```bnf
program         ::= function*
function        ::= "func" identifier "(" parameters? ")" "->" type block
parameters      ::= parameter ("," parameter)*
parameter       ::= identifier ":" type
block           ::= "{" statement* "}"
statement       ::= declaration | assignment | ifStmt | whileStmt | 
                    forStmt | returnStmt | expressionStmt | block
declaration     ::= ("let" | "const") identifier (":" type)? "=" expression ";"
assignment      ::= identifier "=" expression ";"
ifStmt          ::= "if" "(" expression ")" block ("else" (ifStmt | block))?
whileStmt       ::= "while" "(" expression ")" block
forStmt         ::= "for" "(" declaration expression ";" assignment ")" block
returnStmt      ::= "return" expression? ";"
expressionStmt  ::= expression ";"
expression      ::= logicalOr
logicalOr       ::= logicalAnd ("||" logicalAnd)*
logicalAnd      ::= equality ("&&" equality)*
equality        ::= comparison (("==" | "!=") comparison)*
comparison      ::= bitwiseOr (("<" | "<=" | ">" | ">=") bitwiseOr)*
bitwiseOr       ::= bitwiseXor ("|" bitwiseXor)*
bitwiseXor      ::= bitwiseAnd ("^" bitwiseAnd)*
bitwiseAnd      ::= shift ("&" shift)*
shift           ::= addition (("<<" | ">>") addition)*
addition        ::= multiplication (("+" | "-") multiplication)*
multiplication  ::= unary (("*" | "/" | "%") unary)*
unary           ::= ("!" | "-" | "~") unary | call
call            ::= primary ("(" arguments? ")")*
arguments       ::= expression ("," expression)*
primary         ::= literal | identifier | "(" expression ")"
literal         ::= integer | string | "true" | "false"
type            ::= "int" | "string" | "bool" | "void"
identifier      ::= [a-zA-Z_][a-zA-Z0-9_]*
integer         ::= [0-9]+ | "0x"[0-9a-fA-F]+
string          ::= '"' [^"]* '"'
```

---

## Compilation Process

```
Source Code (.algo)
    ↓
Lexical Analysis (Tokenization)
    ↓
Syntax Analysis (Parsing → AST)
    ↓
Semantic Analysis (Type Checking)
    ↓
Code Generation (Assembly .asm)
    ↓
Assembly (Binary .bin)
    ↓
Execution (A1M Emulator)
```

---

## Reserved for Future

- Arrays: `let arr: int[10];`
- Structures: `struct Point { x: int, y: int }`
- Pointers: `let ptr: int* = &x;`
- Dynamic memory: `malloc()`, `free()`
- File I/O: `fopen()`, `fwrite()`, `fread()`
- Advanced types: `float`, `char`, `byte`

---

## License

Copyright (c) 2025 A1M CPU Project
See LICENSE file for details.
