#include <stdlib.h>
#include <time.h>
#include "snake.h"

void init_snake(snake_t * snake) {
	int x0 = WIDTH / 2;
	int y0 = HEIGHT / 2;

	snake_node_t * head = (snake_node_t *) malloc(sizeof(snake_node_t));
	head->x = x0;
	head->y = y0;
	head->next = NULL;

	snake->head = head;
	snake->tail = head;
	snake->direction = 'R';
	snake->length = 1;

	snake_node_t * current = head;
	for (int i = 1; i < 3; i++) {
		snake_node_t * new_node = (snake_node_t *) malloc(sizeof(snake_node_t));
		new_node->x = x0 - i;
		new_node->y = y0;
		new_node->next = NULL;
		current->next = new_node;
		current = new_node;
	}

	snake->tail = current;
	snake->length = 3;
}

void draw_snake(board_t * board, snake_t * snake) {
	snake_node_t * current = snake->head;
	board->grid[current->y][current->x] = 'S';
	current = current->next;
	while (current) {
		board->grid[current->y][current->x] = 's';
		current = current->next;
	}
}

void move_snake(snake_t * snake, board_t * board, int * running) {
	int new_x = snake->head->x;
	int new_y = snake->head->y;

	switch (snake->direction) {
		case 'U': new_y--; break;
		case 'D': new_y++; break;
		case 'L': new_x--; break;
		case 'R': new_x++; break;
	}

	if (new_x <= 0 || new_x >= WIDTH - 1 || new_y <= 0 || new_y >= HEIGHT - 1) {
		*running = 0;
		return;
	}

	snake_node_t * current = snake->head;
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
		
		// Update best score if current score is higher
		if (board->score > board->best_score) {
			board->best_score = board->score;
		}

		int fx, fy;
		int head_x = snake->head->x;
		int head_y = snake->head->y;
		int half_size = HEAD_NEIGHBORHOOD_SIZE / 2;
		snake_node_t * check;
		
		do {
			fx = rand() % (WIDTH - 2) + 1;
			fy = rand() % (HEIGHT - 2) + 1;
			
			// First check neighborhood (faster than iterating through snake)
			if (fx >= head_x - half_size && fx <= head_x + half_size &&
			    fy >= head_y - half_size && fy <= head_y + half_size) {
				continue; // Skip to next iteration
			}
			
			// Then check collision with snake body
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
		} while (1);

		board->food_x = fx;
		board->food_y = fy;
		board->grid[fy][fx] = '*';
	}

	snake_node_t * new_head = (snake_node_t *) malloc(sizeof(snake_node_t));
	new_head->x = new_x;
	new_head->y = new_y;
	new_head->next = snake->head;
	snake->head = new_head;

	board->grid[new_y][new_x] = 'S';
	board->grid[new_head->next->y][new_head->next->x] = 's';

	if (!grow && snake->head != snake->tail) {
		current = snake->head;
		while (current->next != snake->tail) {
			current = current->next;
		}
		board->grid[snake->tail->y][snake->tail->x] = ' ';
		free(snake->tail);
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
		free(cur);
		cur = next;
	}
	snake->head = NULL;
	snake->tail = NULL;
	snake->length = 0;
}

