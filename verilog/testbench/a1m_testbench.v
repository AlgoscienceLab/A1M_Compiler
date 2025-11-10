// Testbench for A1M CPU
// Updated: November 9, 2025 - Added SYSCALL monitoring

`timescale 1ns/1ps

module a1m_testbench;

// Clock and reset
reg clk;
reg reset;

// Status signals
wire halted;
wire [63:0] pc;

// SYSCALL monitoring
wire syscall_active;
wire [13:0] syscall_num;
wire [63:0] syscall_arg;

// Instantiate top-level module
a1m_top dut (
    .clk(clk),
    .reset(reset),
    .halted(halted),
    .pc(pc),
    .syscall_active(syscall_active),
    .syscall_num(syscall_num),
    .syscall_arg(syscall_arg)
);

// Clock generation (50MHz)
initial begin
    clk = 0;
    forever #10 clk = ~clk;  // 20ns period
end

// SYSCALL monitoring
always @(posedge clk) begin
    if (syscall_active) begin
        case (syscall_num)
            14'h00: $display("[SYSCALL 0x00] Exit with code %0d", syscall_arg);
            14'h01: $display("[SYSCALL 0x01] Print integer: %0d", syscall_arg);
            14'h02: $display("[SYSCALL 0x02] Print char: '%c' (0x%h)", syscall_arg[7:0], syscall_arg[7:0]);
            14'h03: $display("[SYSCALL 0x03] Read integer");
            14'h04: $display("[SYSCALL 0x04] Print string at address 0x%h", syscall_arg);
            default: $display("[SYSCALL 0x%h] Unknown syscall with arg 0x%h", syscall_num, syscall_arg);
        endcase
    end
end

// Test sequence
initial begin
    $dumpfile("a1m_cpu.vcd");
    $dumpvars(0, a1m_testbench);
    
    // Initialize
    reset = 1;
    #50;
    reset = 0;
    
    // Load test program
    $display("Loading test program...");
    dut.mem.load_program("program.hex");
    
    // Run until halt or timeout
    $display("Starting CPU execution...");
    #10000;
    
    if (halted) begin
        $display("CPU halted at PC = 0x%h", pc);
    end else begin
        $display("CPU still running at PC = 0x%h", pc);
    end
    
    // Display some register values
    $display("\nRegister File Contents:");
    $display("R1  = 0x%h", dut.cpu.regfile.registers[1]);
    $display("R2  = 0x%h", dut.cpu.regfile.registers[2]);
    $display("R3  = 0x%h", dut.cpu.regfile.registers[3]);
    $display("R31 = 0x%h", dut.cpu.regfile.registers[31]);
    
    $finish;
end

// Monitor important signals
initial begin
    $monitor("Time=%0t PC=0x%h Inst=0x%h Halted=%b", 
             $time, pc, dut.cpu.if_id_instruction, halted);
end

endmodule
