# A1M CPU Architecture

## Overview

The A1M is a 64-bit RISC-inspired CPU architecture designed for simplicity and educational purposes. It features a load-store architecture with fixed-length 32-bit instructions.

## Register Set

### General Purpose Registers (GPRs)
- **R0-R31**: 32 general-purpose 64-bit registers
- **R0**: Hardwired to zero (reads always return 0, writes are ignored)
- **R1-R30**: General purpose
- **R31**: Link register (LR) - used for return addresses

### Special Registers
- **PC** (Program Counter): 64-bit, points to the current instruction
- **SP** (Stack Pointer): 64-bit, points to the top of the stack
- **FLAGS**: 64-bit status register with the following bits:
  - Bit 0: Zero Flag (ZF)
  - Bit 1: Carry Flag (CF)
  - Bit 2: Overflow Flag (OF)
  - Bit 3: Negative Flag (NF)
  - Bits 4-63: Reserved

## Memory Model

- **Address Space**: 64-bit addressing (16 EB theoretical)
- **Byte Addressable**: Each address points to a byte
- **Alignment**: No strict alignment requirements (though aligned access is faster)
- **Endianness**: Little-endian
- **Memory Layout**:
  - 0x0000000000000000 - 0x0000000000000FFF: Reserved
  - 0x0000000000001000 - 0x00000000000FFFFF: Text (code) segment
  - 0x0000000000100000 - 0x00000000001FFFFF: Data segment
  - 0x0000000000200000 - 0x00000000002FFFFF: Heap
  - 0x7FFFFFFFFFFFFFFF - 0x7FFFFFFFFFFFFFF0: Stack (grows downward)

## Instruction Format

All instructions are 32 bits wide with the following formats:

### R-Type (Register)
```
| opcode (8 bits) | rd (5 bits) | rs1 (5 bits) | rs2 (5 bits) | func (9 bits) |
  31          24    23       19   18        14   13         9    8          0
```

### I-Type (Immediate)
```
| opcode (8 bits) | rd (5 bits) | rs1 (5 bits) | immediate (14 bits) |
  31          24    23       19   18        14   13                 0
```

### J-Type (Jump)
```
| opcode (8 bits) | address (24 bits)                              |
  31          24    23                                             0
```

### M-Type (Memory)
```
| opcode (8 bits) | rd (5 bits) | rs1 (5 bits) | offset (14 bits) |
  31          24    23       19   18        14   13               0
```

## Pipeline Stages

The A1M CPU uses a 5-stage pipeline:

1. **Fetch (IF)**: Fetch instruction from memory at PC
2. **Decode (ID)**: Decode instruction and read registers
3. **Execute (EX)**: Execute operation in ALU or calculate address
4. **Memory (MEM)**: Access data memory if needed
5. **Writeback (WB)**: Write result back to register file

### Pipeline Hazards
- **Data Hazards**: Resolved using forwarding and stalling
- **Control Hazards**: Branch prediction (predict not taken)
- **Structural Hazards**: Avoided by design (separate instruction/data caches)

## ALU Operations

The ALU supports the following operations:
- **Arithmetic**: ADD, SUB, MUL, DIV, MOD
- **Logical**: AND, OR, XOR, NOT
- **Shift**: SHL (shift left), SHR (shift right logical), SAR (shift arithmetic right)
- **Comparison**: Compare two values and set flags

## Control Unit

The control unit generates control signals based on the opcode:
- Register write enable
- ALU operation select
- Memory read/write enable
- Branch/Jump control
- Immediate value selection

## Exception Handling

- **Reset**: PC set to 0x0000000000001000
- **Invalid Opcode**: Jump to exception handler at 0x0000000000000100
- **Division by Zero**: Jump to exception handler at 0x0000000000000200
- **Memory Access Violation**: Jump to exception handler at 0x0000000000000300

## Performance Characteristics

- **Clock Speed**: Target 50-100 MHz on FPGA
- **CPI** (Cycles Per Instruction): 1 (ideal pipeline), 1.2-1.5 (with hazards)
- **Maximum Memory Bandwidth**: 8 bytes per cycle
- **Branch Prediction Accuracy**: ~85% (simple static prediction)

## Design Philosophy

The A1M architecture prioritizes:
1. **Simplicity**: Easy to understand and implement
2. **Completeness**: Full instruction set for practical programs
3. **Performance**: Pipelined design with hazard mitigation
4. **Extensibility**: Easy to add new instructions or features
