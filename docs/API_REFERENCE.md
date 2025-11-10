# A1M Standard Library API Reference

## Overview

The A1M Standard Library provides essential functions for I/O operations, mathematics, string manipulation, and system utilities.

---

## Table of Contents

1. [Input/Output Functions](#inputoutput-functions)
2. [Mathematical Functions](#mathematical-functions)
3. [String Functions](#string-functions)
4. [System Functions](#system-functions)
5. [Memory Functions](#memory-functions)
6. [SYSCALL Interface](#syscall-interface)

---

## Input/Output Functions

### print()

**Syntax:**
```algo
print(value);
```

**Description:**  
Prints a value to standard output. Supports integers and strings.

**Parameters:**
- `value` - Integer or string to print

**Returns:** void

**Examples:**
```algo
print("Hello, World!");     // Print string
print(42);                   // Print integer
print(x);                    // Print variable
```

**Implementation:**
- For integers: Uses SYSCALL 0x01 (print_int)
- For strings: Uses SYSCALL 0x04 (print_string)

---

### println()

**Syntax:**
```algo
println(value);
```

**Description:**  
Prints a value followed by a newline character.

**Parameters:**
- `value` - Value to print

**Returns:** void

**Examples:**
```algo
println("Hello!");
println(42);
```

---

### input()

**Syntax:**
```algo
let value = input();
```

**Description:**  
Reads an integer from standard input.

**Parameters:** None

**Returns:** int - The integer entered by user

**Examples:**
```algo
let age = input();
print("You entered: ");
println(age);
```

**Implementation:**
Uses SYSCALL 0x03 (read_int)

---

### input_str()

**Syntax:**
```algo
let text = input_str();
```

**Description:**  
Reads a string from standard input.

**Parameters:** None

**Returns:** string - The string entered by user

**Examples:**
```algo
let name = input_str();
print("Hello, ");
println(name);
```

---

## Mathematical Functions

### abs()

**Syntax:**
```algo
let result = abs(value);
```

**Description:**  
Returns the absolute value of a number.

**Parameters:**
- `value: int` - Input value

**Returns:** int - Absolute value

**Examples:**
```algo
let x = abs(-42);    // x = 42
let y = abs(17);     // y = 17
```

---

### min()

**Syntax:**
```algo
let result = min(a, b);
```

**Description:**  
Returns the smaller of two values.

**Parameters:**
- `a: int` - First value
- `b: int` - Second value

**Returns:** int - Minimum value

**Examples:**
```algo
let small = min(10, 20);     // small = 10
let val = min(-5, 3);        // val = -5
```

---

### max()

**Syntax:**
```algo
let result = max(a, b);
```

**Description:**  
Returns the larger of two values.

**Parameters:**
- `a: int` - First value
- `b: int` - Second value

**Returns:** int - Maximum value

**Examples:**
```algo
let large = max(10, 20);     // large = 20
let val = max(-5, 3);        // val = 3
```

---

### pow()

**Syntax:**
```algo
let result = pow(base, exponent);
```

**Description:**  
Calculates base raised to the power of exponent.

**Parameters:**
- `base: int` - Base value
- `exponent: int` - Exponent (must be non-negative)

**Returns:** int - Result of base^exponent

**Examples:**
```algo
let x = pow(2, 10);      // x = 1024
let y = pow(5, 3);       // y = 125
let z = pow(10, 0);      // z = 1
```

**Notes:**
- Currently supports only integer exponents
- For negative exponents, result is 0 (integer division)

---

### sqrt()

**Syntax:**
```algo
let result = sqrt(value);
```

**Description:**  
Calculates the integer square root of a value.

**Parameters:**
- `value: int` - Input value (must be non-negative)

**Returns:** int - Integer square root

**Examples:**
```algo
let x = sqrt(16);        // x = 4
let y = sqrt(100);       // y = 10
let z = sqrt(50);        // z = 7 (rounded down)
```

---

### mod()

**Syntax:**
```algo
let result = a % b;
```

**Description:**  
Returns the remainder of integer division.

**Parameters:**
- `a: int` - Dividend
- `b: int` - Divisor

**Returns:** int - Remainder

**Examples:**
```algo
let r1 = 10 % 3;         // r1 = 1
let r2 = 17 % 5;         // r2 = 2
let r3 = 20 % 4;         // r3 = 0
```

---

## String Functions

### strlen()

**Syntax:**
```algo
let length = strlen(str);
```

**Description:**  
Returns the length of a string.

**Parameters:**
- `str: string` - Input string

**Returns:** int - Number of characters

**Examples:**
```algo
let len = strlen("Hello");       // len = 5
let count = strlen("World!");    // count = 6
```

---

### strcmp()

**Syntax:**
```algo
let result = strcmp(str1, str2);
```

**Description:**  
Compares two strings lexicographically.

**Parameters:**
- `str1: string` - First string
- `str2: string` - Second string

**Returns:** int
- 0 if strings are equal
- < 0 if str1 < str2
- > 0 if str1 > str2

**Examples:**
```algo
let cmp = strcmp("abc", "abc");   // cmp = 0
let r1 = strcmp("abc", "xyz");    // r1 < 0
let r2 = strcmp("xyz", "abc");    // r2 > 0
```

---

### strcat()

**Syntax:**
```algo
let result = strcat(str1, str2);
```

**Description:**  
Concatenates two strings.

**Parameters:**
- `str1: string` - First string
- `str2: string` - Second string

**Returns:** string - Concatenated string

**Examples:**
```algo
let full = strcat("Hello, ", "World!");
// full = "Hello, World!"
```

---

### substr()

**Syntax:**
```algo
let result = substr(str, start, length);
```

**Description:**  
Extracts a substring.

**Parameters:**
- `str: string` - Source string
- `start: int` - Starting index (0-based)
- `length: int` - Number of characters

**Returns:** string - Substring

**Examples:**
```algo
let sub = substr("Hello", 1, 3);     // sub = "ell"
let word = substr("World", 0, 3);    // word = "Wor"
```

---

### toupper()

**Syntax:**
```algo
let result = toupper(str);
```

**Description:**  
Converts string to uppercase.

**Parameters:**
- `str: string` - Input string

**Returns:** string - Uppercase string

**Examples:**
```algo
let upper = toupper("hello");    // upper = "HELLO"
```

---

### tolower()

**Syntax:**
```algo
let result = tolower(str);
```

**Description:**  
Converts string to lowercase.

**Parameters:**
- `str: string` - Input string

**Returns:** string - Lowercase string

**Examples:**
```algo
let lower = tolower("WORLD");    // lower = "world"
```

---

## System Functions

### exit()

**Syntax:**
```algo
exit(code);
```

**Description:**  
Exits the program with a status code.

**Parameters:**
- `code: int` - Exit status code (0 = success)

**Returns:** void (never returns)

**Examples:**
```algo
exit(0);        // Exit successfully
exit(1);        // Exit with error
```

**Implementation:**
Uses SYSCALL 0x00 with exit code in R1

---

### sleep()

**Syntax:**
```algo
sleep(milliseconds);
```

**Description:**  
Pauses execution for specified milliseconds.

**Parameters:**
- `milliseconds: int` - Time to sleep

**Returns:** void

**Examples:**
```algo
sleep(1000);      // Sleep for 1 second
sleep(500);       // Sleep for 0.5 seconds
```

---

### time()

**Syntax:**
```algo
let timestamp = time();
```

**Description:**  
Returns current timestamp (implementation-dependent).

**Parameters:** None

**Returns:** int - Current time

---

## Memory Functions

### malloc()

**Syntax:**
```algo
let ptr = malloc(size);
```

**Description:**  
Allocates memory dynamically (future implementation).

**Parameters:**
- `size: int` - Number of bytes to allocate

**Returns:** int - Pointer to allocated memory

**Status:** ⚠️ Not yet implemented

---

### free()

**Syntax:**
```algo
free(ptr);
```

**Description:**  
Frees dynamically allocated memory.

**Parameters:**
- `ptr: int` - Pointer to free

**Returns:** void

**Status:** ⚠️ Not yet implemented

---

## SYSCALL Interface

The A1M CPU provides low-level system calls for direct hardware interaction.

### SYSCALL Table

| Number | Name | Description | R1 (In) | R1 (Out) |
|--------|------|-------------|---------|----------|
| 0x00 | exit | Terminate program | Exit code | - |
| 0x01 | print_int | Print integer | Value | - |
| 0x02 | print_char | Print character | ASCII value | - |
| 0x03 | read_int | Read integer | - | Value read |
| 0x04 | print_string | Print string | String address | - |
| 0x05 | read_string | Read string | Buffer address | Length |
| 0x10 | open | Open file | Path address | File descriptor |
| 0x11 | close | Close file | File descriptor | Status |
| 0x12 | read | Read from file | File descriptor | Bytes read |
| 0x13 | write | Write to file | File descriptor | Bytes written |

### Using SYSCALL in Assembly

```asm
; Print integer (SYSCALL 0x01)
MOVI R1, 42
SYSCALL 0x01

; Print string (SYSCALL 0x04)
MOVI R1, string_addr
SYSCALL 0x04

; Read integer (SYSCALL 0x03)
SYSCALL 0x03
; Result in R1

; Exit program (SYSCALL 0x00)
MOVI R1, 0
SYSCALL 0x00
HALT
```

---

## Planned Functions

### Version 1.1

- `printf()` - Formatted printing
- `scanf()` - Formatted input
- `random()` - Random number generation
- `array_sort()` - Array sorting
- `array_search()` - Array searching

### Version 2.0

- `fopen()` - File operations
- `fread()` / `fwrite()` - File I/O
- `malloc()` / `free()` - Dynamic memory
- `thread_create()` - Multi-threading
- `mutex_lock()` / `mutex_unlock()` - Synchronization

---

## Error Codes

| Code | Name | Description |
|------|------|-------------|
| 0 | SUCCESS | Operation successful |
| 1 | ERROR | Generic error |
| 2 | INVALID_ARG | Invalid argument |
| 3 | OUT_OF_MEMORY | Memory allocation failed |
| 4 | IO_ERROR | I/O operation failed |
| 5 | DIV_BY_ZERO | Division by zero |

---

## Examples

### Complete Program Example

```algo
// Calculator program using standard library

func add(a: int, b: int) -> int {
    return a + b;
}

func subtract(a: int, b: int) -> int {
    return a - b;
}

func main() -> int {
    println("=== A1M Calculator ===");
    
    print("Enter first number: ");
    let num1 = input();
    
    print("Enter second number: ");
    let num2 = input();
    
    println("\nResults:");
    print("Sum: ");
    println(add(num1, num2));
    
    print("Difference: ");
    println(subtract(num1, num2));
    
    print("Maximum: ");
    println(max(num1, num2));
    
    print("Minimum: ");
    println(min(num1, num2));
    
    return 0;
}
```

---

## Performance Notes

- **print()**: O(n) where n is string length
- **strlen()**: O(n) where n is string length
- **strcmp()**: O(min(n, m)) where n, m are string lengths
- **pow()**: O(log n) using fast exponentiation
- **sqrt()**: O(log n) using binary search

---

## Thread Safety

Currently, the standard library is **not thread-safe**. Thread safety will be added in Version 2.0.

---

## Platform Notes

- All integers are 64-bit signed
- Strings are null-terminated byte arrays
- Memory addresses are 64-bit
- Stack grows downward from high memory
- Heap grows upward from low memory (when implemented)

---

Copyright (c) 2025 A1M CPU Project  
See [LICENSE](../LICENSE) for details.
