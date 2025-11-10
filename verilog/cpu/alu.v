// A1M ALU - Arithmetic Logic Unit
// 64-bit operations with flag generation

module alu (
    input wire [63:0] operand_a,    // First operand
    input wire [63:0] operand_b,    // Second operand
    input wire [3:0] alu_op,        // ALU operation code
    output reg [63:0] result,       // Result
    output reg zero_flag,           // Zero flag
    output reg carry_flag,          // Carry flag
    output reg overflow_flag,       // Overflow flag
    output reg negative_flag        // Negative flag
);

// ALU operation codes
localparam ALU_ADD  = 4'h0;
localparam ALU_SUB  = 4'h1;
localparam ALU_MUL  = 4'h2;
localparam ALU_DIV  = 4'h3;
localparam ALU_MOD  = 4'h4;
localparam ALU_AND  = 4'h5;
localparam ALU_OR   = 4'h6;
localparam ALU_XOR  = 4'h7;
localparam ALU_NOT  = 4'h8;
localparam ALU_SHL  = 4'h9;
localparam ALU_SHR  = 4'hA;
localparam ALU_SAR  = 4'hB;
localparam ALU_CMP  = 4'hC;

// Internal signals for overflow detection
wire [64:0] add_result;
wire [64:0] sub_result;
wire signed [63:0] signed_a, signed_b;

assign signed_a = operand_a;
assign signed_b = operand_b;
assign add_result = {1'b0, operand_a} + {1'b0, operand_b};
assign sub_result = {1'b0, operand_a} - {1'b0, operand_b};

always @(*) begin
    // Default flag values
    zero_flag = 1'b0;
    carry_flag = 1'b0;
    overflow_flag = 1'b0;
    negative_flag = 1'b0;
    result = 64'h0;
    
    case (alu_op)
        ALU_ADD: begin
            result = add_result[63:0];
            carry_flag = add_result[64];
            overflow_flag = (operand_a[63] == operand_b[63]) && 
                           (result[63] != operand_a[63]);
        end
        
        ALU_SUB: begin
            result = sub_result[63:0];
            carry_flag = sub_result[64];
            overflow_flag = (operand_a[63] != operand_b[63]) && 
                           (result[63] != operand_a[63]);
        end
        
        ALU_MUL: begin
            result = operand_a * operand_b;
            // Overflow if result doesn't fit in 64 bits
            overflow_flag = (operand_a != 0) && (result / operand_a != operand_b);
        end
        
        ALU_DIV: begin
            result = (operand_b != 0) ? operand_a / operand_b : 64'hFFFFFFFFFFFFFFFF;
        end
        
        ALU_MOD: begin
            result = (operand_b != 0) ? operand_a % operand_b : 64'h0;
        end
        
        ALU_AND: begin
            result = operand_a & operand_b;
        end
        
        ALU_OR: begin
            result = operand_a | operand_b;
        end
        
        ALU_XOR: begin
            result = operand_a ^ operand_b;
        end
        
        ALU_NOT: begin
            result = ~operand_a;
        end
        
        ALU_SHL: begin
            result = operand_a << operand_b[5:0];  // Max shift 63
            if (operand_b[5:0] != 0)
                carry_flag = operand_a[64 - operand_b[5:0]];
        end
        
        ALU_SHR: begin
            result = operand_a >> operand_b[5:0];
            if (operand_b[5:0] != 0)
                carry_flag = operand_a[operand_b[5:0] - 1];
        end
        
        ALU_SAR: begin
            result = signed_a >>> operand_b[5:0];  // Arithmetic shift
        end
        
        ALU_CMP: begin
            result = sub_result[63:0];  // Same as SUB but don't store
            carry_flag = sub_result[64];
            overflow_flag = (operand_a[63] != operand_b[63]) && 
                           (result[63] != operand_a[63]);
        end
        
        default: begin
            result = 64'h0;
        end
    endcase
    
    // Update zero and negative flags
    zero_flag = (result == 64'h0);
    negative_flag = result[63];
end

endmodule
