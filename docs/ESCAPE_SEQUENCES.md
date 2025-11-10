# String Escape Sequences - Quick Reference

## Supported Escape Sequences

The Algo language compiler now supports the following escape sequences in string literals:

| Escape Sequence | Description | ASCII Code | Example |
|----------------|-------------|------------|---------|
| `\n` | Newline | 10 (0x0A) | `print("Line 1\nLine 2");` |
| `\t` | Tab | 9 (0x09) | `print("Name:\tValue");` |
| `\r` | Carriage Return | 13 (0x0D) | `print("Text\r");` |
| `\\` | Backslash | 92 (0x5C) | `print("Path: C:\\folder");` |
| `\"` | Double Quote | 34 (0x22) | `print("He said \"Hi\"");` |
| `\0` | Null Character | 0 (0x00) | `print("End\0");` |

## Examples

### Basic Newlines
```algo
func main() -> int {
    print("Hello\nWorld");
    // Output:
    // Hello
    // World
    return 0;
}
```

### Formatted Output
```algo
func main() -> int {
    print("=== Report ===\n");
    print("Name:\tJohn Doe\n");
    print("Age:\t25\n");
    print("City:\tNew York\n");
    print("==============\n");
    return 0;
}
// Output:
// === Report ===
// Name:    John Doe
// Age:     25
// City:    New York
// ==============
```

### Quotes in Strings
```algo
func main() -> int {
    print("She said \"Hello!\"\n");
    print("The book's title is \"1984\"\n");
    return 0;
}
// Output:
// She said "Hello!"
// The book's title is "1984"
```

### Mixed Escape Sequences
```algo
func main() -> int {
    print("Line 1\n");
    print("\tIndented line\n");
    print("\t\tDouble indented\n");
    print("Back to normal\n");
    return 0;
}
// Output:
// Line 1
//     Indented line
//         Double indented
// Back to normal
```

### Combining with Variables
```algo
func main() -> int {
    let age: int = 25;
    print("Age: ");
    print(age);
    print("\n");
    
    let score: int = 95;
    print("Score:\t");
    print(score);
    print("\n");
    
    return 0;
}
// Output:
// Age: 25
// Score:  95
```

## Implementation Details

### Lexer Processing
The lexer (`compiler/src/lexer.c`) recognizes escape sequences during string tokenization:
- When a backslash (`\`) is encountered, the next character is checked
- Valid escape sequences are passed through to the code generator
- Invalid escape sequences are treated as literal characters

### Code Generation
The code generator (`compiler/src/codegen.c`) translates escape sequences:
- Each character in a string is emitted as a separate SYSCALL 0x02 (print_char)
- Escape sequences are converted to their ASCII values during emission
- Example: `\n` becomes `MOVI R1, 10` + `SYSCALL 0x02`

### Assembly Output
For the string `"Hello\n"`, the compiler generates:
```asm
MOVI R1, 72    ; 'H'
SYSCALL 0x02
MOVI R1, 101   ; 'e'
SYSCALL 0x02
MOVI R1, 108   ; 'l'
SYSCALL 0x02
MOVI R1, 108   ; 'l'
SYSCALL 0x02
MOVI R1, 111   ; 'o'
SYSCALL 0x02
MOVI R1, 10    ; '\n' (newline)
SYSCALL 0x02
```

## Testing

Test file included: `examples/algo/newline_test.algo`

To test escape sequences:
```bash
./compiler/algo-compiler examples/algo/newline_test.algo -o examples/asm/newline_test.asm
./assembler/a1m-asm examples/asm/newline_test.asm -o examples/bin/newline_test.bin
./emulator/a1m-emu examples/bin/newline_test.bin
```

Expected output shows proper line breaks and tab spacing.

## Future Enhancements

Potential future escape sequences:
- `\b` - Backspace
- `\f` - Form feed
- `\v` - Vertical tab
- `\xHH` - Hexadecimal character codes
- `\uHHHH` - Unicode characters
- `\ooo` - Octal character codes

---

**Note:** This feature was added in response to user request to support newline formatting in string output.
