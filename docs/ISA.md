# A1M Instruction Set Architecture (ISA)

## Instruction Encoding

All A1M instructions are 32 bits wide. The opcode occupies the upper 8 bits (bits 31-24).

## Opcode Table

| Opcode | Mnemonic | Type | Description |
|--------|----------|------|-------------|
| 0x00 | NOP | - | No operation |
| 0x01 | HALT | - | Halt execution |
| 0x02 | ADD | R | Add two registers |
| 0x03 | ADDI | I | Add immediate |
| 0x04 | SUB | R | Subtract registers |
| 0x05 | SUBI | I | Subtract immediate |
| 0x06 | MUL | R | Multiply registers |
| 0x07 | MULI | I | Multiply immediate |
| 0x08 | DIV | R | Divide registers |
| 0x09 | DIVI | I | Divide immediate |
| 0x0A | MOD | R | Modulo operation |
| 0x0B | MODI | I | Modulo immediate |
| 0x0C | AND | R | Bitwise AND |
| 0x0D | ANDI | I | AND immediate |
| 0x0E | OR | R | Bitwise OR |
| 0x0F | ORI | I | OR immediate |
| 0x10 | XOR | R | Bitwise XOR |
| 0x11 | XORI | I | XOR immediate |
| 0x12 | NOT | R | Bitwise NOT |
| 0x13 | SHL | R | Shift left logical |
| 0x14 | SHLI | I | Shift left immediate |
| 0x15 | SHR | R | Shift right logical |
| 0x16 | SHRI | I | Shift right immediate |
| 0x17 | SAR | R | Shift arithmetic right |
| 0x18 | SARI | I | Shift arithmetic immediate |
| 0x19 | CMP | R | Compare registers |
| 0x1A | CMPI | I | Compare immediate |
| 0x1B | TEST | R | Bitwise test |
| 0x20 | LOAD | M | Load from memory |
| 0x21 | STORE | M | Store to memory |
| 0x22 | LOADB | M | Load byte |
| 0x23 | STOREB | M | Store byte |
| 0x24 | LOADH | M | Load halfword (16-bit) |
| 0x25 | STOREH | M | Store halfword |
| 0x26 | LOADW | M | Load word (32-bit) |
| 0x27 | STOREW | M | Store word |
| 0x28 | PUSH | M | Push to stack |
| 0x29 | POP | M | Pop from stack |
| 0x30 | JMP | J | Unconditional jump |
| 0x31 | JZ | J | Jump if zero |
| 0x32 | JNZ | J | Jump if not zero |
| 0x33 | JC | J | Jump if carry |
| 0x34 | JNC | J | Jump if not carry |
| 0x35 | JO | J | Jump if overflow |
| 0x36 | JNO | J | Jump if not overflow |
| 0x37 | JN | J | Jump if negative |
| 0x38 | JNN | J | Jump if not negative |
| 0x39 | CALL | J | Call subroutine |
| 0x3A | RET | - | Return from subroutine |
| 0x3B | JR | R | Jump register |
| 0x40 | MOV | R | Move register to register |
| 0x41 | MOVI | I | Move immediate to register |
| 0x42 | LUI | I | Load upper immediate |
| 0x50 | SYSCALL | I | System call |

## Instruction Details

### Arithmetic Instructions

#### ADD - Add Registers
- **Format**: R-Type
- **Syntax**: `ADD rd, rs1, rs2`
- **Operation**: `rd = rs1 + rs2`
- **Flags**: Sets ZF, CF, OF, NF

#### ADDI - Add Immediate
- **Format**: I-Type
- **Syntax**: `ADDI rd, rs1, imm`
- **Operation**: `rd = rs1 + sign_extend(imm)`
- **Flags**: Sets ZF, CF, OF, NF

#### SUB - Subtract Registers
- **Format**: R-Type
- **Syntax**: `SUB rd, rs1, rs2`
- **Operation**: `rd = rs1 - rs2`
- **Flags**: Sets ZF, CF, OF, NF

#### MUL - Multiply Registers
- **Format**: R-Type
- **Syntax**: `MUL rd, rs1, rs2`
- **Operation**: `rd = rs1 * rs2` (lower 64 bits)
- **Flags**: Sets ZF, OF (if overflow)

#### DIV - Divide Registers
- **Format**: R-Type
- **Syntax**: `DIV rd, rs1, rs2`
- **Operation**: `rd = rs1 / rs2`
- **Exception**: Division by zero exception if rs2 == 0

#### MOD - Modulo
- **Format**: R-Type
- **Syntax**: `MOD rd, rs1, rs2`
- **Operation**: `rd = rs1 % rs2`

### Logical Instructions

#### AND - Bitwise AND
- **Format**: R-Type
- **Syntax**: `AND rd, rs1, rs2`
- **Operation**: `rd = rs1 & rs2`
- **Flags**: Sets ZF, NF

#### OR - Bitwise OR
- **Format**: R-Type
- **Syntax**: `OR rd, rs1, rs2`
- **Operation**: `rd = rs1 | rs2`
- **Flags**: Sets ZF, NF

#### XOR - Bitwise XOR
- **Format**: R-Type
- **Syntax**: `XOR rd, rs1, rs2`
- **Operation**: `rd = rs1 ^ rs2`
- **Flags**: Sets ZF, NF

#### NOT - Bitwise NOT
- **Format**: R-Type
- **Syntax**: `NOT rd, rs1`
- **Operation**: `rd = ~rs1`
- **Flags**: Sets ZF, NF

### Shift Instructions

