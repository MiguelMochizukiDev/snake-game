/**
 * main.cpp
 */

#include "game_controller.hpp"
#include "board.hpp"
#include "input_handler.hpp"
#include "score_manager.hpp"
#include "terminal_renderer.hpp"

#include <cstdlib>
#include <ctime>
#include <memory>

int main() {
	std::srand(std::time(nullptr));

	auto scoreManager = std::make_shared<ScoreManager>();
	auto board = std::make_shared<Board>(Config::LENGTH, Config::HEIGHT, scoreManager);
	auto inputHandler = std::make_shared<WASDInputHandler>();
	auto renderer = std::make_shared<TerminalRenderer>();

	GameController game(board, inputHandler, renderer);
	game.run();
}
