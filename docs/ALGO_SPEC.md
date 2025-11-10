# Algo Language Specification

## Overview

Algo is a statically-typed, high-level programming language designed to compile to A1M assembly. It features C-like syntax with modern language features.

## File Extension
`.algo`

## Lexical Structure

### Keywords
```
func, return, if, else, while, for, break, continue,
let, const, int, bool, char, string, void,
true, false, print, input
```

### Operators
```
Arithmetic: +, -, *, /, %
Comparison: ==, !=, <, >, <=, >=
Logical: &&, ||, !
Bitwise: &, |, ^, ~, <<, >>
Assignment: =, +=, -=, *=, /=, %=
```

### Delimiters
```
( ) { } [ ] ; , :
```

### Comments
```algo
// Single-line comment
/* Multi-line
   comment */
```

## Data Types

### Primitive Types
- `int`: 64-bit signed integer
- `bool`: Boolean (true/false)
- `char`: 8-bit character
- `void`: No return value

### Composite Types
- Arrays: `int[10]`
- Strings: `string` (array of char)

## Variables

### Declaration
```algo
let x: int = 42;
let y: int;
const MAX: int = 100;
```

### Type Inference
```algo
let x = 42;        // Inferred as int
let flag = true;   // Inferred as bool
```

## Functions

### Function Declaration
```algo
func add(a: int, b: int) -> int {
    return a + b;
}

func greet(name: string) -> void {
    print("Hello, ");
    print(name);
}
```

### Main Function
```algo
func main() -> int {
    print("Hello, World!");
    return 0;
}
```

## Control Flow

### If Statement
```algo
if (x > 0) {
    print("Positive");
} else if (x < 0) {
    print("Negative");
} else {
    print("Zero");
}
```

### While Loop
```algo
let i = 0;
while (i < 10) {
    print(i);
    i = i + 1;
}
```

### For Loop
```algo
for (let i = 0; i < 10; i = i + 1) {
    print(i);
}
```

### Break and Continue
```algo
while (true) {
    if (x == 10) {
        break;
    }
    if (x % 2 == 0) {
        continue;
    }
    print(x);
}
```

## Arrays

### Declaration and Initialization
```algo
let arr: int[5];
let nums: int[3] = [1, 2, 3];
```

### Array Access
```algo
arr[0] = 42;
let x = arr[0];
```

## Built-in Functions

### I/O Functions
```algo
print(value);       // Print value
let x = input();    // Read integer input
```

## Operators

### Arithmetic Operators
```algo
let sum = a + b;
let diff = a - b;
let prod = a * b;
let quot = a / b;
let rem = a % b;
```

### Comparison Operators
```algo
if (a == b) { }
if (a != b) { }
if (a < b) { }
if (a > b) { }
if (a <= b) { }
if (a >= b) { }
```

### Logical Operators
```algo
if (a && b) { }    // AND
if (a || b) { }    // OR
if (!a) { }        // NOT
```

### Bitwise Operators
```algo
let x = a & b;     // AND
let y = a | b;     // OR
let z = a ^ b;     // XOR
let w = ~a;        // NOT
let left = a << 2; // Shift left
let right = a >> 2;// Shift right
```

## Example Programs

### Hello World
```algo
func main() -> int {
    print("Hello, World!");
    return 0;
}
```

### Factorial
```algo
func factorial(n: int) -> int {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

func main() -> int {
    let result = factorial(5);
    print(result);
    return 0;
}
```

### Fibonacci Sequence
```algo
func fibonacci(n: int) -> int {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

func main() -> int {
    for (let i = 0; i < 10; i = i + 1) {
        print(fibonacci(i));
    }
    return 0;
}
```

### Array Sum
```algo
func sum_array(arr: int[], size: int) -> int {
    let total = 0;
    for (let i = 0; i < size; i = i + 1) {
        total = total + arr[i];
    }
    return total;
}

func main() -> int {
    let numbers: int[5] = [10, 20, 30, 40, 50];
    let result = sum_array(numbers, 5);
    print(result);
    return 0;
}
```