#### SHL - Shift Left Logical
- **Format**: R-Type
- **Syntax**: `SHL rd, rs1, rs2`
- **Operation**: `rd = rs1 << rs2`
- **Flags**: Sets CF (last bit shifted out)

#### SHR - Shift Right Logical
- **Format**: R-Type
- **Syntax**: `SHR rd, rs1, rs2`
- **Operation**: `rd = rs1 >> rs2` (zero-fill)

#### SAR - Shift Arithmetic Right
- **Format**: R-Type
- **Syntax**: `SAR rd, rs1, rs2`
- **Operation**: `rd = rs1 >> rs2` (sign-extend)

### Memory Instructions

#### LOAD - Load Doubleword
- **Format**: M-Type
- **Syntax**: `LOAD rd, offset(rs1)`
- **Operation**: `rd = memory[rs1 + sign_extend(offset)]`

#### STORE - Store Doubleword
- **Format**: M-Type
- **Syntax**: `STORE rs2, offset(rs1)`
- **Operation**: `memory[rs1 + sign_extend(offset)] = rs2`

#### LOADB - Load Byte
- **Format**: M-Type
- **Syntax**: `LOADB rd, offset(rs1)`
- **Operation**: `rd = zero_extend(memory[rs1 + offset])`

#### PUSH - Push to Stack
- **Format**: M-Type
- **Syntax**: `PUSH rs1`
- **Operation**: `SP = SP - 8; memory[SP] = rs1`

#### POP - Pop from Stack
- **Format**: M-Type
- **Syntax**: `POP rd`
- **Operation**: `rd = memory[SP]; SP = SP + 8`

### Control Flow Instructions

#### JMP - Unconditional Jump
- **Format**: J-Type
- **Syntax**: `JMP address`
- **Operation**: `PC = PC + sign_extend(address << 2)`

#### JZ - Jump if Zero
- **Format**: J-Type
- **Syntax**: `JZ address`
- **Operation**: `if (ZF == 1) PC = PC + sign_extend(address << 2)`

#### CALL - Call Subroutine
- **Format**: J-Type
- **Syntax**: `CALL address`
- **Operation**: `R31 = PC + 4; PC = PC + sign_extend(address << 2)`

#### RET - Return from Subroutine
- **Format**: -
- **Syntax**: `RET`
- **Operation**: `PC = R31`

#### JR - Jump Register
- **Format**: R-Type
- **Syntax**: `JR rs1`
- **Operation**: `PC = rs1`

### Data Movement Instructions

#### MOV - Move Register
- **Format**: R-Type
- **Syntax**: `MOV rd, rs1`
- **Operation**: `rd = rs1`

#### MOVI - Move Immediate
- **Format**: I-Type
- **Syntax**: `MOVI rd, imm`
- **Operation**: `rd = sign_extend(imm)`

#### LUI - Load Upper Immediate
- **Format**: I-Type
- **Syntax**: `LUI rd, imm`
- **Operation**: `rd = imm << 50` (places immediate in upper bits)

### Special Instructions

#### NOP - No Operation
- **Format**: -
- **Syntax**: `NOP`
- **Operation**: No effect

#### HALT - Halt Execution
- **Format**: -
- **Syntax**: `HALT`
- **Operation**: Stop CPU execution

#### SYSCALL - System Call
- **Format**: I-Type
- **Syntax**: `SYSCALL imm`
- **Operation**: Execute system call specified by imm
- **System Calls**:
  - 0x00: exit(R1)
  - 0x01: print_int(R1)
  - 0x02: print_char(R1)
  - 0x03: read_int() -> R1
  - 0x04: read_char() -> R1

## Assembly Language Syntax

### Comments
```asm
; This is a comment
```

### Labels
```asm
main:
    ; code here
```

### Directives
```asm
.text           ; Code section
.data           ; Data section
.word value     ; Define 64-bit word
.byte value     ; Define byte
.string "text"  ; Define string
.space n        ; Reserve n bytes
```

## Example Programs

### Hello World
```asm
.data
msg: .string "Hello, World!\n"

.text
main:
    MOVI R1, msg        ; Load message address
    MOVI R2, 14         ; Message length
    SYSCALL 0x02        ; Print string
    HALT
```

### Fibonacci
```asm
.text
main:
    MOVI R1, 10         ; n = 10
    CALL fibonacci
    MOV R1, R2          ; Move result to R1
    SYSCALL 0x01        ; Print integer
    HALT

fibonacci:
    PUSH R31            ; Save return address
    PUSH R1             ; Save n
    
    CMPI R1, 1
    JNC base_case
    
    SUBI R1, R1, 1
    CALL fibonacci
    PUSH R2             ; Save fib(n-1)
    
    POP R1
    SUBI R1, R1, 2
    CALL fibonacci
    POP R3
    ADD R2, R2, R3      ; fib(n-1) + fib(n-2)
    
    POP R1
    POP R31
    RET

base_case:
    MOV R2, R1
    POP R1
    POP R31
    RET
```

## Instruction Encoding Examples

### ADD R3, R1, R2
```
Opcode: 0x02 (ADD)
rd: 3, rs1: 1, rs2: 2, func: 0
Binary: 00000010 00011 00001 00010 000000000
Hex: 0x02188400
```

### ADDI R5, R4, 100
```
Opcode: 0x03 (ADDI)
rd: 5, rs1: 4, imm: 100
Binary: 00000011 00101 00100 00000001100100
Hex: 0x03288064
```

### LOAD R2, 8(R1)
```
Opcode: 0x20 (LOAD)
rd: 2, rs1: 1, offset: 8
Binary: 00100000 00010 00001 00000000001000
Hex: 0x20110008
```
