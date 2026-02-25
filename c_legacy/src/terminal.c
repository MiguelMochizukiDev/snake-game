#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include "terminal.h"

struct termios orig_termios;

void enable_raw_mode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

int kbhit() {
	struct timeval tv = {0L, 0L};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

char getch() {
	char c;
	if (read(STDIN_FILENO, &c, 1) < 0)
		return 0;
	return c;
}

