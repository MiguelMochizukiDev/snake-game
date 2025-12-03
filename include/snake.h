#ifndef SNAKE_H
#define SNAKE_H

#include "board.h"

#define HEAD_NEIGHBORHOOD_SIZE 5                   /* Size of area around head where food won't spawn */
#define MAX_SNAKE_LENGTH (WIDTH * HEIGHT)          /* Maximum possible snake length */
#define NODE_POOL_SIZE (MAX_SNAKE_LENGTH + 10)     /* Pool with some extra nodes */

/**
 * Single node in the snake's linked list body
 * Input: None (structure definition)
 * Output: None (structure definition)
 */
typedef struct snake_node {
	int x;                        /* X coordinate of this body segment */
	int y;                        /* Y coordinate of this body segment */
	struct snake_node *next;      /* Pointer to next body segment */
} snake_node_t;

/**
 * Snake entity containing position, direction, and object pool for performance
 * Input: None (structure definition)
 * Output: None (structure definition)
 */
typedef struct {
	snake_node_t *head;                         /* Pointer to snake head */
	snake_node_t *tail;                         /* Pointer to snake tail */
	char direction;                             /* Current movement direction (U/D/L/R) */
	int length;                                 /* Current snake length */
	snake_node_t node_pool[NODE_POOL_SIZE];     /* Pre-allocated node pool */
	snake_node_t *free_nodes;                   /* Stack of available nodes */
	int pool_initialized;                       /* Flag for pool initialization status */
} snake_t;

/**
 * Initialize snake with starting position, direction and object pool
 * Input: snake - pointer to snake structure to initialize
 * Output: None (modifies snake structure)
 */
void init_snake(snake_t *snake);

/**
 * Draw snake on the game board grid
 * Input: board - game board to draw on, snake - snake to draw
 * Output: None (modifies board grid)
 */
void draw_snake(board_t *board, snake_t *snake);

/**
 * Move snake in current direction, handle collisions and food consumption
 * Input: snake - snake to move, board - game board, running - game state flag
 * Output: None (modifies snake, board, and running flag)
 */
void move_snake(snake_t *snake, board_t *board, int *running);

/**
 * Free all snake nodes and reset snake structure
 * Input: snake - snake structure to cleanup
 * Output: None (frees memory and resets structure)
 */
void free_snake(snake_t *snake);

/**
 * Get a node from the pre-allocated object pool for performance
 * Input: snake - snake containing the object pool
 * Output: Pointer to available snake node
 */
snake_node_t *get_node_from_pool(snake_t *snake);

/**
 * Return a node to the object pool for reuse
 * Input: snake - snake containing object pool, node - node to return
 * Output: None (returns node to pool)
 */
void return_node_to_pool(snake_t *snake, snake_node_t *node);

/**
 * Initialize the object pool by linking all nodes together
 * Input: snake - snake structure to initialize pool for
 * Output: None (initializes pool structure)
 */
void init_node_pool(snake_t *snake);

#endif

