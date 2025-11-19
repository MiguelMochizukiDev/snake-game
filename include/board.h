#ifndef BOARD_H
#define BOARD_H

#define HEIGHT 20
#define WIDTH 20

typedef struct {
	char **grid;
	int height;
	int width;
	int score;
	int food_x;
	int food_y;
} board_t;

void init_ncurses();
void init_board(board_t * board);
void print_board(board_t * board);
void free_board(board_t * board);
void print_message(const char *msg, int line);
void cleanup_ncurses();

#endif
