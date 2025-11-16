# A1M CPU Verilog Makefile
# Supports: Linux, macOS, Windows (MSYS2/MinGW64)
# Supports simulation with Icarus Verilog and synthesis

# Detect operating system
ifeq ($(OS),Windows_NT)
    # Windows (MSYS2/MinGW64)
    DETECTED_OS := Windows
    EXE_EXT := .exe
    RM := del /Q /F
    NULL_DEVICE := NUL
    BACKGROUND :=
else
    DETECTED_OS := $(shell uname -s)
    EXE_EXT :=
    RM := rm -f
    NULL_DEVICE := /dev/null
    BACKGROUND := &
endif

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
SIM_OUT = a1m_sim$(EXE_EXT)
VCD_OUT = a1m_cpu.vcd

# Tools
IVERILOG = iverilog
VVP = vvp
GTKWAVE = gtkwave

# Compiler flags
IVERILOG_FLAGS = -g2012 -Wall
IVERILOG_INCLUDES = -I$(CPU_DIR) -I$(MEM_DIR)

# Simulation
.PHONY: all sim clean view help info

all: sim

# Compile simulation
$(SIM_OUT): $(ALL_SOURCES) $(TB_SOURCES)
	@echo "Compiling A1M CPU simulation on $(DETECTED_OS)..."
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
ifeq ($(OS),Windows_NT)
	@echo "Note: GTKWave should be installed and in PATH on Windows"
	@$(GTKWAVE) $(VCD_OUT) || echo "GTKWave not found. Install from http://gtkwave.sourceforge.net/"
else
	@$(GTKWAVE) $(VCD_OUT) $(BACKGROUND)
endif

# Syntax check only
check: $(ALL_SOURCES)
	@echo "Checking syntax on $(DETECTED_OS)..."
	$(IVERILOG) $(IVERILOG_FLAGS) $(IVERILOG_INCLUDES) \
		-t null -o $(NULL_DEVICE) \
		$(ALL_SOURCES) $(TB_SOURCES)
	@echo "Syntax check passed!"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
ifeq ($(OS),Windows_NT)
	@if exist "$(SIM_OUT)" $(RM) "$(SIM_OUT)"
	@if exist "$(VCD_OUT)" $(RM) "$(VCD_OUT)"
	@if exist "*.vcd" $(RM) "*.vcd"
	@if exist "*.lxt" $(RM) "*.lxt"
	@if exist "*.lx2" $(RM) "*.lx2"
else
	@$(RM) $(SIM_OUT) $(VCD_OUT) 2>/dev/null || true
	@$(RM) *.vcd *.lxt *.lx2 2>/dev/null || true
endif
	@echo "Clean complete!"

# Help
help:
	@echo "A1M CPU Verilog Makefile ($(DETECTED_OS))"
	@echo ""
	@echo "Targets:"
	@echo "  all      - Compile and run simulation (default)"
	@echo "  sim      - Compile and run simulation"
	@echo "  check    - Syntax check only"
	@echo "  view     - Open waveform viewer"
	@echo "  clean    - Remove build artifacts"
	@echo "  info     - Show system information"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make              # Compile and simulate"
	@echo "  make check        # Check syntax only"
	@echo "  make sim view     # Simulate and view waveforms"
	@echo ""

info:
	@echo "Detected OS: $(DETECTED_OS)"
	@echo "Icarus Verilog: $(IVERILOG)"
	@echo "VVP: $(VVP)"
	@echo "GTKWave: $(GTKWAVE)"
	@echo "Simulation output: $(SIM_OUT)"

# Synthesis targets (for specific tools)
.PHONY: synth-xilinx synth-intel

synth-xilinx:
	@echo "Xilinx synthesis requires Vivado or ISE"
	@echo "Use: vivado -mode batch -source synth_xilinx.tcl"

synth-intel:
	@echo "Intel synthesis requires Quartus"
	@echo "Use: quartus_sh --flow compile a1m_cpu"

