/**
 * test_unit.cpp
 * Unit tests for Snake game components
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "board.hpp"
#include "snake.hpp"
#include "food.hpp"
#include "constants.hpp"

TEST_CASE("Board") {
	Board board(15, 25);

	REQUIRE(board.getLength() == 15);
	REQUIRE(board.getHeight() == 25);
}

TEST_CASE("Food") {
	Board board(10, 10);
	Food* food = board.getFood();

	REQUIRE(food->getX() >= 0);
	REQUIRE(food->getX() < board.getLength());
	REQUIRE(food->getY() >= 0);
	REQUIRE(food->getY() < board.getHeight());
	REQUIRE(food->symbol() == '*');

	food->setPosition(3, 4);
	REQUIRE(food->getX() == 3);
	REQUIRE(food->getY() == 4);
}

TEST_CASE("SnakeSegment") {
	SnakeSegment seg(1, 2);

	REQUIRE(seg.getX() == 1);
	REQUIRE(seg.getY() == 2);
	REQUIRE(seg.symbol() == 'O');

	seg.setPosition(5, 6);
	REQUIRE(seg.getX() == 5);
	REQUIRE(seg.getY() == 6);
}

TEST_CASE("Snake basic behavior") {
	Board board(10, 10);
	Snake* snake = board.getSnake();

	REQUIRE(snake->getLength() == Config::INITIAL_SNAKE_SIZE);
	REQUIRE(snake->getSegments().size() == Config::INITIAL_SNAKE_SIZE);

	const SnakeSegment* head = snake->getHead();
	REQUIRE(head != nullptr);

	int headX = head->getX();
	int headY = head->getY();

	bool foodEaten = snake->move(Direction::RIGHT, -1, -1);
	board.sync();

	REQUIRE(snake->getLength() == Config::INITIAL_SNAKE_SIZE);
	REQUIRE(snake->getHead()->getX() == headX + 1);
	REQUIRE(snake->getHead()->getY() == headY);
	REQUIRE_FALSE(foodEaten);

	const SnakeSegment* tail = snake->getTail();
	REQUIRE(tail != nullptr);
	REQUIRE(tail->getX() == headX - (Config::INITIAL_SNAKE_SIZE - 2));
	REQUIRE(tail->getY() == headY);
}

TEST_CASE("Snake growth when eating food") {
	Board board(10, 10);
	Snake* snake = board.getSnake();

	size_t initialSize = snake->getLength();

	int headX = snake->getHead()->getX();
	int headY = snake->getHead()->getY();

	int foodX = headX + 1;
	int foodY = headY;

	bool foodEaten = snake->move(Direction::RIGHT, foodX, foodY);
	board.sync();

	REQUIRE(foodEaten == true);
	REQUIRE(snake->getLength() == initialSize + 1);
	REQUIRE(snake->getHead()->getX() == foodX);
	REQUIRE(snake->getHead()->getY() == foodY);

	snake->setGrow();
	foodEaten = snake->move(Direction::RIGHT, -1, -1);
	board.sync();

	REQUIRE_FALSE(foodEaten);
	REQUIRE(snake->getLength() == initialSize + 2);
}

TEST_CASE("Snake collision detection - simplified") {
	Board board(10, 10);
	Snake* snake = board.getSnake();

	const SnakeSegment* head = snake->getHead();
	int startY = head->getY();

	for (int i = 0; i < startY; ++i) {
		snake->move(Direction::UP, -1, -1);
		board.sync();
	}

	REQUIRE(snake->getHead()->getY() == 0);
	REQUIRE_THROWS_AS(snake->move(Direction::UP, -1, -1), std::runtime_error);
}

TEST_CASE("Snake wall collision") {
	Board board(10, 10);
	Snake* snake = board.getSnake();

	const SnakeSegment* head = snake->getHead();
	int startY = head->getY();

	for (int i = 0; i < startY; ++i) {
		snake->move(Direction::UP, -1, -1);
		board.sync();
	}

	REQUIRE(snake->getHead()->getY() == 0);
	REQUIRE_THROWS_AS(snake->move(Direction::UP, -1, -1), std::runtime_error);

	Board wallBoard(5, 5);
	Snake* wallSnake = wallBoard.getSnake();

	wallSnake->move(Direction::RIGHT, -1, -1);
	wallBoard.sync();
	wallSnake->move(Direction::RIGHT, -1, -1);
	wallBoard.sync();

	REQUIRE(wallSnake->getHead()->getX() == 4);
	REQUIRE_THROWS_AS(wallSnake->move(Direction::RIGHT, -1, -1), std::runtime_error);
}

TEST_CASE("Snake self collision") {
	Board board(5, 5);
	Snake* snake = board.getSnake();
	Food* food = board.getFood();

	food->setPosition(-1, -1);
	board.sync();

	snake->move(Direction::RIGHT, -1, -1);
	board.sync();

	snake->move(Direction::DOWN, -1, -1);
	board.sync();

	snake->move(Direction::LEFT, -1, -1);
	board.sync();

	snake->move(Direction::UP, -1, -1);
	board.sync();

	REQUIRE_THROWS_AS(snake->move(Direction::DOWN, -1, -1), std::runtime_error);
}

TEST_CASE("Snake self collision - edge case") {
	Board board(10, 10);
	Snake* snake = board.getSnake();
	Food* food = board.getFood();

	food->setPosition(-1, -1);
	board.sync();

	snake->move(Direction::RIGHT, -1, -1);
	board.sync();

	snake->move(Direction::DOWN, -1, -1);
	board.sync();

	snake->move(Direction::LEFT, -1, -1);
	board.sync();

	bool moved = false;
	try {
		snake->move(Direction::UP, -1, -1);
		board.sync();
		moved = true;
	} catch (...) {
		moved = false;
	}
	REQUIRE(moved == true);

	try {
		snake->move(Direction::LEFT, -1, -1);
		board.sync();
		moved = true;
	} catch (...) {
		moved = false;
	}
	REQUIRE(moved == true);
}

TEST_CASE("Snake getters and edge cases") {
	Board board(10, 10);
	Snake* snake = board.getSnake();

	REQUIRE(snake->getHead() != nullptr);
	REQUIRE(snake->getTail() != nullptr);
	REQUIRE(snake->getLength() == Config::INITIAL_SNAKE_SIZE);

	const auto& segments = snake->getSegments();
	REQUIRE(segments.size() == Config::INITIAL_SNAKE_SIZE);

	snake->setGrow();

	bool foodEaten = snake->move(Direction::RIGHT, -1, -1);
	board.sync();

	REQUIRE_FALSE(foodEaten);
	REQUIRE(snake->getLength() == Config::INITIAL_SNAKE_SIZE + 1);

	foodEaten = snake->move(Direction::RIGHT, -1, -1);
	board.sync();

	REQUIRE_FALSE(foodEaten);
	REQUIRE(snake->getLength() == Config::INITIAL_SNAKE_SIZE + 1);
}
