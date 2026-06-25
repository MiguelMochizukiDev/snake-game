/**
 * input_handler.cpp
 */

#include "input_handler.hpp"

Direction WASDInputHandler::processInput(char c, Direction currentDirection) const {
	if ((c == 'w' || c == 'W') && currentDirection != Direction::DOWN)
		return Direction::UP;
	if ((c == 's' || c == 'S') && currentDirection != Direction::UP)
		return Direction::DOWN;
	if ((c == 'a' || c == 'A') && currentDirection != Direction::RIGHT)
		return Direction::LEFT;
	if ((c == 'd' || c == 'D') && currentDirection != Direction::LEFT)
		return Direction::RIGHT;

	return currentDirection;
}
