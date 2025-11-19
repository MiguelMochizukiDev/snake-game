#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "board.h"

// Separate function for ncurses setup
void init_ncurses() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); // Enable special keys like arrows
    timeout(100); // Non-blocking input with 100ms timeout
}

// Modified init_board without initscr()
void init_board(board_t *board) {
    board->height = HEIGHT;
    board->width = WIDTH;
    board->score = 0;

    // allocate grid
    board->grid = (char **) malloc(sizeof(char *) * HEIGHT);
    for (int y = 0; y < HEIGHT; y++) {
        board->grid[y] = (char *) malloc(sizeof(char) * WIDTH);
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                board->grid[y][x] = '#';
            } else {
                board->grid[y][x] = ' ';
            }
        }
    }

    // Place initial food
    int fx = rand() % (WIDTH - 2) + 1;
    int fy = rand() % (HEIGHT - 2) + 1;
    board->food_x = fx;
    board->food_y = fy;
    board->grid[fy][fx] = '*';
}

void print_board(board_t *board) {
    // Redraw entire grid (static borders + dynamic contents)
    for (int y = 0; y < board->height; y++) {
        for (int x = 0; x < board->width; x++) {
            mvaddch(y, x, board->grid[y][x]);
        }
    }

    // Print score below the board and refresh to update the screen
    mvprintw(board->height + 1, 0, "Score: %d", board->score);
    refresh();
}

void cleanup_ncurses() {
    endwin(); // Restores terminal to normal state
}

void free_board(board_t *board) {
    if (!board) return;
    if (board->grid) {
        for (int y = 0; y < board->height; y++) {
            free(board->grid[y]);
            board->grid[y] = NULL;
        }
        free(board->grid);
        board->grid = NULL;
    }
    board->height = 0;
    board->width = 0;
    board->score = 0;
}

void print_message(const char *msg, int line) {
    if (!msg) return;
    mvprintw(line, 0, "%s", msg);
    refresh();
}
