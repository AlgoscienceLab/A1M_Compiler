# A1M CPU Timing Constraints
# Xilinx Design Constraints (XDC) format

# Clock Definition
# 50 MHz system clock (20ns period)
create_clock -period 20.000 -name sys_clk [get_ports clk]

# Clock uncertainty (jitter, etc.)
set_clock_uncertainty 0.500 [get_clocks sys_clk]

# Input delays (relative to clock)
set_input_delay -clock sys_clk -max 2.0 [get_ports reset]
set_input_delay -clock sys_clk -min 1.0 [get_ports reset]

# Output delays
set_output_delay -clock sys_clk -max 3.0 [get_ports halted]
set_output_delay -clock sys_clk -min 1.0 [get_ports halted]
set_output_delay -clock sys_clk -max 3.0 [get_ports pc]
set_output_delay -clock sys_clk -min 1.0 [get_ports pc]

# False paths (asynchronous signals)
set_false_path -from [get_ports reset] -to [all_registers]

# Multicycle paths (if any)
# Example: Memory access takes 2 cycles
# set_multicycle_path -setup 2 -from [get_cells cpu/ex_mem_*] -to [get_cells mem/*]

# Maximum delay constraints
set_max_delay 15.0 -from [get_cells cpu/id_ex_*] -to [get_cells cpu/ex_mem_*]

# Pipeline register optimization
set_property ASYNC_REG TRUE [get_cells cpu/if_id_*]
set_property ASYNC_REG TRUE [get_cells cpu/id_ex_*]
set_property ASYNC_REG TRUE [get_cells cpu/ex_mem_*]
set_property ASYNC_REG TRUE [get_cells cpu/mem_wb_*]

# Timing exceptions for debug signals
set_false_path -to [get_ports syscall_active]
set_false_path -to [get_ports syscall_num]
set_false_path -to [get_ports syscall_arg]

# I/O standards (example for Artix-7)
# Uncomment and modify for your board
# set_property IOSTANDARD LVCMOS33 [get_ports clk]
# set_property IOSTANDARD LVCMOS33 [get_ports reset]
# set_property IOSTANDARD LVCMOS33 [get_ports halted]

# Pin assignments (example for Artix-7 on Basys3 board)
# Uncomment and modify for your board
# set_property PACKAGE_PIN W5 [get_ports clk]
# set_property PACKAGE_PIN U18 [get_ports reset]
# set_property PACKAGE_PIN U16 [get_ports halted]

# Configuration settings
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 33 [current_design]
set_property CONFIG_MODE SPIx4 [current_design]
