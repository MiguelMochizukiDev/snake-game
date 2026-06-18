/**
 * food.cpp
 */

#include "food.hpp"
#include "board.hpp"
#include "snake.hpp"
#include <cstdlib>
#include <ctime>

Food::Food(IBoard* board) : board_(board) {
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	/* Don't spawn here - let Board handle it after full initialization */
}

void Food::spawn() {
	Board* board = dynamic_cast<Board*>(board_);
	if (!board) return;

	Snake* snake = board->getSnake();
	if (!snake) return; /* Safety check - snake might not be initialized yet */

	int attempts = 0;
	const int MAX_ATTEMPTS = 1000;

	do {
		x_ = std::rand() % board->getLength();
		y_ = std::rand() % board->getHeight();
		attempts++;

		/* Check if position is occupied by snake */
		bool occupied = false;
		for (auto& seg : snake->getSegments()) {
			if (seg->getX() == x_ && seg->getY() == y_) {
				occupied = true;
				break;
			}
		}

		if (!occupied) {
			break;
		}

	} while (attempts < MAX_ATTEMPTS);

	/* If we couldn't find a free position, try a simple scan */
	if (attempts >= MAX_ATTEMPTS) {
		for (int y = 0; y < board->getHeight() && attempts >= MAX_ATTEMPTS; ++y) {
			for (int x = 0; x < board->getLength() && attempts >= MAX_ATTEMPTS; ++x) {
				bool occupied = false;
				for (auto& seg : snake->getSegments()) {
					if (seg->getX() == x && seg->getY() == y) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					x_ = x;
					y_ = y;
					attempts = 0;
					break;
				}
			}
		}
	}
}

void Food::setPosition(int x, int y) {
	x_ = x;
	y_ = y;
}

int Food::getX() const { return x_; }
int Food::getY() const { return y_; }
char Food::symbol() const { return '*'; }
