/**
 * terminal_renderer.cpp
 */

#include "terminal_renderer.hpp"
#include "board.hpp"

#include <iostream>
#include <cstdlib>

void TerminalRenderer::clear() const {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void TerminalRenderer::render(const Board& board) const {
	const auto& grid = const_cast<Board&>(board).getGrid();
	int length = board.getLength();
	int height = board.getHeight();

	/* Top border */
	for (int x = 0; x < length + 2; ++x) {
		std::cout << "#";
	}
	std::cout << "\n";

	/* Game area */
	for (int y = 0; y < height; ++y) {
		std::cout << "#";
		for (int x = 0; x < length; ++x) {
			if (grid[y][x] == nullptr)
				std::cout << " ";
			else
				std::cout << grid[y][x]->symbol();
		}
		std::cout << "#\n";
	}

	/* Bottom border */
	for (int x = 0; x < length + 2; ++x) {
		std::cout << "#";
	}
	std::cout << "\n";

	/* Score display */
	std::cout << "Score: " << board.getScore() << "\n";
	std::cout << "Best Score: " << board.getBestScore() << "\n";
}
