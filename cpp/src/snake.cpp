/**
 * snake.cpp
 */

#include "snake.hpp"
#include "board.hpp"

#include <stdexcept>

SnakeSegment::SnakeSegment(int x, int y) : x_(x), y_(y) {}

int SnakeSegment::getX() const { return x_; }
int SnakeSegment::getY() const { return y_; }

void SnakeSegment::setPosition(int x, int y) {
	x_ = x;
	y_ = y;
}

char SnakeSegment::symbol() const { return 'O'; }

Snake::Snake(Board* board) : board_(board) {
	int startX = board_->getLength() / 2;
	int startY = board_->getHeight() / 2;

	for (int i = 0; i < Config::INITIAL_SNAKE_SIZE; i++) {
		segments_.push_back(
			std::make_unique<SnakeSegment>(startX - i, startY)
		);
	}
}

void Snake::move(Direction direction) {
	if (segments_.empty())
		return;

	int newX = segments_.front()->getX();
	int newY = segments_.front()->getY();

	switch (direction) {
		case Direction::UP:    newY -= 1; break;
		case Direction::DOWN:  newY += 1; break;
		case Direction::LEFT:  newX -= 1; break;
		case Direction::RIGHT: newX += 1; break;
	}

	if (newX < 0 || newX >= board_->getLength() ||
	    newY < 0 || newY >= board_->getHeight())
		throw std::runtime_error("Game Over: crashed into the wall!");

	for (const auto& seg : segments_) {
		if (seg->getX() == newX && seg->getY() == newY)
			throw std::runtime_error("Game Over: crashed into itself!");
	}

	for (int i = segments_.size() - 1; i > 0; i--) {
		segments_[i]->setPosition(
			segments_[i - 1]->getX(),
			segments_[i - 1]->getY()
		);
	}

	segments_.front()->setPosition(newX, newY);
}

void Snake::grow() {
	int size = segments_.size();

	if (size == 0)
		return;

	int tailX = segments_[size - 1]->getX();
	int tailY = segments_[size - 1]->getY();

	int newX = tailX;
	int newY = tailY;

	if (size > 1) {
		int prevX = segments_[size - 2]->getX();
		int prevY = segments_[size - 2]->getY();

		int dx = tailX - prevX;
		int dy = tailY - prevY;

		newX = tailX + dx;
		newY = tailY + dy;
	} else {
		newX = tailX - 1;
	}

	segments_.push_back(
		std::make_unique<SnakeSegment>(newX, newY)
	);
}

const std::vector<std::unique_ptr<SnakeSegment>>&
Snake::getSegments() const {
	return segments_;
}
