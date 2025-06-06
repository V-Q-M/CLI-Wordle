# Compiler and flags for Linux
CXX := g++
CXXFLAGS := -fsanitize=address -O2 -Wall

# Compiler and flags for Windows (MinGW)
MINGW_CXX := x86_64-w64-mingw32-g++
MINGW_CXXFLAGS := -O2 -Wall
#MINGW_CXXFLAGS := -O2 -Wall -static -static-libgcc -static-libstdc++
# Libraries to link (add -l flags if needed)
LIBS := 

# Source files
SRCS := src/main.cpp src/utils.cpp src/terminal_input.cpp src/word_machine.cpp src/visuals.cpp src/game.cpp
HDRS := include/main.h include/utils.h include/terminal_input.h include/word_machine.h include/visuals.h include/game.h

# Build directories
BUILD_DIR_LINUX := build/linux
BUILD_DIR_WIN := build/win

# Object files for Linux
OBJS := $(patsubst src/%.cpp,$(BUILD_DIR_LINUX)/%.o,$(SRCS))

# Object files for Windows
OBJS_WIN := $(patsubst src/%.cpp,$(BUILD_DIR_WIN)/%.o,$(SRCS))

# Targets
TARGET := $(BUILD_DIR_LINUX)/cli-wordle
TARGET_WIN := $(BUILD_DIR_WIN)/cli-wordle.exe

# Default: build Linux executable
all: $(TARGET)

# Linux build
$(TARGET): $(OBJS) | $(BUILD_DIR_LINUX)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR_LINUX)/%.o: src/%.cpp | $(BUILD_DIR_LINUX)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR_LINUX):
	mkdir -p $(BUILD_DIR_LINUX)

# Windows build using MinGW
win: $(TARGET_WIN)

$(TARGET_WIN): $(OBJS_WIN) | $(BUILD_DIR_WIN)
	$(MINGW_CXX) $(MINGW_CXXFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR_WIN)/%.o: src/%.cpp | $(BUILD_DIR_WIN)
	$(MINGW_CXX) $(MINGW_CXXFLAGS) -c $< -o $@

$(BUILD_DIR_WIN):
	mkdir -p $(BUILD_DIR_WIN)

# Clean both builds
clean:
	rm -rf $(BUILD_DIR_LINUX) $(BUILD_DIR_WIN)

.PHONY: all clean win
