# A1M CPU Quick Reference Card

## Essential Commands

### Build Everything
```bash
./build.sh
```

### Run Demo
```bash
./demo.sh
```

### Run Tests
```bash
./test.sh
```

## Assembler

### Basic Usage
```bash
./assembler/a1m-asm input.asm -o output.bin
```

### Example
```bash
./assembler/a1m-asm examples/asm/hello.asm -o hello.bin
```

## Emulator

### Run Program
```bash
./emulator/a1m-emu program.bin
```

### Debug Mode
```bash
./emulator/a1m-emu program.bin -d        # Show each instruction
./emulator/a1m-emu program.bin -s        # Step-by-step execution
./emulator/a1m-emu program.bin -r        # Dump registers at end
./emulator/a1m-emu program.bin -m        # Dump memory at end
```

## Compiler

### Compile Algo to Assembly
```bash
./compiler/algo-compiler program.algo -o program.asm
```

### Full Pipeline
```bash
./compiler/algo-compiler program.algo -o program.asm
./assembler/a1m-asm program.asm -o program.bin
./emulator/a1m-emu program.bin
```

## GUI

### Launch GUI
```bash
./gui/a1m-gui
```

## Common Assembly Instructions

### Data Movement
```asm
MOVI R1, 42          ; R1 = 42
MOV R2, R1           ; R2 = R1
LOAD R3, 0(R4)       ; R3 = memory[R4]
STORE R5, 8(R6)      ; memory[R6+8] = R5
```

### Arithmetic
```asm
ADD R1, R2, R3       ; R1 = R2 + R3
ADDI R1, R2, 100     ; R1 = R2 + 100
SUB R1, R2, R3       ; R1 = R2 - R3
MUL R1, R2, R3       ; R1 = R2 * R3
DIV R1, R2, R3       ; R1 = R2 / R3
```

### Logical
```asm
AND R1, R2, R3       ; R1 = R2 & R3
OR R1, R2, R3        ; R1 = R2 | R3
XOR R1, R2, R3       ; R1 = R2 ^ R3
NOT R1, R2           ; R1 = ~R2
SHL R1, R2, R3       ; R1 = R2 << R3
SHR R1, R2, R3       ; R1 = R2 >> R3
```

### Control Flow
```asm
JMP label            ; Unconditional jump
JZ label             ; Jump if zero
JNZ label            ; Jump if not zero
CALL function        ; Call subroutine
RET                  ; Return from subroutine
```

### Stack
```asm
PUSH R1              ; Push R1 to stack
POP R2               ; Pop from stack to R2
```

### System Calls
```asm
SYSCALL 0x00         ; exit(R1)
SYSCALL 0x01         ; print_int(R1)
SYSCALL 0x02         ; print_char(R1)
SYSCALL 0x03         ; read_int() -> R1
```

### Program Control
```asm
NOP                  ; No operation
HALT                 ; Stop execution
```

## Algo Language Syntax

### Variables
```algo
let x: int = 42;
let y = 10;          // Type inference
const MAX = 100;
```

### Functions
```algo
func add(a: int, b: int) -> int {
    return a + b;
}

func main() -> int {
    let result = add(5, 3);
    print(result);
    return 0;
}
```

### Control Flow
```algo
// If statement
if (x > 0) {
    print("positive");
} else {
    print("non-positive");
}

// While loop
while (i < 10) {
    print(i);
    i = i + 1;
}

// For loop
for (let i = 0; i < 10; i = i + 1) {
    print(i);
}
```

### Arrays
```algo
let arr: int[5];
arr[0] = 42;
let x = arr[0];
```

## Registers

### General Purpose
- **R0** - Always zero (read-only)
- **R1-R30** - General purpose
- **R31** - Link register (used by CALL/RET)

### Special
- **PC** - Program Counter
- **SP** - Stack Pointer
- **FLAGS** - Status flags (Z, C, O, N)

## Memory Layout

