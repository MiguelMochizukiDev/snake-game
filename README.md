# Snake Game

A terminal-based implementation of the classic Snake game.

Originally this project was written in C with a modular architecture. The codebase separated concerns across **board**, **snake**, **game logic**, and **terminal I/O** modules.

Later it has been refactored in C++ following object-oriented paradigm, with three main classes: Board, Entity (modeling grids, food and snake segments) and GameController, which runs main logic.

---

## Features

* Terminal interface
* Object-oriented paradigm
* Real-time, non-blocking input
* Dynamic snake growth (now with vector from STL)
* Automatic logging of:

  * Best scores (`best_scores.txt`)
  * All game results (`score_history.txt`)

---

## Project Structure

### C Legacy

```bash
c_legacy/
├─ include/
│  ├─ board.h
│  ├─ snake.h
│  ├─ game.h
│  └─ terminal.h
├─ src/
│  ├─ board.c
│  ├─ snake.c
│  ├─ game.c
│  └─ terminal.c
└─ main.c
```

### C++

```bash
cpp/
├── best_scores.txt
├── include
│   ├── board.hpp
│   ├── catch2
│   │   └── catch.hpp
│   ├── constants.hpp
│   ├── entity.hpp
│   ├── food.hpp
│   ├── game_controller.hpp
│   └── snake.hpp
├── main.cpp
├── Makefile
├── score_history.txt
├── snake
├── src
│   ├── board.cpp
│   ├── food.cpp
│   ├── game_controller.cpp
│   └── snake.cpp
├── test_integration
├── tests
│   ├── test_integration.cpp
│   └── test_unit.cpp
└── test_unit
```

---

## Compilation

### C Legacy

Requires **gcc** and **ncurses**.

```bash
cd c_legacy

gcc -o snake \
  -Iinclude \
  src/board.c \
  src/snake.c \
  src/game.c \
  src/terminal.c \
  main.c \
  -Wall -Wextra -pedantic -lncurses
```

Run with:

```bash
./snake
```

### C++

Requires **Make**.

```bash
cd cpp
make snake
```

Run with:

```bash
./snake
```

Controls (WASD):

* **W**: Up
* **S**: Down
* **A**: Left
* **D**: Right

The game ends on collision with a wall or the snake’s body.

---

## Score Tracking

### `best_scores.txt`

* Loaded on startup
* Displays current best score during gameplay
* Updated when a new session high score is achieved
* New best scores are appended as separate entries

### `score_history.txt`

* Logs every final score
* Provides full session history for progress or statistics

---

## New Features

### Automatic Memory Management

Using smart pointers, the C++ version is far more memory safe than the latter C implementation.

### Polymorphis

The C++ version implements an abstract class Entity which models the grid_ attribute from Board, the segments_ attribute (vector of SnakeSegments, which is subclass of Entity) of Snake and and Food (as explicit subclass).

### Cross-Platform Support

Using macros the C++ version is expected to run both on Windows and UNIX/Linux systems.

### Unit and Integration Tests

Using Catch2, we implement unit and integrated tests to C++ implementation.

## Notes

C++ version is still in development.

---

## License

This project is licensed under the MIT License. See [LICENSE](./LICENSE).