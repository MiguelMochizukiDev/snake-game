/**
 * terminal_renderer.hpp
 * Terminal-based renderer implementation
 */

#pragma once

#include "irenderer.hpp"

/**
 * TerminalRenderer renders game state to terminal/console
 * Follows Single Responsibility Principle - only handles terminal rendering
 * Input: None (class definition)
 * Output: None (class definition)
 */
class TerminalRenderer : public IRenderer {
public:
	/**
	 * Clear the terminal screen
	 * Input: None
	 * Output: None (clears terminal)
	 */
	void clear() const override;

	/**
	 * Render the board state to terminal
	 * Input: board - reference to game board state
	 * Output: None (displays to terminal)
	 */
	void render(const Board& board) const override;
};
