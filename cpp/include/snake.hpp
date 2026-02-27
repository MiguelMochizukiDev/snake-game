/**
 * snake.hpp
 */

#pragma once

#include "entity.hpp"
#include "iboard.hpp"
#include "constants.hpp"

#include <vector>
#include <memory>

/**
 * Single segment of the snake body, inherits from Entity
 * Input: None (class definition)
 * Output: None (class definition)
 */
class SnakeSegment : public Entity {
public:
	/**
	 * Construct snake segment at specified position
	 * Input: x - X coordinate, y - Y coordinate
	 * Output: None (constructor)
	 */
	SnakeSegment(int x, int y);

	/**
	 * Get X coordinate of segment
	 * Input: None
	 * Output: X coordinate as integer
	 */
	int getX() const override;

	/**
	 * Get Y coordinate of segment
	 * Input: None
	 * Output: Y coordinate as integer
	 */
	int getY() const override;

	/**
	 * Set position of segment on the board
	 * Input: x - X coordinate, y - Y coordinate
	 * Output: None (modifies segment position)
	 */
	void setPosition(int x, int y) override;

	/**
	 * Get character symbol for display
	 * Input: None
	 * Output: Character 'O' representing snake body
	 */
	char symbol() const override;

private:
	int x_;    /* X coordinate of segment */
	int y_;    /* Y coordinate of segment */
};

/**
 * Snake entity containing linked segments and movement logic
 * Input: None (class definition)
 * Output: None (class definition)
 */
class Snake {
public:
	/**
	 * Construct snake on specified board
	 * Input: board - pointer to IBoard interface
	 * Output: None (constructor)
	 */
	explicit Snake(IBoard* board);

	/**
	 * Move snake in specified direction, handle collisions
	 * Input: direction - movement direction
	 * Output: None (modifies snake position)
	 */
	void move(Direction direction);

	/**
	 * Grow snake by adding a new segment at the tail
	 * Input: None
	 * Output: None (adds segment to snake)
	 */
	void grow();

	/**
	 * Get const reference to snake segments vector
	 * Input: None
	 * Output: Const reference to segments vector
	 */
	const std::vector<std::unique_ptr<SnakeSegment>>& getSegments() const;

private:
	IBoard* board_;                                         /* Pointer to board interface */
	std::vector<std::unique_ptr<SnakeSegment>> segments_;   /* Snake body segments */
};
