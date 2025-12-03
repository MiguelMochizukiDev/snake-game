#ifndef BOARD_H
#define BOARD_H

#define HEIGHT 20  /* Game board height in cells */
#define WIDTH 20   /* Game board width in cells */

/**
 * Game board structure containing grid, dimensions, scores and food position
 * Input: None (structure definition)
 * Output: None (structure definition)
 */
typedef struct {
	char **grid;      /* 2D grid representing the game board */
	int height;       /* Board height (should equal HEIGHT) */
	int width;        /* Board width (should equal WIDTH) */
	int score;        /* Current game score */
	int best_score;   /* Best score from previous games */
	int food_x;       /* Food X coordinate */
	int food_y;       /* Food Y coordinate */
} board_t;

/**
 * Initialize ncurses library for terminal-based display
 * Input: None
 * Output: None
 */
void init_ncurses();

/**
 * Initialize game board with borders, empty spaces and initial food placement
 * Input: board - pointer to board structure to initialize
 * Output: None (modifies board structure)
 */
void init_board(board_t *board);

/**
 * Display the current board state and scores to the terminal
 * Input: board - pointer to board structure to display
 * Output: None (updates terminal display)
 */
void print_board(board_t *board);

/**
 * Free allocated memory for board grid
 * Input: board - pointer to board structure to cleanup
 * Output: None (frees memory)
 */
void free_board(board_t *board);

/**
 * Print a message at specified line on terminal
 * Input: msg - message string to display, line - line number for display
 * Output: None (updates terminal display)
 */
void print_message(const char *msg, int line);

/**
 * Cleanup ncurses library and restore terminal state
 * Input: None
 * Output: None
 */
void cleanup_ncurses();

/**
 * Read the best score from best_scores.txt file
 * Input: None
 * Output: Best score as integer, 0 if file doesn't exist
 */
int read_best_score();

/**
 * Save a new best score to best_scores.txt file
 * Input: score - score value to save
 * Output: None (writes to file)
 */
void save_score(int score);

/**
 * Save final score to score_history.txt for complete game tracking
 * Input: score - final score value to save
 * Output: None (writes to file)
 */
void save_final_score(int score);

#endif
