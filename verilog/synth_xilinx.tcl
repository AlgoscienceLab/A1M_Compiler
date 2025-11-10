# Xilinx Vivado Synthesis Script for A1M CPU
# Usage: vivado -mode batch -source synth_xilinx.tcl

# Create project
create_project a1m_cpu ./build/xilinx -part xc7a35tcpg236-1 -force

# Add source files
add_files {
    cpu/a1m_cpu.v
    cpu/control_unit.v
    cpu/alu.v
    cpu/register_file.v
    memory/memory.v
    top.v
}

# Add include directories
set_property include_dirs {cpu} [current_fileset]

# Set top module
set_property top a1m_top [current_fileset]

# Create clock constraint
create_clock -period 20.0 -name clk [get_ports clk]

# Synthesize
synth_design -top a1m_top -part xc7a35tcpg236-1

# Optimize
opt_design

# Place
place_design

# Route
route_design

# Generate reports
report_utilization -file ./build/xilinx/utilization.rpt
report_timing -file ./build/xilinx/timing.rpt
report_power -file ./build/xilinx/power.rpt

# Write bitstream
write_bitstream -force ./build/xilinx/a1m_cpu.bit

# Print summary
puts "\n========================================="
puts "Synthesis Complete!"
puts "========================================="
puts "Bitstream: ./build/xilinx/a1m_cpu.bit"
puts "Reports:"
puts "  - Utilization: ./build/xilinx/utilization.rpt"
puts "  - Timing:      ./build/xilinx/timing.rpt"
puts "  - Power:       ./build/xilinx/power.rpt"
puts "=========================================\n"
