# Snake Game

A modern, terminal-based implementation of the classic Snake game, showcasing clean architecture, SOLID design principles, and performance-conscious data structures.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Getting Started](#getting-started)
- [Project Structure](#project-structure)
- [Design Principles](#design-principles)
- [Performance Optimizations](#performance-optimizations)
- [Testing](#testing)
- [License](#license)

---

## Overview

This project demonstrates the evolution of software design through two implementations:

**C Legacy (Procedural):** Original modular implementation with separated concerns across board, snake, game logic, and terminal I/O modules.

**C++ Modern (Object-Oriented):** Complete refactoring following SOLID principles, featuring dependency injection, interface-based design, comprehensive test coverage, and **efficient O(1) operations** for critical game mechanics.

---

## Features

### Gameplay
- Real-time, non-blocking keyboard input
- Dynamic snake growth mechanics
- Collision detection (walls and self)
- WASD control scheme (extensible to other schemes)

### Persistence
- Best score tracking (`best_scores.txt`)
- Complete game history logging (`score_history.txt`)

### Technical Highlights
- **Smart pointers** for automatic memory management
- **Polymorphic entities** through abstract base classes
- **Strategy pattern** for input handling and rendering
- **Dependency injection** for loose coupling
- **Cross-platform support** (Windows and Unix/Linux)
- **Unit and integration tests** using Catch2 framework
- **O(1) snake movement** using `std::deque` (push_front/pop_back)
- **O(1) occupancy checks** using a 2D grid (eliminates O(n) loops in `Food::spawn`)

---

## Architecture

The C++ implementation follows a **layered architecture** with clear separation of concerns:

```
┌─────────────────────────────────────────┐
│         GameController (Orchestration)  │
├─────────────────────────────────────────┤
│  Board  │  Renderer  │  InputHandler    │
├─────────────────────────────────────────┤
│  Snake  │  Food  │  ScoreManager        │
├─────────────────────────────────────────┤
│  IBoard │  IRenderer │  IInputHandler   │
└─────────────────────────────────────────┘
```

### Key Components

| Component | Responsibility | Design Pattern |
|-----------|---------------|----------------|
| `GameController` | Game loop orchestration | Mediator |
| `Board` | Game state management & grid | Facade |
| `Snake` / `Food` | Entity logic with efficient data structures | Polymorphism (Entity base) |
| `TerminalRenderer` | Display logic | Strategy (IRenderer) |
| `WASDInputHandler` | Input processing | Strategy (IInputHandler) |
| `ScoreManager` | Persistence | Single Responsibility |

---

## Getting Started

### Prerequisites

**C Legacy:**
- GCC compiler
- ncurses library

**C++ Modern:**
- C++17 compatible compiler
- Make build system

### Building & Running

#### C++ Version (Recommended)

```bash
cd cpp
make snake
./snake
```

#### C Legacy Version

```bash
cd c_legacy
gcc -o snake -Iinclude src/*.c main.c -lncurses
./snake
```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move Up |
| `S` | Move Down |
| `A` | Move Left |
| `D` | Move Right |

Game ends on collision with walls or the snake's own body.

---

## Project Structure

### C++ Implementation

```
cpp/
├── include/                  # Header files
│   ├── board.hpp             # Game state manager (implements IBoard)
│   ├── constants.hpp         # Game configuration
│   ├── entity.hpp            # Abstract entity base class + EntityType enum
│   ├── food.hpp              # Food entity (extends Entity)
│   ├── game_controller.hpp   # Main game loop orchestrator
│   ├── iboard.hpp            # Board interface (DIP)
│   ├── input_handler.hpp     # Input strategy interface + WASD impl
│   ├── irenderer.hpp         # Renderer interface (DIP)
│   ├── score_manager.hpp     # Persistence handler
│   ├── snake.hpp             # Snake entity (extends Entity) with std::deque
│   └── terminal_renderer.hpp # Terminal rendering strategy
│
├── src/                      # Implementation files
│   ├── board.cpp
│   ├── food.cpp
│   ├── game_controller.cpp
│   ├── input_handler.cpp
│   ├── score_manager.cpp
│   ├── snake.cpp
│   └── terminal_renderer.cpp
│
├── tests/                    # Test suite
│   ├── test_unit.cpp         # Unit tests (18 assertions)
│   └── test_integration.cpp  # Integration tests (43 assertions)
│
├── main.cpp                  # Entry point (composition root)
├── Makefile                  # Build configuration
└── best_scores.txt           # Persistent high scores
```

### C Legacy Implementation

```
c_legacy/
├── include/
│   ├── board.h
│   ├── game.h
│   ├── snake.h
│   └── terminal.h
├── src/
│   ├── board.c
│   ├── game.c
│   ├── snake.c
│   └── terminal.c
└── main.c
```

---

## Design Principles (SOLID)

The C++ implementation strictly adheres to SOLID principles:

### Single Responsibility Principle

Each class has one clear purpose:

- `ScoreManager`: File I/O operations only
- `Board`: Game state management only
- `TerminalRenderer`: Display logic only
- `WASDInputHandler`: Input mapping only

**Before:** Board handled state + rendering + file I/O (3 responsibilities)
**After:** Separated into Board, TerminalRenderer, and ScoreManager

### Open/Closed Principle

New functionality via extension, not modification:

```cpp
// Add new control schemes without changing GameController
class ArrowKeysHandler : public IInputHandler { /* ... */ };
class GamepadHandler : public IInputHandler { /* ... */ };

// Add new rendering backends without changing game logic
class GUIRenderer : public IRenderer { /* ... */ };
class WebRenderer : public IRenderer { /* ... */ };
```

### Liskov Substitution Principle

Subclasses are fully substitutable:

- Any `Entity` subclass (`SnakeSegment`, `Food`) works polymorphically
- Any `IBoard` implementation can replace `Board` for entities
- Any `IRenderer` implementation works with `GameController`

### Interface Segregation Principle

Minimal, client-specific interfaces:

- `IBoard` has only 3 methods (what entities need)
- `IRenderer` has only 2 methods (clear, render)
- `IInputHandler` has only 1 method (processInput)

No client depends on methods it doesn't use.

### Dependency Inversion Principle

Depend on abstractions, not concretions:

```cpp
// High-level GameController depends on abstractions
GameController(std::shared_ptr<Board> board,
               std::shared_ptr<IInputHandler> inputHandler,
               std::shared_ptr<IRenderer> renderer);

// Low-level entities depend on IBoard interface
class Snake {
    IBoard* board_;  // Abstract interface, not concrete Board
};

// Composition root in main() wires dependencies
auto renderer = std::make_shared<TerminalRenderer>();
GameController game(board, inputHandler, renderer);
```

---

## Performance Optimizations

Recent refactors have dramatically improved runtime efficiency while preserving clean architecture:

### 1. O(1) Snake Movement with `std::deque`

**Before (std::vector):** Each move required shifting all segment positions (O(n)).
**After (std::deque):** Head insertion (`push_front`) and tail removal (`pop_back`) are O(1) amortized.

```cpp
segments_.emplace_front(std::make_unique<SnakeSegment>(newX, newY));
if (!shouldGrow_) segments_.pop_back();
```

### 2. O(1) Occupancy Checks via Grid

**Before (`isOccupied`):** Performed a linear scan over the snake's deque (O(n)) for every food spawn attempt (up to 1000 tries).
**After:** Direct access to the 2D `grid_` matrix (O(1)) makes food spawning virtually instant.

```cpp
bool Board::isOccupied(int x, int y) const {
    return grid_[y][x] != nullptr;  // O(1)
}
```

The grid is synchronized **before** food spawn, ensuring `isOccupied` sees the updated snake position.

### 3. Fast Type Identification with `EntityType` Enum

Replaces `dynamic_cast` with a lightweight virtual `getType()` method (O(1) integer comparison), useful for future extensions like power-ups.

### Design Trade-off

The self-collision check in `Snake::move` remains O(n) (loop over segments) to preserve encapsulation—the snake validates its own state without requiring the board to temporarily remove the tail. Given the board is at most 20x20 (400 cells), this is negligible in practice (microseconds per frame).

---

## Testing

Comprehensive test suite using **Catch2** framework:

### Run Tests

```bash
cd cpp
make test_unit test_integration
./test_unit && ./test_integration
```

### Coverage

- **Unit Tests:** 18 assertions covering Board, Snake, Food, and SnakeSegment
- **Integration Tests:** 43 assertions validating complete game scenarios
- **Total:** 61 assertions, 100% pass rate

Test files demonstrate proper mocking and dependency injection practices.

---

## Comparison: C vs C++

| Aspect | C Legacy | C++ Modern |
|--------|----------|------------|
| Paradigm | Procedural | Object-Oriented |
| Memory Management | Manual | Automatic (smart pointers) |
| Extensibility | Function pointers | Interfaces + Polymorphism |
| Coupling | Tight | Loose (DI) |
| Testability | Difficult | Easy (mocking via interfaces) |
| Architecture | Modular | Layered + SOLID |
| Performance (move) | O(n) | O(1) |
| Occupancy checks | O(n) | O(1) |
| Lines of Code | ~800 | ~1200 (with tests) |

---

## License

This project is licensed under the MIT License. See [LICENSE](./LICENSE) for details.

---

## Educational Value

This project serves as a practical example of:

- Refactoring procedural code to object-oriented design
- Applying SOLID principles in real-world scenarios
- Using design patterns (Strategy, Factory, Dependency Injection)
- Writing testable, maintainable code
- Evolution from "working code" to "clean code" with performance awareness

Perfect for students learning software architecture and design patterns.
