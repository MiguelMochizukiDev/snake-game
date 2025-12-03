#ifndef SNAKE_H
#define SNAKE_H

#include "board.h"

#define HEAD_NEIGHBORHOOD_SIZE 5
#define MAX_SNAKE_LENGTH (WIDTH * HEIGHT)  // Maximum possible snake length
#define NODE_POOL_SIZE (MAX_SNAKE_LENGTH + 10)  // Pool with some extra nodes

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
	snake_node_t node_pool[NODE_POOL_SIZE];  // Pre-allocated node pool
	snake_node_t * free_nodes;  // Stack of available nodes
	int pool_initialized;
} snake_t;

void init_snake(snake_t * snake);
void draw_snake(board_t * board, snake_t * snake);
void move_snake(snake_t * snake, board_t * board, int * running);
void free_snake(snake_t * snake);
snake_node_t * get_node_from_pool(snake_t * snake);
void return_node_to_pool(snake_t * snake, snake_node_t * node);
void init_node_pool(snake_t * snake);

#endif

