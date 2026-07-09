# Snake Game Makefile
# Author: Miguel Mochizuki Silva
# Description: Makefile to orchestrate CMake build process

# Directories
BUILD_DIR = build
BIN_DIR = bin
DATA_DIR = data

# CMake options
CMAKE = cmake
CMAKE_BUILD_TYPE ?= Release
CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

# Executable path (CMake puts it in build/bin by default)
EXECUTABLE = $(BUILD_DIR)/bin/snake

# Colors for help output
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

# Default target
.PHONY: all
all: build-local

# Build local - Configure and build with CMake
.PHONY: build-local
build-local:
	@echo "$(BLUE)Configuring CMake...$(NC)"
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) $(CMAKE_FLAGS) ..
	@echo "$(BLUE)Building project...$(NC)"
	@$(MAKE) -C $(BUILD_DIR)
	@echo "$(GREEN)Build complete!$(NC)"
	@echo "$(GREEN)Executable: $(EXECUTABLE)$(NC)"

# Run local - Build and run the game
.PHONY: run-local
run-local: build-local
	@echo "$(GREEN)Running Snake Game...$(NC)"
	@$(EXECUTABLE)

# Clean local - Remove build artifacts
.PHONY: clean-local
clean-local:
	@echo "$(YELLOW)Cleaning build files...$(NC)"
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "$(YELLOW)Clean complete!$(NC)"

# Rebuild local - Clean and rebuild
.PHONY: rebuild-local
rebuild-local: clean-local build-local

# Help target
.PHONY: help
help:
	@echo "$(GREEN)Snake Game - Makefile Options$(NC)"
	@echo ""
	@echo "$(BLUE)Available targets:$(NC)"
	@echo "  $(GREEN)make build-local$(NC)    - Configure and build the game using CMake"
	@echo "  $(GREEN)make run-local$(NC)      - Build and run the game"
	@echo "  $(GREEN)make clean-local$(NC)    - Remove build directory and executable"
	@echo "  $(GREEN)make rebuild-local$(NC)  - Clean and rebuild the game"
	@echo "  $(GREEN)make help$(NC)           - Show this help message"
	@echo ""
	@echo "$(BLUE)Build options:$(NC)"
	@echo "  $(YELLOW)CMAKE_BUILD_TYPE=$(NC)   - Build type (Release, Debug, etc.)"
	@echo ""
	@echo "$(BLUE)Example usage:$(NC)"
	@echo "  $(YELLOW)make build-local$(NC)    - Build the game"
	@echo "  $(YELLOW)make run-local$(NC)      - Play the game"
	@echo "  $(YELLOW)make rebuild-local$(NC)  - Rebuild after changes"
	@echo "  $(YELLOW)make clean-local$(NC)    - Clean build files"
	@echo ""
