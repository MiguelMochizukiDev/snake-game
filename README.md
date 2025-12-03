# Snake Game in C

A classic Snake game implemented in C, designed with a modular structure.  
This project demonstrates clean separation of concerns using headers and source files for **board**, **snake**, **game**, and **terminal input handling**.

---

## Features

- Terminal-based Snake game.
- Modular code: board, snake, game logic, and terminal I/O separated.
- Real-time input (no need to press Enter).
- Dynamic snake growth when eating food.
- Score tracking with persistent best score history.
- Collision detection with walls and itself.
- **Score History**: The game automatically saves your best scores to `best_scores.txt` and displays your current best score during gameplay. Additionally, every final score is saved to `score_history.txt` for complete game tracking.

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

The game ends if the snake hits a wall or itself. Your current score and best score are displayed at the bottom of the board.

## Score History

The game maintains two types of score tracking:

### Best Scores (`best_scores.txt`)
- On startup, the game reads your previous best score from `best_scores.txt`
- During gameplay, your best score is displayed alongside your current score
- When you achieve a new high score, it becomes your new best score for that session
- At the end of the game, if you set a new record, it's automatically saved to `best_scores.txt`
- Each new record is appended as a new line

### Complete Game History (`score_history.txt`)
- Every final score from each game is saved to `score_history.txt`
- This provides a complete log of all your game sessions
- Useful for tracking your progress and game statistics over time

## Notes

- The game uses system("clear") to redraw the board. On Windows, replace it with system("cls").

- Memory management uses malloc and free.

## License
This project is under MIT License. For more information see [LICENSE](./LICENSE).
