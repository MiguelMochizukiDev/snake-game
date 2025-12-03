#include "game.h"

void init_game(game_t *game) {
	init_board(&game->board);
	init_snake(&game->snake);
	game->running = 1;
	draw_snake(&game->board, &game->snake);
}

