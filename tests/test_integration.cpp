/**
 * test_integration.cpp
 * Integration tests for Snake game components
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "board.hpp"
#include "snake.hpp"
#include "food.hpp"
#include "entity.hpp"
#include "constants.hpp"

TEST_CASE("Full system integration: Board + Snake + Food") {

	Board board(10, 10);
	Snake* snake = board.getSnake();
	Food* food = board.getFood();

	REQUIRE(board.getLength() == 10);
	REQUIRE(board.getHeight() == 10);

	SECTION("Initial state consistency") {

		board.sync();

		for (auto& seg : snake->getSegments()) {
			REQUIRE(board.getGrid()[seg->getY()][seg->getX()] == seg.get());
		}

		REQUIRE(board.getGrid()[food->getY()][food->getX()] == food);

		bool overlap = false;
		for (auto& seg : snake->getSegments()) {
			if (seg->getX() == food->getX() && seg->getY() == food->getY()) {
				overlap = true;
			}
		}
		REQUIRE_FALSE(overlap);

		REQUIRE(snake->getLength() == Config::INITIAL_SNAKE_SIZE);
	}

	SECTION("Movement keeps grid consistent") {

		bool foodEaten = snake->move(Direction::RIGHT, -1, -1);
		board.sync();

		REQUIRE_FALSE(foodEaten);

		for (auto& seg : snake->getSegments()) {
			REQUIRE(board.getGrid()[seg->getY()][seg->getX()] == seg.get());
		}

		for (size_t i = 0; i < snake->getSegments().size(); ++i) {
			for (size_t j = i + 1; j < snake->getSegments().size(); ++j) {
				const auto& seg1 = snake->getSegments()[i];
				const auto& seg2 = snake->getSegments()[j];
				bool samePosition = (seg1->getX() == seg2->getX()) &&
									(seg1->getY() == seg2->getY());
				REQUIRE_FALSE(samePosition);
			}
		}
	}

	SECTION("Growth keeps grid consistent") {

		size_t sizeBefore = snake->getLength();

		const SnakeSegment* head = snake->getHead();
		int foodX = head->getX() + 1;
		int foodY = head->getY();

		bool foodEaten = snake->move(Direction::RIGHT, foodX, foodY);
		board.sync();

		REQUIRE(foodEaten);
		REQUIRE(snake->getLength() == sizeBefore + 1);

		for (auto& seg : snake->getSegments()) {
			REQUIRE(board.getGrid()[seg->getY()][seg->getX()] == seg.get());
		}

		for (size_t i = 0; i < snake->getSegments().size(); ++i) {
			for (size_t j = i + 1; j < snake->getSegments().size(); ++j) {
				const auto& seg1 = snake->getSegments()[i];
				const auto& seg2 = snake->getSegments()[j];
				bool samePosition = (seg1->getX() == seg2->getX()) &&
									(seg1->getY() == seg2->getY());
				REQUIRE_FALSE(samePosition);
			}
		}
	}

	SECTION("Food respawn never overlaps snake") {

		for (int i = 0; i < 3; ++i) {
			snake->move(Direction::RIGHT, -1, -1);
			board.sync();
		}

		for (int i = 0; i < 20; ++i) {
			food->spawn();
			board.sync();

			bool overlap = false;
			for (auto& seg : snake->getSegments()) {
				if (seg->getX() == food->getX() &&
					seg->getY() == food->getY()) {
					overlap = true;
					break;
				}
			}
			REQUIRE_FALSE(overlap);

			REQUIRE(food->getX() >= 0);
			REQUIRE(food->getX() < board.getLength());
			REQUIRE(food->getY() >= 0);
			REQUIRE(food->getY() < board.getHeight());
		}
	}

	SECTION("Wall collision throws exception") {

		const SnakeSegment* head = snake->getHead();
		int movesToWall = board.getLength() - head->getX() - 1;

		for (int i = 0; i < movesToWall; ++i) {
			snake->move(Direction::RIGHT, -1, -1);
			board.sync();
		}

		REQUIRE(snake->getHead()->getX() == board.getLength() - 1);
		REQUIRE_THROWS_AS(snake->move(Direction::RIGHT, -1, -1),
						  std::runtime_error);
	}

	SECTION("Self collision throws exception") {

		Board smallBoard(5, 5);
		Snake* smallSnake = smallBoard.getSnake();
		Food* food = smallBoard.getFood();

		food->setPosition(-1, -1);
		smallBoard.sync();

		smallSnake->move(Direction::RIGHT, -1, -1);
		smallBoard.sync();

		smallSnake->move(Direction::DOWN, -1, -1);
		smallBoard.sync();

		smallSnake->move(Direction::LEFT, -1, -1);
		smallBoard.sync();

		smallSnake->move(Direction::UP, -1, -1);
		smallBoard.sync();

		REQUIRE_THROWS_AS(smallSnake->move(Direction::DOWN, -1, -1),
						  std::runtime_error);
	}

	SECTION("Full game loop integration") {

		Board gameBoard(15, 15);
		Snake* gameSnake = gameBoard.getSnake();
		Food* gameFood = gameBoard.getFood();

		int initialScore = 0;
		int moves = 0;

		gameFood->setPosition(10, 10);
		gameBoard.sync();

		for (int i = 0; i < 10; ++i) {
			const SnakeSegment* head = gameSnake->getHead();
			int foodX = gameFood->getX();
			int foodY = gameFood->getY();

			Direction dir = Direction::RIGHT;
			if (head->getX() < foodX) {
				dir = Direction::RIGHT;
			} else if (head->getX() > foodX) {
				dir = Direction::LEFT;
			} else if (head->getY() < foodY) {
				dir = Direction::DOWN;
			} else if (head->getY() > foodY) {
				dir = Direction::UP;
			}

			try {
				bool foodEaten = gameSnake->move(dir, foodX, foodY);
				gameBoard.sync();

				if (foodEaten) {
					gameFood->spawn();
					gameBoard.sync();
					initialScore++;
				}
				moves++;

				// Verify grid consistency after each move
				for (auto& seg : gameSnake->getSegments()) {
					REQUIRE(gameBoard.getGrid()[seg->getY()][seg->getX()] == seg.get());
				}

			} catch (const std::runtime_error& e) {
				// Game over - that's fine for test
				break;
			}
		}

		REQUIRE(moves > 0);
	}

	SECTION("setGrow flag integration") {

		Board growBoard(10, 10);
		Snake* growSnake = growBoard.getSnake();

		size_t initialSize = growSnake->getLength();

		growSnake->setGrow();

		bool foodEaten = growSnake->move(Direction::RIGHT, -1, -1);
		growBoard.sync();

		REQUIRE_FALSE(foodEaten);
		REQUIRE(growSnake->getLength() == initialSize + 1);

		for (auto& seg : growSnake->getSegments()) {
			REQUIRE(growBoard.getGrid()[seg->getY()][seg->getX()] == seg.get());
		}

		foodEaten = growSnake->move(Direction::RIGHT, -1, -1);
		growBoard.sync();

		REQUIRE_FALSE(foodEaten);
		REQUIRE(growSnake->getLength() == initialSize + 1);
	}

	SECTION("Multiple food eating sequence") {

		Board eatBoard(10, 10);
		Snake* eatSnake = eatBoard.getSnake();
		Food* eatFood = eatBoard.getFood();

		size_t initialSize = eatSnake->getLength();

		for (int i = 0; i < 3; ++i) {
			const SnakeSegment* head = eatSnake->getHead();

			int newX = head->getX() + 1;
			int newY = head->getY();

			if (newX >= eatBoard.getLength()) {
				newX = head->getX() - 1;
			}

			eatFood->setPosition(newX, newY);
			eatBoard.sync();

			Direction dir = (newX > head->getX()) ? Direction::RIGHT : Direction::LEFT;
			bool foodEaten = eatSnake->move(dir, newX, newY);
			eatBoard.sync();

			REQUIRE(foodEaten);
			REQUIRE(eatSnake->getLength() == initialSize + i + 1);

			eatFood->spawn();
			eatBoard.sync();

			for (auto& seg : eatSnake->getSegments()) {
				REQUIRE(eatBoard.getGrid()[seg->getY()][seg->getX()] == seg.get());
			}
		}

		REQUIRE(eatSnake->getLength() == initialSize + 3);
	}
}
