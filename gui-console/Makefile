# Makefile for A1M Console
# Supports: Linux, macOS, Windows (MSYS2/MinGW64)

# Detect operating system
ifeq ($(OS),Windows_NT)
    # Windows (MSYS2/MinGW64)
    DETECTED_OS := Windows
    EXE_EXT := .exe
    RM := del /Q /F
    SHELL_SCRIPT := console.bat
else
    DETECTED_OS := $(shell uname -s)
    EXE_EXT :=
    RM := rm -f
    SHELL_SCRIPT := console.sh
endif

CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = a1m-console$(EXE_EXT)
SRC = a1m_console.c

.PHONY: all clean info install uninstall

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo ""
	@echo "══════════════════════════════════════════════════"
	@echo "  A1M Console built successfully for $(DETECTED_OS)!"
	@echo "══════════════════════════════════════════════════"
	@echo ""
	@echo "Run with:"
ifeq ($(OS),Windows_NT)
	@echo "  $(SHELL_SCRIPT)                    - Interactive mode"
	@echo "  $(SHELL_SCRIPT) <file>             - Quick run mode"
else
	@echo "  ./$(SHELL_SCRIPT)                  - Interactive mode"
	@echo "  ./$(SHELL_SCRIPT) <file>           - Quick run mode"
endif
	@echo ""

clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(TARGET)" $(RM) "$(TARGET)"
else
	@$(RM) $(TARGET) 2>/dev/null || true
endif
	@echo "Cleaned build files"

# Installation paths
ifeq ($(OS),Windows_NT)
	PREFIX ?= /usr/local
	INSTALL_DIR = $(PREFIX)/bin
	INSTALL = install -m 755
else ifeq ($(DETECTED_OS),Darwin)
	PREFIX ?= /usr/local
	INSTALL_DIR = $(PREFIX)/bin
	INSTALL = install -m 755
else
	PREFIX ?= /usr/local
	INSTALL_DIR = $(PREFIX)/bin
	INSTALL = install -m 755
endif

install: $(TARGET)
	@echo "Installing $(TARGET) to $(INSTALL_DIR)..."
ifeq ($(OS),Windows_NT)
	@mkdir -p $(INSTALL_DIR)
	@cp $(TARGET) $(INSTALL_DIR)/
	@echo "Installed $(TARGET) to $(INSTALL_DIR)"
	@echo "Make sure $(INSTALL_DIR) is in your PATH"
else
	@mkdir -p $(INSTALL_DIR)
	@$(INSTALL) $(TARGET) $(INSTALL_DIR)/
	@echo "Installed $(TARGET) to $(INSTALL_DIR)"
endif

uninstall:
	@echo "Uninstalling $(TARGET) from $(INSTALL_DIR)..."
ifeq ($(OS),Windows_NT)
	@if exist "$(INSTALL_DIR)/$(TARGET)" $(RM) "$(INSTALL_DIR)/$(TARGET)"
else
	@$(RM) $(INSTALL_DIR)/$(TARGET)
endif
	@echo "Uninstalled $(TARGET)"

info:
	@echo "Detected OS: $(DETECTED_OS)"
	@echo "Compiler: $(CC)"
	@echo "Target: $(TARGET)"
	@echo "Install Dir: $(INSTALL_DIR)"
