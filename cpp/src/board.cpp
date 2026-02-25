/**
 * board.cpp
 */

#include "board.hpp"
#include "food.hpp"
#include "snake.hpp"

#include <iostream>
#include <fstream>
#include <string>

Board::Board(int length, int height)
	: length_(length), height_(height), score_(0), bestScore_(0) {
	grid_.resize(height_);

	for (int y = 0; y < height_; y++) {
		grid_[y].resize(length_, nullptr);
	}

	bestScore_ = readBestScore();

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
		score_++;
		if (score_ > bestScore_) {
			bestScore_ = score_;
		}
	}

	sync();
}

void Board::render() const {
	for (int x = 0; x < length_ + 2; ++x) {
		std::cout << "#";
	}
	std::cout << "\n";

	for (int y = 0; y < height_; ++y) {
		std::cout << "#";
		for (int x = 0; x < length_; ++x) {
			if (grid_[y][x] == nullptr)
				std::cout << " ";
			else
				std::cout << grid_[y][x]->symbol();
		}
		std::cout << "#\n";
	}

	for (int x = 0; x < length_ + 2; ++x) {
		std::cout << "#";
	}
	std::cout << "\n";

	std::cout << "Score: " << score_ << "\n";
	std::cout << "Best Score: " << bestScore_ << "\n";
}

int Board::getScore() const {
	return score_;
}

int Board::getBestScore() const {
	return bestScore_;
}

int Board::readBestScore() {
	std::ifstream file("best_scores.txt");
	if (!file.is_open()) {
		return 0;
	}

	int score = 0;
	std::string line;
	while (std::getline(file, line)) {
		try {
			score = std::stoi(line);
		} catch (...) {
		}
	}

	file.close();
	return score;
}

void Board::saveBestScore(int score) {
	std::ofstream file("best_scores.txt");
	if (!file.is_open()) {
		return;
	}

	file << score << "\n";
	file.close();
}

void Board::saveFinalScore(int score) {
	std::ofstream file("score_history.txt", std::ios::app);
	if (!file.is_open()) {
		return;
	}

	file << score << "\n";
	file.close();
}
