// Simple Memory Module for A1M CPU
// Unified instruction and data memory

module memory #(
    parameter ADDR_WIDTH = 16,  // 64KB memory for simulation
    parameter DATA_WIDTH = 64
) (
    input wire clk,
    
    // Instruction memory port
    input wire [63:0] imem_addr,
    output reg [31:0] imem_data,
    input wire imem_read,
    
    // Data memory port
    input wire [63:0] dmem_addr,
    input wire [63:0] dmem_write_data,
    output reg [63:0] dmem_read_data,
    input wire dmem_read,
    input wire dmem_write
);

// Memory array (byte-addressable)
reg [7:0] mem_array [0:(1 << ADDR_WIDTH)-1];

integer i;

// Initialize memory
initial begin
    for (i = 0; i < (1 << ADDR_WIDTH); i = i + 1) begin
        mem_array[i] = 8'h0;
    end
end

// Instruction memory read (asynchronous, little-endian)
always @(*) begin
    if (imem_read && imem_addr[ADDR_WIDTH-1:0] < (1 << ADDR_WIDTH) - 3) begin
        imem_data = {mem_array[imem_addr[ADDR_WIDTH-1:0] + 3],
                     mem_array[imem_addr[ADDR_WIDTH-1:0] + 2],
                     mem_array[imem_addr[ADDR_WIDTH-1:0] + 1],
                     mem_array[imem_addr[ADDR_WIDTH-1:0]]};
    end else begin
        imem_data = 32'h0;
    end
end

// Data memory operations (synchronous for writes, asynchronous for reads)
always @(*) begin
    if (dmem_read && dmem_addr[ADDR_WIDTH-1:0] < (1 << ADDR_WIDTH) - 7) begin
        dmem_read_data = {mem_array[dmem_addr[ADDR_WIDTH-1:0] + 7],
                         mem_array[dmem_addr[ADDR_WIDTH-1:0] + 6],
                         mem_array[dmem_addr[ADDR_WIDTH-1:0] + 5],
                         mem_array[dmem_addr[ADDR_WIDTH-1:0] + 4],
                         mem_array[dmem_addr[ADDR_WIDTH-1:0] + 3],
                         mem_array[dmem_addr[ADDR_WIDTH-1:0] + 2],
                         mem_array[dmem_addr[ADDR_WIDTH-1:0] + 1],
                         mem_array[dmem_addr[ADDR_WIDTH-1:0]]};
    end else begin
        dmem_read_data = 64'h0;
    end
end

always @(posedge clk) begin
    if (dmem_write && dmem_addr[ADDR_WIDTH-1:0] < (1 << ADDR_WIDTH) - 7) begin
        mem_array[dmem_addr[ADDR_WIDTH-1:0]]     <= dmem_write_data[7:0];
        mem_array[dmem_addr[ADDR_WIDTH-1:0] + 1] <= dmem_write_data[15:8];
        mem_array[dmem_addr[ADDR_WIDTH-1:0] + 2] <= dmem_write_data[23:16];
        mem_array[dmem_addr[ADDR_WIDTH-1:0] + 3] <= dmem_write_data[31:24];
        mem_array[dmem_addr[ADDR_WIDTH-1:0] + 4] <= dmem_write_data[39:32];
        mem_array[dmem_addr[ADDR_WIDTH-1:0] + 5] <= dmem_write_data[47:40];
        mem_array[dmem_addr[ADDR_WIDTH-1:0] + 6] <= dmem_write_data[55:48];
        mem_array[dmem_addr[ADDR_WIDTH-1:0] + 7] <= dmem_write_data[63:56];
    end
end

// Task to load program into memory
task load_program;
    input [1023:0] filename;
    begin
        $readmemh(filename, mem_array);
    end
endtask

endmodule
