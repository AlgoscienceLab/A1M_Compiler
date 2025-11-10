// A1M Register File
// 32 64-bit general purpose registers
// R0 is hardwired to zero

module register_file (
    input wire clk,                 // Clock
    input wire reset,               // Reset signal
    input wire write_enable,        // Write enable
    input wire [4:0] read_addr1,    // Read address 1
    input wire [4:0] read_addr2,    // Read address 2
    input wire [4:0] write_addr,    // Write address
    input wire [63:0] write_data,   // Write data
    output reg [63:0] read_data1,   // Read data 1
    output reg [63:0] read_data2    // Read data 2
);

// 32 64-bit registers
reg [63:0] registers [0:31];

integer i;

// Initialize registers
initial begin
    for (i = 0; i < 32; i = i + 1) begin
        registers[i] = 64'h0;
    end
end

// Write logic (synchronous)
always @(posedge clk or posedge reset) begin
    if (reset) begin
        for (i = 0; i < 32; i = i + 1) begin
            registers[i] <= 64'h0;
        end
    end else if (write_enable && write_addr != 5'h0) begin
        // R0 is hardwired to zero, cannot be written
        registers[write_addr] <= write_data;
    end
end

// Read logic (asynchronous)
always @(*) begin
    // R0 always returns zero
    if (read_addr1 == 5'h0)
        read_data1 = 64'h0;
    else
        read_data1 = registers[read_addr1];
        
    if (read_addr2 == 5'h0)
        read_data2 = 64'h0;
    else
        read_data2 = registers[read_addr2];
end

endmodule