| Address Range | Usage |
|---------------|-------|
| 0x7FFF...FFF0 | Stack (top) |
| 0x0030...0000 | Heap |
| 0x0010...0000 | Data segment |
| 0x0000...1000 | Code segment (reset vector) |
| 0x0000...0000 | Reserved |

## File Extensions

| Extension | Description |
|-----------|-------------|
| .algo | Algo source code |
| .asm | Assembly source |
| .bin | Binary executable |
| .v | Verilog HDL |
| .vh | Verilog header |

## Documentation Files

| File | Description |
|------|-------------|
| README.md | Project overview |
| GETTING_STARTED.md | Tutorial |
| PROJECT_SUMMARY.md | Complete summary |
| docs/ISA.md | Instruction set |
| docs/ARCHITECTURE.md | CPU design |
| docs/ALGO_SPEC.md | Language spec |
| docs/ARCHITECTURE_DIAGRAM.md | Visual diagrams |

## Example Programs

### Assembly
- `examples/asm/hello.asm` - Hello World
- `examples/asm/fibonacci.asm` - Fibonacci
- `examples/asm/array_sum.asm` - Array operations

### Algo
- `examples/algo/hello.algo` - Hello World
- `examples/algo/fibonacci.algo` - Fibonacci
- `examples/algo/factorial.algo` - Factorial

## Debugging Tips

1. **Use step mode** to trace execution:
   ```bash
   ./emulator/a1m-emu program.bin -s
   ```

2. **Enable debug output**:
   ```bash
   ./emulator/a1m-emu program.bin -d
   ```

3. **Check registers** after execution:
   ```bash
   ./emulator/a1m-emu program.bin -r
   ```

4. **Verify assembly** output:
   ```bash
   ./assembler/a1m-asm program.asm -o program.bin
   hexdump -C program.bin
   ```

## Common Patterns

### Function Call
```asm
; Caller
MOVI R1, 10          ; Argument
CALL my_function
MOV R3, R2           ; Get return value

; Callee
my_function:
    PUSH R31         ; Save return address
    ; ... function body ...
    MOVI R2, 42      ; Return value
    POP R31
    RET
```

### Loop
```asm
    MOVI R1, 0       ; counter = 0
    MOVI R2, 10      ; limit = 10
loop:
    ; ... loop body ...
    ADDI R1, R1, 1   ; counter++
    CMP R1, R2
    JNZ loop         ; if counter != limit, continue
```

### Array Access
```asm
    MOVI R1, 0x100000  ; array base
    MOVI R2, 5         ; index
    MOVI R3, 8         ; element size
    MUL R4, R2, R3     ; offset = index * size
    ADD R5, R1, R4     ; address = base + offset
    LOAD R6, 0(R5)     ; load element
```

## Troubleshooting

### Build Issues
- **Missing gcc**: Install build-essential
- **Missing GTK**: Install libgtk-3-dev (GUI optional)

### Runtime Issues
- **Segfault**: Check memory bounds
- **Invalid opcode**: Verify assembly syntax
- **Undefined label**: Check label definitions

### Assembly Issues
- **Parse error**: Check instruction format
- **Register range**: Use R0-R31 only
- **Immediate too large**: 14-bit limit for I-type

## Performance

- **Pipeline**: 5 stages (IF, ID, EX, MEM, WB)
- **CPI**: ~1.2-1.5 (ideal: 1.0)
- **Clock**: 50-100 MHz (FPGA target)
- **Registers**: 32 × 64-bit
- **Memory**: 16 MB (emulator), configurable (FPGA)

## Quick Links

- Build: `./build.sh`
- Test: `./test.sh`
- Demo: `./demo.sh`
- Emulator: `./emulator/a1m-emu`
- Assembler: `./assembler/a1m-asm`
- Compiler: `./compiler/algo-compiler`
- GUI: `./gui/a1m-gui`

---

**For More Information:** See GETTING_STARTED.md and docs/
