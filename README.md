# Snake Game

A modern, terminal-based implementation of the classic Snake game, showcasing clean architecture, SOLID design principles, automated testing, and performance-conscious data structures.

## Overview

This repository contains the actively developed **C++ implementation** of Snake.

The project began as a procedural C implementation and was later refactored into a modern object-oriented architecture to explore software engineering concepts such as dependency injection, interface-driven design, testing, and maintainability.

The original C version is preserved in the `legacy-c` branch for historical reference and comparison, while all new development takes place on the main C++ codebase.

### Branches

| Branch     | Purpose                                             |
| ---------- | --------------------------------------------------- |
| `main`     | Active C++ development                              |
| `dev`      | Integration branch for new features and experiments |
| `legacy-c` | Archived procedural C implementation                |

The goal of the repository is not only to provide a playable Snake game, but also to document the evolution of software design from procedural programming to modern C++ architecture.

## Features

### Gameplay

* Real-time, non-blocking keyboard input
* Dynamic snake growth mechanics
* Collision detection (walls and self)
* WASD control scheme

### Architecture

* SOLID principles
* Dependency injection
* Interface-based design
* Strategy pattern
* Polymorphism
* Smart pointers
* Unit and integration testing

### Performance

* O(1) snake movement using `std::deque`
* O(1) board occupancy checks through grid synchronization
* Efficient memory management through RAII and smart pointers

## Getting Started

### Requirements

* C++17 compatible compiler
* GNU Make

### Build

```bash
make snake
./snake
```

### Run Tests

```bash
make test_unit test_integration
./test_unit
./test_integration
```

## Project Structure

```text
.
├── include/
├── src/
├── tests/
├── main.cpp
├── Makefile
├── README.md
└── LICENSE
```

### Main Components

| Component        | Responsibility                |
| ---------------- | ----------------------------- |
| GameController   | Game loop orchestration       |
| Board            | Game state management         |
| Snake            | Snake behavior and movement   |
| Food             | Food generation and placement |
| TerminalRenderer | Rendering                     |
| InputHandler     | Input processing              |
| ScoreManager     | Persistence                   |

## Legacy Implementation

The original procedural implementation written in C is maintained in the `legacy-c` branch.

It provides an interesting comparison point for studying:

* Procedural vs object-oriented design
* Manual vs automatic memory management
* Tight vs loose coupling
* Modular programming vs SOLID architecture
* Evolution of performance optimizations

## Educational Value

This project serves as a practical example of:

* Refactoring procedural code into modern C++
* Applying SOLID principles
* Designing testable software
* Using dependency injection and interfaces
* Balancing clean architecture with performance considerations
* Maintaining software evolution through version control history

## License

This project is licensed under the MIT License.

