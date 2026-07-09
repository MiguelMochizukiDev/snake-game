/**
 * terminal_renderer.hpp
 * Author: Miguel Mochizuki Silva
 * Description: Terminal renderer class
 */
#ifndef TERMINAL_RENDERER_HPP
#define TERMINAL_RENDERER_HPP

#include "game_state.hpp"

// Forward declaration
class WASDInputHandler;

/**
 * Renders game state to terminal/console
 */
class TerminalRenderer {
public:
	/**
	 * Constructor for the TerminalRenderer class
	 */
	TerminalRenderer() = default;

	/**
	 * Destructor for the TerminalRenderer class
	 */
	~TerminalRenderer() = default;

	/**
	 * Clears the terminal screen
	 */
	void clear();

	/**
	 * Renders the game state
	 *
	 * Parameters:
	 * const GameState& state: The game state to render
	 */
	void render(const GameState& state);

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
	bool showGameOver(int finalScore, int bestScore, size_t totalGames,
	                  double averageScore, WASDInputHandler& inputHandler);
};

#endif
