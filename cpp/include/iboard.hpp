/**
 * iboard.hpp
 * Interface for board operations needed by game entities
 */

#pragma once

/**
 * IBoard interface defining board operations for game entities
 * Follows Dependency Inversion Principle - entities depend on abstraction
 * Input: None (interface definition)
 * Output: None (interface definition)
 */
class IBoard {
public:
	/**
	 * Get board width
	 * Input: None
	 * Output: Board length as integer
	 */
	virtual int getLength() const = 0;

	/**
	 * Get board height
	 * Input: None
	 * Output: Board height as integer
	 */
	virtual int getHeight() const = 0;

	/**
	 * Check if a grid cell is occupied by an entity
	 * Input: x - X coordinate, y - Y coordinate
	 * Output: true if occupied or out of bounds, false otherwise
	 */
	virtual bool isOccupied(int x, int y) const = 0;

	/**
	 * Virtual destructor for proper polymorphic cleanup
	 * Input: None
	 * Output: None
	 */
	virtual ~IBoard() = default;
};
