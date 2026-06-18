/**
 * snake.cpp
 * Snake implementation using std::deque for O(1) push_front/pop_back
 */

#include "snake.hpp"
#include "constants.hpp"
#include <stdexcept>

/* SnakeSegment implementation */
SnakeSegment::SnakeSegment(int x, int y) : x_(x), y_(y) {}

int SnakeSegment::getX() const { return x_; }
int SnakeSegment::getY() const { return y_; }

void SnakeSegment::setPosition(int x, int y) {
	x_ = x;
	y_ = y;
}

char SnakeSegment::symbol() const { return 'O'; }

/* Snake implementation */
Snake::Snake(IBoard* board) : board_(board), shouldGrow_(false) {
	int startX = board_->getLength() / 2;
	int startY = board_->getHeight() / 2;

	/* Build initial snake from head backwards */
	for (int i = 0; i < Config::INITIAL_SNAKE_SIZE; i++) {
		segments_.emplace_back(
			std::make_unique<SnakeSegment>(startX - i, startY)
		);
	}
}

bool Snake::move(Direction direction, int foodX, int foodY) {
	if (segments_.empty())
		return false;

	int newX = segments_.front()->getX();
	int newY = segments_.front()->getY();

	switch (direction) {
		case Direction::UP: newY -= 1; break;
		case Direction::DOWN: newY += 1; break;
		case Direction::LEFT: newX -= 1; break;
		case Direction::RIGHT: newX += 1; break;
		default: break;
	}

	if (newX < 0 || newX >= board_->getLength() ||
		newY < 0 || newY >= board_->getHeight()) {
		throw std::runtime_error("Game Over: crashed into the wall!");
	}

	bool eatingFood = (newX == foodX && newY == foodY);

	size_t segmentsToCheck = segments_.size();
	if (!shouldGrow_ && !eatingFood && segmentsToCheck > 0) {
		segmentsToCheck = segments_.size() - 1;
	}

	for (size_t i = 0; i < segmentsToCheck; ++i) {
		if (segments_[i]->getX() == newX && segments_[i]->getY() == newY) {
			throw std::runtime_error("Game Over: crashed into itself!");
		}
	}

	if (eatingFood) {
		shouldGrow_ = true;
	}

	segments_.emplace_front(std::make_unique<SnakeSegment>(newX, newY));

	if (!shouldGrow_) {
		segments_.pop_back();
	} else {
		shouldGrow_ = false;
	}

	return eatingFood;
}

void Snake::setGrow() {
	shouldGrow_ = true;
}

const std::deque<std::unique_ptr<SnakeSegment>>&
Snake::getSegments() const {
	return segments_;
}

const SnakeSegment* Snake::getHead() const {
	if (segments_.empty())
		return nullptr;
	return segments_.front().get();
}

const SnakeSegment* Snake::getTail() const {
	if (segments_.empty())
		return nullptr;
	return segments_.back().get();
}

size_t Snake::getLength() const {
	return segments_.size();
}
