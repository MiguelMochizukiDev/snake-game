/**
 * test_integration.cpp
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "board.hpp"
#include "snake.hpp"
#include "food.hpp"
#include "entity.hpp"

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
	}

	SECTION("Movement keeps grid consistent") {

		snake->move(Direction::RIGHT);
		board.sync();

		for (auto& seg : snake->getSegments()) {
			REQUIRE(board.getGrid()[seg->getY()][seg->getX()] == seg.get());
		}
	}

	SECTION("Grow keeps grid consistent") {

		int sizeBefore = snake->getSegments().size();

		snake->grow();
		board.sync();

		REQUIRE(snake->getSegments().size() == sizeBefore + 1);

		for (auto& seg : snake->getSegments()) {
			REQUIRE(board.getGrid()[seg->getY()][seg->getX()] == seg.get());
		}
	}

	SECTION("Food respawn never overlaps snake") {

		for (int i = 0; i < 20; ++i) {
			food->spawn();
			board.sync();

			bool overlap = false;

			for (auto& seg : snake->getSegments()) {
				if (seg->getX() == food->getX() &&
				    seg->getY() == food->getY()) {
					overlap = true;
				}
			}

			REQUIRE_FALSE(overlap);
		}
	}

	SECTION("Wall collision throws exception") {

		auto* head = snake->getSegments().front().get();

		while (head->getX() < board.getLength() - 1) {
			snake->move(Direction::RIGHT);
			board.sync();
		}

		REQUIRE_THROWS_AS(snake->move(Direction::RIGHT), std::runtime_error);
	}
}
