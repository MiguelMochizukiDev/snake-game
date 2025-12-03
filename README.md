# Snake Game in C

A terminal-based implementation of the classic Snake game, written in C with a modular architecture. The codebase separates concerns across **board**, **snake**, **game logic**, and **terminal I/O** modules.

---

## Features

* Terminal interface using ncurses
* Modular project structure (board, snake, game, terminal input)
* Real-time, non-blocking input
* Dynamic snake growth
* Collision detection (walls and self)
* Score display with persistent best-score tracking
* **Optimized performance** through object pooling and predictable frame timing
* **Smart food placement** avoiding the 5×5 region around the snake’s head
* Automatic logging of:

  * Best scores (`best_scores.txt`)
  * All game results (`score_history.txt`)

---

## Project Structure

```bash
snake_game/
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

---

## Compilation

Requires **gcc** and **ncurses**.

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

## Performance Optimizations

### Object Pooling

* Pre-allocated snake node pool
* Eliminates runtime allocation overhead
* Improves memory locality and consistency

### Smart Food Generation

* Avoids spawning food within a 5×5 region around the snake’s head
* Bounded fallback strategy prevents timing spikes

### Frame Stability

* Avoids stuttering caused by dynamic allocation
* Predictable update cycle and optimized collision checks

---

## Notes

* Uses `system("clear")` to refresh the screen. On Windows, replace with `system("cls")`.
* Memory management relies on `malloc`/`free`.

---

## License

This project is licensed under the MIT License. See [LICENSE](./LICENSE).