/**
 * food.cpp
 */

#include "food.hpp"

#include <cstdlib>

Food::Food(IBoard* board) : board_(board), x_(-1), y_(-1) {}

int Food::getX() const { return x_; }
int Food::getY() const { return y_; }

void Food::setPosition(int x, int y) {
	x_ = x;
	y_ = y;
}

char Food::symbol() const { return '*'; }

void Food::spawn() {
	int width = board_->getLength();
	int height = board_->getHeight();

	int fx, fy;

	do {
		fx = std::rand() % width;
		fy = std::rand() % height;
	} while (board_->isOccupied(fx, fy));

	x_ = fx;
	y_ = fy;
}
