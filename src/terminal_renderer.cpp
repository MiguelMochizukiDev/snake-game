/**
 * terminal_renderer.cpp
 * Author: Miguel Mochizuki Silva
 * Description: Terminal renderer implementation
 */
#include "terminal_renderer.hpp"
#include "wasd_input_handler.hpp"
#include <iostream>
#include <cstdlib>
#include <iomanip>

/**
 * Clears the terminal screen
 */
void TerminalRenderer::clear() {
	std::cout << "\033[2J\033[H";;
}

/**
 * Renders the game state
 *
 * Parameters:
 * const GameState& state: The game state to render
 */
void TerminalRenderer::render(const GameState& state) {
	const auto& grid = state.getOccupied();
	int rows = state.getRows();
	int cols = state.getCols();

	// Top border
	for (int x = 0; x < cols + 2; ++x) {
		std::cout << "#";
	}
	std::cout << "\n";

	// Game grid - row by row (y is row, x is column)
	for (int y = 0; y < rows; ++y) {
		std::cout << "#";  // Left border
		for (int x = 0; x < cols; ++x) {
			if (grid[y][x]) {
				// Check if this is the food position
				if (x == state.getFood().getX() && y == state.getFood().getY()) {
					std::cout << "*";
				} else {
					std::cout << "O";
				}
			} else {
				std::cout << " ";
			}
		}
		std::cout << "#\n";  // Right border
	}

	// Bottom border
	for (int x = 0; x < cols + 2; ++x) {
		std::cout << "#";
	}
	std::cout << "\n";

	// Info
	std::cout << "Score: " << state.getScore() << "\n";
	std::cout << "Best: " << state.getBestScore() << "\n";
	std::cout << "Controls: WASD to move, Q to quit\n";
}

/**
 * Shows game over screen with statistics
 *
 * Parameters:
 * int finalScore: The final score
 * int bestScore: The best score
 * size_t totalGames: Total number of games played
 * double averageScore: Average score
 * WASDInputHandler& inputHandler: Reference to the input handler
 *
 * Returns bool: true if restart was requested (R key)
 */
bool TerminalRenderer::showGameOver(int finalScore, int bestScore, size_t totalGames,
                                   double averageScore, WASDInputHandler& inputHandler) {
	std::cout << "\n";
	std::cout << "==============================\n";
	std::cout << "         GAME OVER!           \n";
	std::cout << "                              \n";
	std::cout << "  Final Score:  " << std::setw(5) << finalScore << "\n";
	std::cout << "  Best Score:   " << std::setw(5) << bestScore << "\n";
	std::cout << "  Games Played: " << std::setw(5) << totalGames << "\n";
	std::cout << "  Average Score:" << std::setw(6) << std::fixed << std::setprecision(1) << averageScore << "\n";
	std::cout << "                              \n";
	std::cout << "  [R] Restart  [Q] Quit       \n";
	std::cout << "==============================\n";

	while (true) {
		char choice = inputHandler.readCharBlocking();
		if (choice == 'r' || choice == 'R') {
			return true;
		} else if (choice == 'q' || choice == 'Q') {
			return false;
		}
	}
}
