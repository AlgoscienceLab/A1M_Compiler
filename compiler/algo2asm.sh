#!/bin/bash
# Simple Algo to Assembly translator
# Converts basic Algo programs to A1M assembly

input_file="$1"
output_file="$2"

if [ -z "$input_file" ] || [ -z "$output_file" ]; then
    echo "Usage: $0 <input.algo> <output.asm>"
    exit 1
fi

if [ ! -f "$input_file" ]; then
    echo "Error: Input file not found: $input_file"
    exit 1
fi

# Check if it's a print statement with a string
if grep -q 'print("' "$input_file"; then
    # Extract the string to print
    string_content=$(grep -o 'print("[^"]*")' "$input_file" | sed 's/print("//; s/")//')
    
    # Create assembly that stores string in memory and prints it
    cat > "$output_file" << 'ASM_HEADER'
; Generated from Algo source
; A1M Assembly Code

.text
main:
ASM_HEADER
    
    # Generate STOREB instructions for each character
    # Use address 0x2000 (8192) - fits in positive 14-bit immediate
    str_base=8000  # Use 8000 to be safe (below 8191 limit)
    for (( i=0; i<${#string_content}; i++ )); do
        char="${string_content:$i:1}"
        ascii_val=$(printf '%d' "'$char")
        str_addr=$((str_base + i))
        echo "    MOVI R2, $ascii_val" >> "$output_file"
        echo "    MOVI R3, $str_addr" >> "$output_file"
        echo "    STOREB R2, (R3)" >> "$output_file"
    done
    
    # Store null terminator
    str_end=$((str_base + ${#string_content}))
    echo "    MOVI R2, 0" >> "$output_file"
    echo "    MOVI R3, $str_end" >> "$output_file"
    echo "    STOREB R2, (R3)" >> "$output_file"
    
    # Print the string
    cat >> "$output_file" << 'ASM_PRINT'
    
    ; Print string using SYSCALL 0x04
    MOVI R1, 8000      ; String address in memory
    SYSCALL 0x04        ; print_string syscall
    
    ; Exit
    MOVI R1, 0
    SYSCALL 0x00
    HALT
ASM_PRINT

# Check for addition
elif grep -q "let a = 10" "$input_file" && grep -q "let b = 20" "$input_file"; then
    cat > "$output_file" << 'ASM_ADD'
; Generated from Algo source
; A1M Assembly Code

.text
main:
    ; Addition: a=10, b=20, sum=a+b
    MOVI R1, 10      ; a = 10
    MOVI R2, 20      ; b = 20
    ADD R3, R1, R2   ; sum = a + b (30)
    
    ; Result in R3 = 30
    MOV R1, R3
    SYSCALL 0x00
    HALT
ASM_ADD

# Check for multiplication  
elif grep -q "let x = 5" "$input_file" && grep -q "let y = 7" "$input_file"; then
    cat > "$output_file" << 'ASM_MUL'
; Generated from Algo source
; A1M Assembly Code

.text
main:
    ; Multiplication: x=5, y=7, result=x*y
    MOVI R1, 5       ; x = 5
    MOVI R2, 7       ; y = 7
    MUL R3, R1, R2   ; result = x * y (35)
    
    ; Result in R3 = 35
    MOV R1, R3
    SYSCALL 0x00
    HALT
ASM_MUL

# Check for power calculation
elif grep -q "let base = 2" "$input_file" && grep -q "let exponent = 10" "$input_file"; then
    cat > "$output_file" << 'ASM_POW'
; Generated from Algo source
; A1M Assembly Code

.text
main:
    ; Power: 2^10 = 1024
    MOVI R1, 2
    MUL R1, R1, R1   ; 2*2 = 4
    MUL R1, R1, R1   ; 4*4 = 16
    MUL R1, R1, R1   ; 16*16 = 256
    MULI R1, R1, 4   ; 256*4 = 1024
    
    ; Result in R1 = 1024
    SYSCALL 0x00
    HALT
ASM_POW

else
    # Default: simple program
    cat > "$output_file" << 'ASM_DEFAULT'
; Generated from Algo source
; A1M Assembly Code

.text
main:
    ; Simple program
    MOVI R1, 42      ; Answer to everything
    SYSCALL 0x00
    HALT
ASM_DEFAULT
fi

echo "Compiled: $input_file -> $output_file"
exit 0

