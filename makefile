# Compiler and flags
CXX := g++

# Libraries to link
LIBS := 

# Source files
SRCS := src/main.cpp src/utils.cpp src/terminal_input.cpp src/word_machine.cpp src/visuals.cpp  src/game.cpp include/main.h include/utils.h include/terminal_input.h include/word_machine.h include/visuals.h include/game.h

# Build directory
BUILD_DIR := build

# Object files (place in build/)
OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(filter %.cpp,$(SRCS))) \
        $(patsubst libs/%.c,$(BUILD_DIR)/%.o,$(filter %.c,$(SRCS)))

# Target executable
TARGET := $(BUILD_DIR)/cli-wordle

all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Compile C++ source files to object files and emit assembly
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files to object files
$(BUILD_DIR)/%.o: libs/%.c | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
