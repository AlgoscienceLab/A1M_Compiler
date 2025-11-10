CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = a1m-console
SRC = a1m_console.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo ""
	@echo "══════════════════════════════════════════════════"
	@echo "  A1M Console built successfully!"
	@echo "══════════════════════════════════════════════════"
	@echo ""
	@echo "Run with:"
	@echo "  ./console.sh                    - Interactive mode"
	@echo "  ./console.sh <file>             - Quick run mode"
	@echo ""

clean:
	rm -f $(TARGET)

.PHONY: all clean
