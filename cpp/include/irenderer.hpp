/**
 * irenderer.hpp
 * Interface for rendering game state
 */

#pragma once

class Board;

/**
 * IRenderer interface for displaying game state
 * Follows Open/Closed Principle - easy to add new renderers (GUI, console, etc.)
 * Input: None (interface definition)
 * Output: None (interface definition)
 */
class IRenderer {
public:
	/**
	 * Clear the display
	 * Input: None
	 * Output: None (clears screen)
	 */
	virtual void clear() const = 0;

	/**
	 * Render the board state to display
	 * Input: board - reference to game board state
	 * Output: None (updates display)
	 */
	virtual void render(const Board& board) const = 0;

	/**
	 * Virtual destructor for proper polymorphic cleanup
	 * Input: None
	 * Output: None
	 */
	virtual ~IRenderer() = default;
};
