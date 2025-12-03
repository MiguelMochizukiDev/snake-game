#ifndef TERMINAL_H
#define TERMINAL_H

/**
 * Enable raw terminal mode for immediate key input without buffering
 * Input: None
 * Output: None (modifies terminal settings)
 */
void enable_raw_mode();

/**
 * Disable raw mode and restore normal terminal behavior
 * Input: None
 * Output: None (restores terminal settings)
 */
void disable_raw_mode();

/**
 * Check if a key has been pressed without blocking
 * Input: None
 * Output: 1 if key pressed, 0 otherwise
 */
int kbhit();

/**
 * Get a character from input without echo or buffering
 * Input: None
 * Output: Character code of pressed key
 */
char getch();

#endif

