#include <stdlib.h>
#include <time.h>
#include "snake.h"

void init_node_pool(snake_t *snake) {
	/* Initialize the pool by linking all nodes together */
	for (int i = 0; i < (NODE_POOL_SIZE - 1); i++) {
		snake->node_pool[i].next = &snake->node_pool[i + 1];
	}
	snake->node_pool[NODE_POOL_SIZE - 1].next = NULL;
	snake->free_nodes = &snake->node_pool[0];
	snake->pool_initialized = 1;
}

snake_node_t *get_node_from_pool(snake_t *snake) {
	if (!snake->pool_initialized) {
		init_node_pool(snake);
	}
	
	if (!snake->free_nodes) {
		/* Pool exhausted, fallback to malloc (shouldn't happen in normal play) */
		return (snake_node_t *) malloc(sizeof(snake_node_t));
	}
	
	snake_node_t *node = snake->free_nodes;
	snake->free_nodes = snake->free_nodes->next;
	return node;
}

void return_node_to_pool(snake_t *snake, snake_node_t *node) {
	if (!node) return;
	
	/* Check if node is from pool (within pool memory range) */
	if (node >= snake->node_pool && node < (snake->node_pool + NODE_POOL_SIZE)) {
		node->next = snake->free_nodes;
		snake->free_nodes = node;
	} else {
		/* Node was malloc'd, free it normally */
		free(node);
	}
}

void init_snake(snake_t *snake) {
	int x0 = WIDTH / 2;
	int y0 = HEIGHT / 2;

	/* Initialize object pool */
	snake->pool_initialized = 0;
	init_node_pool(snake);

	snake_node_t *head = get_node_from_pool(snake);
	head->x = x0;
	head->y = y0;
	head->next = NULL;

	snake->head = head;
	snake->tail = head;
	snake->direction = 'R';
	snake->length = 1;

	snake_node_t *current = head;
	for (int i = 1; i < 3; i++) {
		snake_node_t *new_node = get_node_from_pool(snake);
		new_node->x = x0 - i;
		new_node->y = y0;
		new_node->next = NULL;
		current->next = new_node;
		current = new_node;
	}

	snake->tail = current;
	snake->length = 3;
}

void draw_snake(board_t *board, snake_t *snake) {
	snake_node_t *current = snake->head;
	board->grid[current->y][current->x] = 'S';
	current = current->next;
	while (current) {
		board->grid[current->y][current->x] = 's';
		current = current->next;
	}
}

void move_snake(snake_t *snake, board_t *board, int *running) {
	int new_x = snake->head->x;
	int new_y = snake->head->y;

	switch (snake->direction) {
		case 'U': new_y--; break;
		case 'D': new_y++; break;
		case 'L': new_x--; break;
		case 'R': new_x++; break;
	}

	/* Check wall collision */
	if (new_x <= 0 || new_x >= (WIDTH - 1) || new_y <= 0 || new_y >= (HEIGHT - 1)) {
		*running = 0;
		return;
	}

	/* Check self collision */
	snake_node_t *current = snake->head;
	while (current) {
		if (current->x == new_x && current->y == new_y) {
			*running = 0;
			return;
		}
		current = current->next;
	}

	int grow = 0;
	if (new_x == board->food_x && new_y == board->food_y) {
		grow = 1;
		board->score++;
		
		/* Update best score if current score is higher */
		if (board->score > board->best_score) {
			board->best_score = board->score;
		}

		/* Optimized food generation with attempt limit to ensure consistent timing */
		int fx, fy;
		int head_x = snake->head->x;
		int head_y = snake->head->y;
		int half_size = HEAD_NEIGHBORHOOD_SIZE / 2;
		snake_node_t *check;
		int attempts = 0;
		const int MAX_ATTEMPTS = 100; /* Prevent infinite loops */
		
		/* Disable neighborhood restriction when snake is too long to avoid placement issues */
		const int TOTAL_CELLS = (WIDTH - 2) * (HEIGHT - 2); /* Available playing area */
		const int DISABLE_NEIGHBORHOOD_THRESHOLD = TOTAL_CELLS * 3 / 4; /* 75% of board filled */
		int use_neighborhood = (snake->length < DISABLE_NEIGHBORHOOD_THRESHOLD);
		
		do {
			fx = rand() % (WIDTH - 2) + 1;
			fy = rand() % (HEIGHT - 2) + 1;
			attempts++;
			
			/* Check neighborhood only if snake is not too long */
			if (use_neighborhood &&
			    fx >= (head_x - half_size) && fx <= (head_x + half_size) &&
			    fy >= (head_y - half_size) && fy <= (head_y + half_size)) {
				if (attempts >= MAX_ATTEMPTS) {
					/* Fallback: place food at first valid position if we can't find random spot */
					for (int y = 1; y < (HEIGHT - 1); y++) {
						for (int x = 1; x < (WIDTH - 1); x++) {
							/* Skip neighborhood check in fallback if disabled */
							if (use_neighborhood && 
							    (x >= (head_x - half_size) && x <= (head_x + half_size) &&
							     y >= (head_y - half_size) && y <= (head_y + half_size))) {
								continue;
							}
							/* Check if position is free from snake */
							check = snake->head;
							int collision = 0;
							while (check) {
								if (check->x == x && check->y == y) {
									collision = 1;
									break;
								}
								check = check->next;
							}
							if (!collision) {
								fx = x;
								fy = y;
								goto food_placed;
							}
						}
					}
				}
				continue; /* Skip to next iteration */
			}
			
			/* Then check collision with snake body */
			check = snake->head;
			int collision = 0;
			while (check) {
				if (check->x == fx && check->y == fy) {
					collision = 1;
					break;
				}
				check = check->next;
			}
			
			if (!collision) break;
		} while (attempts < MAX_ATTEMPTS);
		
		food_placed:

		board->food_x = fx;
		board->food_y = fy;
		board->grid[fy][fx] = '*';
	}

	/* Create new head and move snake */
	snake_node_t *new_head = get_node_from_pool(snake);
	new_head->x = new_x;
	new_head->y = new_y;
	new_head->next = snake->head;
	snake->head = new_head;

	board->grid[new_y][new_x] = 'S';
	board->grid[new_head->next->y][new_head->next->x] = 's';

	/* Handle tail removal if not growing */
	if (!grow && snake->head != snake->tail) {
		current = snake->head;
		while (current->next != snake->tail) {
			current = current->next;
		}
		board->grid[snake->tail->y][snake->tail->x] = ' ';
		snake_node_t *old_tail = snake->tail;
		return_node_to_pool(snake, old_tail);
		snake->tail = current;
		snake->tail->next = NULL;
	} else if (grow) {
		snake->length++;
	}
}

void free_snake(snake_t *snake) {
	if (!snake) return;
	snake_node_t *cur = snake->head;
	while (cur) {
		snake_node_t *next = cur->next;
		return_node_to_pool(snake, cur);
		cur = next;
	}
	snake->head = NULL;
	snake->tail = NULL;
	snake->length = 0;
}

