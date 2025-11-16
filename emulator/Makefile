# Makefile for A1M Emulator
# Supports: Linux, macOS, Windows (MSYS2/MinGW64)

# Detect operating system
ifeq ($(OS),Windows_NT)
    # Windows (MSYS2/MinGW64)
    DETECTED_OS := Windows
    EXE_EXT := .exe
    RM := del /Q /F
    RMDIR := rmdir /S /Q
    MKDIR := if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
    FIXPATH = $(subst /,\,$1)
    RUN_PREFIX :=
else
    DETECTED_OS := $(shell uname -s)
    EXE_EXT :=
    RM := rm -f
    RMDIR := rm -rf
    MKDIR := mkdir -p $(OBJ_DIR)
    FIXPATH = $1
    RUN_PREFIX := ./
endif

CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS = 
TARGET = a1m-emu$(EXE_EXT)

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean run info install uninstall

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Built $(TARGET) for $(DETECTED_OS)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(call FIXPATH,$(OBJ_DIR))" $(RMDIR) "$(call FIXPATH,$(OBJ_DIR))"
	@if exist "$(TARGET)" $(RM) "$(TARGET)"
else
	@$(RMDIR) $(OBJ_DIR) 2>/dev/null || true
	@$(RM) $(TARGET) 2>/dev/null || true
endif
	@echo "Cleaned build files"

run: $(TARGET)
	$(RUN_PREFIX)$(TARGET)

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
	@echo "Sources: $(SOURCES)"
