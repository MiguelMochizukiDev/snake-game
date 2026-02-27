/**
 * game_controller.hpp
 */

#pragma once

#include "board.hpp"
#include "input_handler.hpp"
#include "constants.hpp"

#include <memory>

/**
 * Main game controller managing game loop, input, and rendering
 * Uses dependency injection for Board and InputHandler
 * Input: None (class definition)
 * Output: None (class definition)
 */
class GameController {
public:
	/**
	 * Construct game controller with board and input handler
	 * Input: board - shared pointer to Board, inputHandler - shared pointer to InputHandler
	 * Output: None (constructor)
	 */
	GameController(std::shared_ptr<Board> board,
	               std::shared_ptr<IInputHandler> inputHandler);

	/**
	 * Destructor to restore terminal state
	 * Input: None
	 * Output: None (destructor)
	 */
	~GameController();

	/**
	 * Start and run the main game loop
	 * Input: None
	 * Output: None (runs until game ends)
	 */
	void run();

private:
	/**
	 * Process keyboard input and update direction
	 * Input: None
	 * Output: None (modifies direction state)
	 */
	void processInput();

	/**
	 * Update game state for current frame
	 * Input: None
	 * Output: None (modifies game state)
	 */
	void update();

	/**
	 * Render current game state to terminal
	 * Input: None
	 * Output: None (updates terminal display)
	 */
	void render();

	/**
	 * Configure terminal for raw input mode
	 * Input: None
	 * Output: None (modifies terminal settings)
	 */
	void setupTerminal();

	/**
	 * Restore terminal to normal mode
	 * Input: None
	 * Output: None (restores terminal settings)
	 */
	void restoreTerminal();

	/**
	 * Read single character from input without blocking
	 * Input: c - reference to store character
	 * Output: true if character read, false otherwise
	 */
	bool readInput(char& c);

	std::shared_ptr<Board> board_;                  /* Game board instance */
	std::shared_ptr<IInputHandler> inputHandler_;   /* Input handler strategy */
	Direction direction_;                           /* Current snake movement direction */
	bool running_;                                  /* Game running status flag */
};
