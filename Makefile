# XCBase Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = xcbase
SOURCE = xc_improved.cpp
HEADER = pch_fixed.h
LEGACY_SOURCE = xc_fixed.cpp

# Default target
$(TARGET): $(SOURCE) $(HEADER)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

# Legacy version
legacy: $(LEGACY_SOURCE) $(HEADER)
	$(CXX) $(CXXFLAGS) $(LEGACY_SOURCE) -o $(TARGET)_legacy

# Clean target
clean:
	rm -f $(TARGET) $(TARGET)_legacy report.txt log.txt key.txt

# Test target
test: $(TARGET)
	@echo "Running basic tests..."
	@echo -e "1\nHello" | ./$(TARGET)
	@echo "Encrypted: $$(cat report.txt)"
	@echo -e "2\n$$(cat report.txt)" | ./$(TARGET)
	@echo "Decrypted: $$(cat report.txt)"
	@echo -e "4\nSecureTest" | ./$(TARGET)
	@echo "Secure key: $$(cat key.txt)"

# Install target (optional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: clean test install legacy