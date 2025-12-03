#ifndef SNAKE_H
#define SNAKE_H

#include "board.h"

#define HEAD_NEIGHBORHOOD_SIZE 5

typedef struct snake_node {
	int x;
	int y;
	struct snake_node * next;
} snake_node_t;

typedef struct {
	snake_node_t * head;
	snake_node_t * tail;
	char direction;
	int length;
} snake_t;

void init_snake(snake_t * snake);
void draw_snake(board_t * board, snake_t * snake);
void move_snake(snake_t * snake, board_t * board, int * running);
void free_snake(snake_t * snake);

#endif

