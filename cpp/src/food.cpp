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

EntityType Food::getType() const { return EntityType::FOOD; }

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

		/* Use board->isOccupied (now O(1) via grid) */
		if (!board->isOccupied(x_, y_)) {
			break;
		}

	} while (attempts < MAX_ATTEMPTS);

	/* If we couldn't find a free position, try a simple scan */
	if (attempts >= MAX_ATTEMPTS) {
		for (int y = 0; y < board->getHeight() && attempts >= MAX_ATTEMPTS; ++y) {
			for (int x = 0; x < board->getLength() && attempts >= MAX_ATTEMPTS; ++x) {
				if (!board->isOccupied(x, y)) {
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
