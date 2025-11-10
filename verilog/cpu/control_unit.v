// A1M Control Unit
// Generates control signals based on instruction opcode

module control_unit (
    input wire [7:0] opcode,        // Instruction opcode
    output reg reg_write,           // Register write enable
    output reg mem_read,            // Memory read enable
    output reg mem_write,           // Memory write enable
    output reg [3:0] alu_op,        // ALU operation
    output reg alu_src,             // ALU source (0=reg, 1=imm)
    output reg reg_dst,             // Register destination
    output reg branch,              // Branch instruction
    output reg jump,                // Jump instruction
    output reg [1:0] mem_to_reg,    // Memory to register (0=alu, 1=mem, 2=pc+4)
    output reg halt                 // Halt signal
);

// Import ALU operation codes
`include "alu_ops.vh"

always @(*) begin
    // Default values
    reg_write = 1'b0;
    mem_read = 1'b0;
    mem_write = 1'b0;
    alu_op = 4'h0;
    alu_src = 1'b0;
    reg_dst = 1'b0;
    branch = 1'b0;
    jump = 1'b0;
    mem_to_reg = 2'b00;
    halt = 1'b0;
    
    case (opcode)
        8'h00: begin // NOP
            // No operation
        end
        
        8'h01: begin // HALT
            halt = 1'b1;
        end
        
        8'h02: begin // ADD
            reg_write = 1'b1;
            alu_op = ALU_ADD;
            alu_src = 1'b0;
        end
        
        8'h03: begin // ADDI
            reg_write = 1'b1;
            alu_op = ALU_ADD;
            alu_src = 1'b1;
        end
        
        8'h04: begin // SUB
            reg_write = 1'b1;
            alu_op = ALU_SUB;
            alu_src = 1'b0;
        end
        
        8'h05: begin // SUBI
            reg_write = 1'b1;
            alu_op = ALU_SUB;
            alu_src = 1'b1;
        end
        
        8'h06: begin // MUL
            reg_write = 1'b1;
            alu_op = ALU_MUL;
            alu_src = 1'b0;
        end
        
        8'h07: begin // MULI
            reg_write = 1'b1;
            alu_op = ALU_MUL;
            alu_src = 1'b1;
        end
        
        8'h08: begin // DIV
            reg_write = 1'b1;
            alu_op = ALU_DIV;
            alu_src = 1'b0;
        end
        
        8'h09: begin // DIVI
            reg_write = 1'b1;
            alu_op = ALU_DIV;
            alu_src = 1'b1;
        end
        
        8'h0A: begin // MOD
            reg_write = 1'b1;
            alu_op = ALU_MOD;
            alu_src = 1'b0;
        end
        
        8'h0B: begin // MODI
            reg_write = 1'b1;
            alu_op = ALU_MOD;
            alu_src = 1'b1;
        end
        
        8'h0C: begin // AND
            reg_write = 1'b1;
            alu_op = ALU_AND;
            alu_src = 1'b0;
        end
        
        8'h0D: begin // ANDI
            reg_write = 1'b1;
            alu_op = ALU_AND;
            alu_src = 1'b1;
        end
        
        8'h0E: begin // OR
            reg_write = 1'b1;
            alu_op = ALU_OR;
            alu_src = 1'b0;
        end
        
        8'h0F: begin // ORI
            reg_write = 1'b1;
            alu_op = ALU_OR;
            alu_src = 1'b1;
        end
        
        8'h10: begin // XOR
            reg_write = 1'b1;
            alu_op = ALU_XOR;
            alu_src = 1'b0;
        end
        
        8'h11: begin // XORI
            reg_write = 1'b1;
            alu_op = ALU_XOR;
            alu_src = 1'b1;
        end
        
        8'h12: begin // NOT
            reg_write = 1'b1;
            alu_op = ALU_NOT;
            alu_src = 1'b0;
        end
        
        8'h13: begin // SHL
            reg_write = 1'b1;
            alu_op = ALU_SHL;
            alu_src = 1'b0;
        end
        
        8'h14: begin // SHLI
            reg_write = 1'b1;
            alu_op = ALU_SHL;
            alu_src = 1'b1;
        end
        
        8'h15: begin // SHR
            reg_write = 1'b1;
            alu_op = ALU_SHR;
            alu_src = 1'b0;
        end
        
        8'h16: begin // SHRI
            reg_write = 1'b1;
            alu_op = ALU_SHR;
            alu_src = 1'b1;
        end
        
        8'h17: begin // SAR
            reg_write = 1'b1;
            alu_op = ALU_SAR;
            alu_src = 1'b0;
        end
        
        8'h18: begin // SARI
            reg_write = 1'b1;
            alu_op = ALU_SAR;
            alu_src = 1'b1;
        end
        
        8'h19: begin // CMP
            alu_op = ALU_CMP;
            alu_src = 1'b0;
        end
        
        8'h1A: begin // CMPI
            alu_op = ALU_CMP;
            alu_src = 1'b1;
        end
        
        8'h20: begin // LOAD
            reg_write = 1'b1;
            mem_read = 1'b1;
            alu_op = ALU_ADD;
            alu_src = 1'b1;
            mem_to_reg = 2'b01;
        end
        
        8'h21: begin // STORE
            mem_write = 1'b1;
            alu_op = ALU_ADD;
            alu_src = 1'b1;
        end
        
        8'h30: begin // JMP
            jump = 1'b1;
        end
        
        8'h31: begin // JZ
            branch = 1'b1;
        end
        
        8'h32: begin // JNZ
            branch = 1'b1;
        end
        
        8'h39: begin // CALL
            reg_write = 1'b1;
            jump = 1'b1;
            mem_to_reg = 2'b10;  // Write PC+4 to R31
        end
        
        8'h3A: begin // RET
            jump = 1'b1;
        end
        
        8'h40: begin // MOV
            reg_write = 1'b1;
            alu_op = ALU_ADD;  // rd = rs1 + 0
            alu_src = 1'b0;
        end
        
        8'h41: begin // MOVI
            reg_write = 1'b1;
            alu_op = ALU_ADD;  // rd = 0 + imm
            alu_src = 1'b1;
        end
        
        8'h50: begin // SYSCALL
            // System call - handled by external system
            // No register write, no memory access
            // Flags may be set based on syscall result
        end
        
        default: begin
            // Unknown opcode - NOP behavior
        end
    endcase
end

endmodule