### Bubble Sort
```algo
func bubble_sort(arr: int[], n: int) -> void {
    for (let i = 0; i < n - 1; i = i + 1) {
        for (let j = 0; j < n - i - 1; j = j + 1) {
            if (arr[j] > arr[j + 1]) {
                let temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

func main() -> int {
    let arr: int[5] = [64, 34, 25, 12, 22];
    bubble_sort(arr, 5);
    
    for (let i = 0; i < 5; i = i + 1) {
        print(arr[i]);
    }
    return 0;
}
```

### GCD (Greatest Common Divisor)
```algo
func gcd(a: int, b: int) -> int {
    while (b != 0) {
        let temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

func main() -> int {
    let result = gcd(48, 18);
    print(result);
    return 0;
}
```

## Grammar (BNF)

```bnf
<program> ::= <function>*

<function> ::= "func" <identifier> "(" <params> ")" "->" <type> <block>

<params> ::= <param> ("," <param>)* | ε
<param> ::= <identifier> ":" <type>

<type> ::= "int" | "bool" | "char" | "void" | <type> "[" <integer> "]"

<block> ::= "{" <statement>* "}"

<statement> ::= <var_decl>
              | <assignment>
              | <if_stmt>
              | <while_stmt>
              | <for_stmt>
              | <return_stmt>
              | <break_stmt>
              | <continue_stmt>
              | <expr_stmt>

<var_decl> ::= ("let" | "const") <identifier> (":" <type>)? "=" <expr> ";"

<assignment> ::= <identifier> <assign_op> <expr> ";"
<assign_op> ::= "=" | "+=" | "-=" | "*=" | "/=" | "%="

<if_stmt> ::= "if" "(" <expr> ")" <block> ("else" <block>)?

<while_stmt> ::= "while" "(" <expr> ")" <block>

<for_stmt> ::= "for" "(" <var_decl> <expr> ";" <assignment> ")" <block>

<return_stmt> ::= "return" <expr>? ";"

<break_stmt> ::= "break" ";"

<continue_stmt> ::= "continue" ";"

<expr_stmt> ::= <expr> ";"

<expr> ::= <logical_or>

<logical_or> ::= <logical_and> ("||" <logical_and>)*

<logical_and> ::= <bitwise_or> ("&&" <bitwise_or>)*

<bitwise_or> ::= <bitwise_xor> ("|" <bitwise_xor>)*

<bitwise_xor> ::= <bitwise_and> ("^" <bitwise_and>)*

<bitwise_and> ::= <equality> ("&" <equality>)*

<equality> ::= <relational> (("==" | "!=") <relational>)*

<relational> ::= <shift> (("<" | ">" | "<=" | ">=") <shift>)*

<shift> ::= <additive> (("<<" | ">>") <additive>)*

<additive> ::= <multiplicative> (("+" | "-") <multiplicative>)*

<multiplicative> ::= <unary> (("*" | "/" | "%") <unary>)*

<unary> ::= ("!" | "-" | "~") <unary> | <postfix>

<postfix> ::= <primary> ("[" <expr> "]")*

<primary> ::= <identifier>
            | <integer>
            | <string>
            | "true"
            | "false"
            | "(" <expr> ")"
            | <function_call>

<function_call> ::= <identifier> "(" <arguments> ")"

<arguments> ::= <expr> ("," <expr>)* | ε

<identifier> ::= [a-zA-Z_][a-zA-Z0-9_]*

<integer> ::= [0-9]+

<string> ::= '"' [^"]* '"'
```

## Compilation Process

1. **Lexical Analysis**: Source code → Tokens
2. **Syntax Analysis**: Tokens → Abstract Syntax Tree (AST)
3. **Semantic Analysis**: Type checking, scope resolution
4. **Code Generation**: AST → A1M Assembly
5. **Optimization**: Optimize assembly code (optional)

## Type System

- Strong static typing
- Type inference for local variables
- No implicit type conversions (explicit casting required)

## Scoping Rules

- Block scope for local variables
- Function scope for parameters
- Global scope for functions
- No global variables (functions only at top level)

## Memory Management

- Stack-based allocation for local variables
- No dynamic memory allocation (heap) in initial version
- All arrays are fixed-size and stack-allocated
