cmake_minimum_required(VERSION 3.10)

project(SnakeGame VERSION 1.0.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
set(SOURCES
	src/entity.cpp
	src/food.cpp
	src/snake_segment.cpp
	src/snake.cpp
	src/game_state.cpp
	src/wasd_input_handler.cpp
	src/terminal_renderer.cpp
	src/game_engine.cpp
	src/score_manager.cpp
	src/main.cpp
)

# Include directories
include_directories(include)

# Executable
add_executable(snake ${SOURCES})

# Compiler warnings
if(MSVC)
	target_compile_options(snake PRIVATE /W4)
else()
	target_compile_options(snake PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Platform-specific settings
if(WIN32)
	# Windows specific settings if needed
elseif(UNIX)
	# Unix specific settings if needed
	target_link_libraries(snake pthread)
endif()

# Print build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source files: ${SOURCES}")
