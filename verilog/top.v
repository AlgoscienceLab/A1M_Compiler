// Top-level module for A1M CPU system
// Updated: November 9, 2025 - Added SYSCALL interface

`timescale 1ns/1ps

module a1m_top (
    input wire clk,
    input wire reset,
    output wire halted,
    output wire [63:0] pc,
    
    // SYSCALL monitoring outputs (for testbench)
    output wire syscall_active,
    output wire [13:0] syscall_num,
    output wire [63:0] syscall_arg
);

// Instruction memory interface
wire [63:0] imem_addr;
wire [31:0] imem_data;
wire imem_read;

// Data memory interface
wire [63:0] dmem_addr;
wire [63:0] dmem_write_data;
wire [63:0] dmem_read_data;
wire dmem_read;
wire dmem_write;

// SYSCALL interface
wire [63:0] syscall_result;
wire syscall_done;

// Simple SYSCALL handler (always ready for now)
assign syscall_result = 64'h0;
assign syscall_done = syscall_active;  // Complete immediately

// CPU instantiation
a1m_cpu cpu (
    .clk(clk),
    .reset(reset),
    .imem_addr(imem_addr),
    .imem_data(imem_data),
    .imem_read(imem_read),
    .dmem_addr(dmem_addr),
    .dmem_write_data(dmem_write_data),
    .dmem_read_data(dmem_read_data),
    .dmem_read(dmem_read),
    .dmem_write(dmem_write),
    .syscall_active(syscall_active),
    .syscall_num(syscall_num),
    .syscall_arg(syscall_arg),
    .syscall_result(syscall_result),
    .syscall_done(syscall_done),
    .halted(halted),
    .pc_out(pc)
);

// Memory instantiation
memory #(
    .ADDR_WIDTH(16),
    .DATA_WIDTH(64)
) mem (
    .clk(clk),
    .imem_addr(imem_addr),
    .imem_data(imem_data),
    .imem_read(imem_read),
    .dmem_addr(dmem_addr),
    .dmem_write_data(dmem_write_data),
    .dmem_read_data(dmem_read_data),
    .dmem_read(dmem_read),
    .dmem_write(dmem_write)
);

endmodule
