// A1M CPU Core - 5-stage pipeline
// Stages: Fetch, Decode, Execute, Memory, Writeback
// Updated: November 9, 2025 - Added SYSCALL support

module a1m_cpu (
    input wire clk,                 // Clock
    input wire reset,               // Reset signal
    
    // Instruction memory interface
    output wire [63:0] imem_addr,
    input wire [31:0] imem_data,
    output wire imem_read,
    
    // Data memory interface
    output wire [63:0] dmem_addr,
    output wire [63:0] dmem_write_data,
    input wire [63:0] dmem_read_data,
    output wire dmem_read,
    output wire dmem_write,
    
    // SYSCALL interface
    output reg syscall_active,
    output reg [13:0] syscall_num,
    output reg [63:0] syscall_arg,
    input wire [63:0] syscall_result,
    input wire syscall_done,
    
    // Status outputs
    output wire halted,
    output wire [63:0] pc_out
);

// ========== Pipeline Registers ==========

// IF/ID Pipeline Register
reg [31:0] if_id_instruction;
reg [63:0] if_id_pc;

// ID/EX Pipeline Register
reg [7:0] id_ex_opcode;
reg [4:0] id_ex_rd, id_ex_rs1, id_ex_rs2;
reg [13:0] id_ex_immediate;
reg [23:0] id_ex_jump_addr;
reg [63:0] id_ex_reg_data1, id_ex_reg_data2;
reg [63:0] id_ex_pc;
reg id_ex_reg_write, id_ex_mem_read, id_ex_mem_write;
reg [3:0] id_ex_alu_op;
reg id_ex_alu_src;
reg [1:0] id_ex_mem_to_reg;
reg id_ex_branch, id_ex_jump;

// EX/MEM Pipeline Register
reg [4:0] ex_mem_rd;
reg [63:0] ex_mem_alu_result;
reg [63:0] ex_mem_reg_data2;
reg [63:0] ex_mem_pc;
reg ex_mem_reg_write, ex_mem_mem_read, ex_mem_mem_write;
reg [1:0] ex_mem_mem_to_reg;
reg ex_mem_zero_flag, ex_mem_carry_flag, ex_mem_overflow_flag, ex_mem_negative_flag;
reg ex_mem_branch, ex_mem_jump;
reg [23:0] ex_mem_jump_addr;

// MEM/WB Pipeline Register
reg [4:0] mem_wb_rd;
reg [63:0] mem_wb_alu_result;
reg [63:0] mem_wb_mem_data;
reg [63:0] mem_wb_pc;
reg mem_wb_reg_write;
reg [1:0] mem_wb_mem_to_reg;

// ========== CPU State ==========
reg [63:0] pc;                      // Program counter
reg [63:0] flags;                   // Status flags register
reg halt_flag;                      // Halt flag
reg syscall_pending;                // SYSCALL in progress

// ========== Control Signals ==========
wire reg_write, mem_read, mem_write;
wire [3:0] alu_op;
wire alu_src, reg_dst, branch, jump;
wire [1:0] mem_to_reg;
wire halt_signal;
wire is_syscall;

// ========== Register File ==========
wire [63:0] reg_read_data1, reg_read_data2;
wire [4:0] reg_read_addr1, reg_read_addr2, reg_write_addr;
reg [63:0] reg_write_data;
wire reg_write_enable;

// ========== ALU Signals ==========
wire [63:0] alu_operand_a, alu_operand_b;
wire [63:0] alu_result;
wire alu_zero, alu_carry, alu_overflow, alu_negative;

// ========== Instruction Decode ==========
wire [7:0] opcode;
wire [4:0] rd, rs1, rs2;
wire [13:0] immediate;
wire [23:0] jump_address;

assign opcode = if_id_instruction[31:24];
assign rd = if_id_instruction[23:19];
assign rs1 = if_id_instruction[18:14];
assign rs2 = if_id_instruction[13:9];
assign immediate = if_id_instruction[13:0];
assign jump_address = if_id_instruction[23:0];

// Sign extend immediate
wire [63:0] immediate_extended;
assign immediate_extended = {{50{immediate[13]}}, immediate};

// Sign extend immediate for EX stage
wire [63:0] id_ex_immediate_extended;
assign id_ex_immediate_extended = {{50{id_ex_immediate[13]}}, id_ex_immediate};

