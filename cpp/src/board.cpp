/**
 * board.cpp
 */

#include "board.hpp"
#include "food.hpp"
#include "snake.hpp"

#include <iostream>

Board::Board(int length, int height)
	: length_(length), height_(height) {
	grid_.resize(height_);

	for (int y = 0; y < height_; y++) {
		grid_[y].resize(length_, nullptr);
	}

	food_ = std::make_unique<Food>(this);
	snake_ = std::make_unique<Snake>(this);

	food_->spawn();
	sync();
}

Board::~Board() {}

int Board::getLength() const { return length_; }
int Board::getHeight() const { return height_; }

Food* Board::getFood() const { return food_.get(); }
Snake* Board::getSnake() const { return snake_.get(); }

std::vector<std::vector<Entity*>>& Board::getGrid() {
	return grid_;
}

bool Board::isOccupied(int x, int y) const {
	if (x < 0 || x >= length_ || y < 0 || y >= height_)
		return true;

	for (const auto& seg : snake_->getSegments()) {
		if (seg->getX() == x && seg->getY() == y)
			return true;
	}

	return false;
}

void Board::sync() {
	for (auto& row : grid_) {
		for (auto& cell : row) {
			cell = nullptr;
		}
	}

	for (const auto& seg : snake_->getSegments()) {
		grid_[seg->getY()][seg->getX()] = seg.get();
	}

	grid_[food_->getY()][food_->getX()] = food_.get();
}

void Board::update(Direction direction) {
	snake_->move(direction);

	if (snake_->getSegments().front()->getX() == food_->getX() &&
	    snake_->getSegments().front()->getY() == food_->getY()) {
		snake_->grow();
		food_->spawn();
	}

	sync();
}

void Board::render() const {
	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < length_; ++x) {
			if (grid_[y][x] == nullptr)
				std::cout << ".";
			else if (grid_[y][x] == food_.get())
				std::cout << "F";
			else
				std::cout << "O";
		}
		std::cout << "\n";
	}
}
