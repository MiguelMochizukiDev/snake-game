/**
 * main.cpp
 * Author: Miguel Mochizuki Silva
 * Description: Main entry point
 */
#include "game_engine.hpp"

/**
 * Program entry point
 *
 * Returns int: Exit status
 */
int main() {
	GameEngine engine(20, 20, 200);
	engine.run();
	return 0;
}
