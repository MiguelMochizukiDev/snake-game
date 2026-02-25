/**
 * main.cpp
 */

#include "game_controller.hpp"

#include <cstdlib>
#include <ctime>

int main() {
	std::srand(std::time(nullptr));
	GameController game;
	game.run();
}
