#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "snake.h"
#include "board.h"
#include "terminal.h"

#define DELAY 200000  /* Game loop delay in microseconds */

int main(void) {
	init_ncurses();

	srand(time(NULL));
	game_t game;
	init_game(&game);

	enable_raw_mode();

	/* Main game loop */
	while (game.running) {
		if (kbhit()) {
			char c = getch();
			switch (c) {
				case 'w': if (game.snake.direction != 'D') game.snake.direction = 'U'; break;
				case 's': if (game.snake.direction != 'U') game.snake.direction = 'D'; break;
				case 'a': if (game.snake.direction != 'R') game.snake.direction = 'L'; break;
				case 'd': if (game.snake.direction != 'L') game.snake.direction = 'R'; break;
				default:
					while (kbhit()) getch();
					break;
			}
		}

		move_snake(&game.snake, &game.board, &game.running);
		print_board(&game.board);
		usleep(DELAY);
	}

	/* Game over — show message and wait for any key before exiting so the
	 * player can see the final board.
	 */
	
	/* Save the final score to score history (every game) */
	save_final_score(game.board.score);
	
	/* Save the best score to best_scores.txt if it's a new record */
	if (game.board.score == game.board.best_score && game.board.score > 0) {
		save_score(game.board.best_score);
	}
	
	print_message("Game Over! Press \"enter\" to exit...", game.board.height + 3);

	/* Wait specifically for Enter (newline or carriage return) before exiting.
	 * This consumes other keys until Enter is pressed.
	 */
	int ch = 0;
	do {
		while (!kbhit()) {
			usleep(100000);
		}
		ch = (unsigned char) getch();
	} while (ch != '\n' && ch != '\r');

	/* Print final score before cleanup */
	printf("Game Over! Final Score: %d\n", game.board.score);

	/* Restore terminal modes and clean up ncurses */
	disable_raw_mode();

	/* Free heap allocations */
	free_snake(&game.snake);
	free_board(&game.board);

	cleanup_ncurses();

	return 0;
}

