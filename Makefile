# Makefile

CXX ?= g++
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
DEBUG_DIR := debug

EXE := nxncube

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

BUILD_OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEBUG_OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(DEBUG_DIR)/%.o)

COMMON := -Wall -Werror -Wno-sign-compare -Wno-comment -pedantic -std=c++17 -I $(INCLUDE_DIR)

CXXFLAGS := $(COMMON)
DEBUG_FLAGS := $(COMMON) -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

all: $(BUILD_DIR)/$(EXE)
debug: $(DEBUG_DIR)/$(EXE)

$(BUILD_DIR)/$(EXE): $(BUILD_OBJS)
	$(CXX) $^ -o $@

$(DEBUG_DIR)/$(EXE): $(DEBUG_OBJS)
	$(CXX) $(DEBUG_FLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(DEBUG_FLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
$(DEBUG_DIR):
	mkdir -p $(DEBUG_DIR)

clean:
	rm -rf $(BUILD_DIR) $(DEBUG_DIR)

.PHONY: all debug clean