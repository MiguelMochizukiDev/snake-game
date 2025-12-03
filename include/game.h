#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "snake.h"

/**
 * Main game state structure containing board, snake and running status
 * Input: None (structure definition)
 * Output: None (structure definition)
 */
typedef struct {
	board_t board;    /* Game board with grid and scores */
	snake_t snake;    /* Snake entity with position and direction */
	int running;      /* Game running status flag (1=running, 0=stopped) */
} game_t;

/**
 * Initialize complete game state with board and snake
 * Input: game - pointer to game structure to initialize
 * Output: None (modifies game structure)
 */
void init_game(game_t *game);

#endif

