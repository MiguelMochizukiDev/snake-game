# Snake Game in C

A classic Snake game implemented in C, designed with a modular structure.  
This project demonstrates clean separation of concerns using headers and source files for **board**, **snake**, **game**, and **terminal input handling**.

---

## Features

- Terminal-based Snake game.
- Modular code: board, snake, game logic, and terminal I/O separated.
- Real-time input (no need to press Enter).
- Dynamic snake growth when eating food.
- Score tracking.
- Collision detection with walls and itself.

---

## Project Structure

```bash
snake_game/
├─ include/
│ ├─ board.h
│ ├─ snake.h
│ ├─ game.h
│ └─ terminal.h
├─ src/
│ ├─ board.c
│ ├─ snake.c
│ ├─ game.c
│ └─ terminal.c
└─ main.c
```

---

## Compilation

Use `gcc` to compile all source files and include the header directory. Ensure installing ncurses before compilling:

```bash
gcc -o snake \
  -Iinclude \
  src/board.c \
  src/snake.c \
  src/game.c \
  src/terminal.c \
  main.c \
  -Wall -Wextra -pedantic -lncurses
```

This produces an executable named snake.
Running the Game

```bash
./snake
```

Control the snake with WASD keys:

- W -> Up

- S -> Down

- A -> Left

- D -> Right

The game ends if the snake hits a wall or itself. Your score is displayed at the bottom of the board.

## Notes

- The game uses system("clear") to redraw the board. On Windows, replace it with system("cls").

- Memory management uses malloc and free.

## License
This project is under MIT License. For more information see [LICENSE](./LICENSE).
