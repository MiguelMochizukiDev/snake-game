/**
 * test_unit.cpp
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "board.hpp"
#include "snake.hpp"
#include "food.hpp"

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

	REQUIRE(snake->getSegments().size() == Config::INITIAL_SNAKE_SIZE);

	int headX = snake->getSegments().front()->getX();
	int headY = snake->getSegments().front()->getY();

	snake->move(Direction::RIGHT);
	board.sync();

	REQUIRE(snake->getSegments().front()->getX() == headX + 1);
	REQUIRE(snake->getSegments().front()->getY() == headY);

	snake->grow();
	board.sync();

	REQUIRE(snake->getSegments().size() == Config::INITIAL_SNAKE_SIZE + 1);
}
