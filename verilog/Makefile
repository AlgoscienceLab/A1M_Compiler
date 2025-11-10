# A1M CPU Verilog Makefile
# Supports simulation with Icarus Verilog and synthesis

# Directories
SRC_DIR = .
CPU_DIR = $(SRC_DIR)/cpu
MEM_DIR = $(SRC_DIR)/memory
TB_DIR = $(SRC_DIR)/testbench

# Source files
CPU_SOURCES = $(CPU_DIR)/a1m_cpu.v \
              $(CPU_DIR)/control_unit.v \
              $(CPU_DIR)/alu.v \
              $(CPU_DIR)/register_file.v

MEM_SOURCES = $(MEM_DIR)/memory.v

TOP_SOURCES = $(SRC_DIR)/top.v

TB_SOURCES = $(TB_DIR)/a1m_testbench.v

ALL_SOURCES = $(CPU_SOURCES) $(MEM_SOURCES) $(TOP_SOURCES)

# Output files
SIM_OUT = a1m_sim
VCD_OUT = a1m_cpu.vcd

# Tools
IVERILOG = iverilog
VVP = vvp
GTKWAVE = gtkwave

# Compiler flags
IVERILOG_FLAGS = -g2012 -Wall
IVERILOG_INCLUDES = -I$(CPU_DIR) -I$(MEM_DIR)

# Simulation
.PHONY: all sim clean view help

all: sim

# Compile simulation
$(SIM_OUT): $(ALL_SOURCES) $(TB_SOURCES)
	@echo "Compiling A1M CPU simulation..."
	$(IVERILOG) $(IVERILOG_FLAGS) $(IVERILOG_INCLUDES) \
		-o $(SIM_OUT) \
		$(ALL_SOURCES) $(TB_SOURCES)
	@echo "Compilation complete: $(SIM_OUT)"

# Run simulation
sim: $(SIM_OUT)
	@echo "Running simulation..."
	$(VVP) $(SIM_OUT)
	@echo "Simulation complete. Waveform: $(VCD_OUT)"

# View waveforms
view: $(VCD_OUT)
	@echo "Opening waveform viewer..."
	$(GTKWAVE) $(VCD_OUT) &

# Syntax check only
check: $(ALL_SOURCES)
	@echo "Checking syntax..."
	$(IVERILOG) $(IVERILOG_FLAGS) $(IVERILOG_INCLUDES) \
		-t null -o /dev/null \
		$(ALL_SOURCES) $(TB_SOURCES)
	@echo "Syntax check passed!"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(SIM_OUT) $(VCD_OUT)
	rm -f *.vcd *.lxt *.lx2
	@echo "Clean complete!"

# Help
help:
	@echo "A1M CPU Verilog Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  all      - Compile and run simulation (default)"
	@echo "  sim      - Compile and run simulation"
	@echo "  check    - Syntax check only"
	@echo "  view     - Open waveform viewer"
	@echo "  clean    - Remove build artifacts"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make              # Compile and simulate"
	@echo "  make check        # Check syntax only"
	@echo "  make sim view     # Simulate and view waveforms"
	@echo ""

# Synthesis targets (for specific tools)
.PHONY: synth-xilinx synth-intel

synth-xilinx:
	@echo "Xilinx synthesis requires Vivado or ISE"
	@echo "Use: vivado -mode batch -source synth_xilinx.tcl"

synth-intel:
	@echo "Intel synthesis requires Quartus"
	@echo "Use: quartus_sh --flow compile a1m_cpu"