// Detect SYSCALL instruction
assign is_syscall = (opcode == 8'h50);

// ========== Module Instantiations ==========

control_unit ctrl (
    .opcode(opcode),
    .reg_write(reg_write),
    .mem_read(mem_read),
    .mem_write(mem_write),
    .alu_op(alu_op),
    .alu_src(alu_src),
    .reg_dst(reg_dst),
    .branch(branch),
    .jump(jump),
    .mem_to_reg(mem_to_reg),
    .halt(halt_signal)
);

register_file regfile (
    .clk(clk),
    .reset(reset),
    .write_enable(mem_wb_reg_write),
    .read_addr1(rs1),
    .read_addr2(rs2),
    .write_addr(mem_wb_rd),
    .write_data(reg_write_data),
    .read_data1(reg_read_data1),
    .read_data2(reg_read_data2)
);

alu alu_unit (
    .operand_a(id_ex_reg_data1),
    .operand_b(id_ex_alu_src ? id_ex_immediate_extended : id_ex_reg_data2),
    .alu_op(id_ex_alu_op),
    .result(alu_result),
    .zero_flag(alu_zero),
    .carry_flag(alu_carry),
    .overflow_flag(alu_overflow),
    .negative_flag(alu_negative)
);

// ========== Writeback Mux ==========
always @(*) begin
    case (mem_wb_mem_to_reg)
        2'b00: reg_write_data = mem_wb_alu_result;
        2'b01: reg_write_data = mem_wb_mem_data;
        2'b10: reg_write_data = mem_wb_pc + 4;
        default: reg_write_data = mem_wb_alu_result;
    endcase
end

// ========== Instruction Fetch ==========
assign imem_addr = pc;
assign imem_read = ~halt_flag;
assign pc_out = pc;
assign halted = halt_flag;

// ========== Memory Stage ==========
assign dmem_addr = ex_mem_alu_result;
assign dmem_write_data = ex_mem_reg_data2;
assign dmem_read = ex_mem_mem_read;
assign dmem_write = ex_mem_mem_write;

// ========== Pipeline Control ==========
wire stall;
wire flush;
wire branch_taken;

// Branch decision
assign branch_taken = ex_mem_branch && 
                     ((ex_mem_jump_addr[0] && ex_mem_zero_flag) ||    // JZ
                      (!ex_mem_jump_addr[0] && !ex_mem_zero_flag));   // JNZ

// Hazard detection (simplified)
assign stall = (id_ex_mem_read && 
               ((id_ex_rd == rs1) || (id_ex_rd == rs2)));

assign flush = branch_taken || ex_mem_jump;

// ========== Pipeline Stages ==========

always @(posedge clk or posedge reset) begin
    if (reset) begin
        pc <= 64'h0000000000001000;  // Reset vector
        halt_flag <= 1'b0;
        flags <= 64'h0;
        syscall_pending <= 1'b0;
        syscall_active <= 1'b0;
        syscall_num <= 14'h0;
        syscall_arg <= 64'h0;
        
        // Clear pipeline registers
        if_id_instruction <= 32'h0;
        if_id_pc <= 64'h0;
        
        id_ex_opcode <= 8'h0;
        id_ex_rd <= 5'h0;
        id_ex_rs1 <= 5'h0;
        id_ex_rs2 <= 5'h0;
        id_ex_immediate <= 14'h0;
        id_ex_jump_addr <= 24'h0;
        id_ex_reg_data1 <= 64'h0;
        id_ex_reg_data2 <= 64'h0;
        id_ex_pc <= 64'h0;
        id_ex_reg_write <= 1'b0;
        id_ex_mem_read <= 1'b0;
        id_ex_mem_write <= 1'b0;
        id_ex_alu_op <= 4'h0;
        id_ex_alu_src <= 1'b0;
        id_ex_mem_to_reg <= 2'b00;
        id_ex_branch <= 1'b0;
        id_ex_jump <= 1'b0;
        
        ex_mem_rd <= 5'h0;
        ex_mem_alu_result <= 64'h0;
        ex_mem_reg_data2 <= 64'h0;
        ex_mem_pc <= 64'h0;
        ex_mem_reg_write <= 1'b0;
        ex_mem_mem_read <= 1'b0;
        ex_mem_mem_write <= 1'b0;
        ex_mem_mem_to_reg <= 2'b00;
        ex_mem_zero_flag <= 1'b0;
        ex_mem_branch <= 1'b0;
        ex_mem_jump <= 1'b0;
        ex_mem_jump_addr <= 24'h0;
        
        mem_wb_rd <= 5'h0;
        mem_wb_alu_result <= 64'h0;
        mem_wb_mem_data <= 64'h0;
        mem_wb_pc <= 64'h0;
        mem_wb_reg_write <= 1'b0;
        mem_wb_mem_to_reg <= 2'b00;
        
    end else if (!halt_flag) begin
        
        // ========== SYSCALL Handling ==========
        if (syscall_pending) begin
            if (syscall_done) begin
                syscall_active <= 1'b0;
                syscall_pending <= 1'b0;
                // Result available in syscall_result if needed
            end
        end else if (is_syscall && !stall) begin
            // Initiate SYSCALL
            syscall_active <= 1'b1;
            syscall_pending <= 1'b1;
            syscall_num <= immediate;
            syscall_arg <= reg_read_data1;  // R1 contains argument
        end
        
        // ========== Fetch Stage ==========
        if (!stall && !syscall_pending) begin
            if (branch_taken) begin
                pc <= ex_mem_pc + {{40{ex_mem_jump_addr[23]}}, ex_mem_jump_addr} << 2;
            end else if (ex_mem_jump) begin
                // Check if RET instruction (opcode from EX/MEM stage would be needed)
                // For now, use jump address for all jumps
                pc <= ex_mem_pc + {{40{ex_mem_jump_addr[23]}}, ex_mem_jump_addr} << 2;
            end else begin
                pc <= pc + 4;
            end
            
            if_id_instruction <= flush ? 32'h0 : imem_data;
            if_id_pc <= pc;
        end
        
        // ========== Decode Stage ==========
        if (!stall) begin
            id_ex_opcode <= flush ? 8'h0 : opcode;
            id_ex_rd <= rd;
            id_ex_rs1 <= rs1;
            id_ex_rs2 <= rs2;
            id_ex_immediate <= immediate;
            id_ex_jump_addr <= jump_address;
            id_ex_reg_data1 <= reg_read_data1;
            id_ex_reg_data2 <= reg_read_data2;
            id_ex_pc <= if_id_pc;
            id_ex_reg_write <= reg_write;
            id_ex_mem_read <= mem_read;
            id_ex_mem_write <= mem_write;
            id_ex_alu_op <= alu_op;
            id_ex_alu_src <= alu_src;
            id_ex_mem_to_reg <= mem_to_reg;
            id_ex_branch <= branch;
            id_ex_jump <= jump;
            
            if (halt_signal) begin
                halt_flag <= 1'b1;
            end
        end
        
        // ========== Execute Stage ==========
        ex_mem_rd <= id_ex_rd;
        ex_mem_alu_result <= alu_result;
        ex_mem_reg_data2 <= id_ex_reg_data2;
        ex_mem_pc <= id_ex_pc;
        ex_mem_reg_write <= id_ex_reg_write;
        ex_mem_mem_read <= id_ex_mem_read;
        ex_mem_mem_write <= id_ex_mem_write;
        ex_mem_mem_to_reg <= id_ex_mem_to_reg;
        ex_mem_zero_flag <= alu_zero;
        ex_mem_carry_flag <= alu_carry;
        ex_mem_overflow_flag <= alu_overflow;
        ex_mem_negative_flag <= alu_negative;
        ex_mem_branch <= id_ex_branch;
        ex_mem_jump <= id_ex_jump;
        ex_mem_jump_addr <= id_ex_jump_addr;
        
        // Update flags
        flags[0] <= alu_zero;
        flags[1] <= alu_carry;
        flags[2] <= alu_overflow;
        flags[3] <= alu_negative;
        
        // ========== Memory Stage ==========
        mem_wb_rd <= ex_mem_rd;
        mem_wb_alu_result <= ex_mem_alu_result;
        mem_wb_mem_data <= dmem_read_data;
        mem_wb_pc <= ex_mem_pc;
        mem_wb_reg_write <= ex_mem_reg_write;
        mem_wb_mem_to_reg <= ex_mem_mem_to_reg;
        
        // ========== Writeback Stage ==========
        // (handled by register file write)
    end
end

endmodule
