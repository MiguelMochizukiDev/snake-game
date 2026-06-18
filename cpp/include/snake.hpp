/**
 * snake.hpp
 */

#pragma once

#include "entity.hpp"
#include "iboard.hpp"
#include "constants.hpp"

#include <deque>
#include <memory>

/**
 * Single segment of the snake body, inherits from Entity
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
 * Snake entity containing deque of segments and movement logic
 * Uses std::deque for O(1) head insertion and tail removal
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
	* Move snake in specified direction, handle collisions and food
	* Input: direction - movement direction
	*        foodX, foodY - current food position
	* Output: Returns true if food was eaten (grow mode), false otherwise
	*         Throws runtime_error on collision
	*/
	bool move(Direction direction, int foodX, int foodY);

	/**
	 * Mark snake to grow on next move (food was eaten)
	 * Input: None
	 * Output: None (sets internal flag)
	 */
	void setGrow();

	/**
	 * Get const reference to snake segments deque
	 * Input: None
	 * Output: Const reference to segments deque
	 */
	const std::deque<std::unique_ptr<SnakeSegment>>& getSegments() const;

	/**
	 * Get pointer to head segment
	 * Input: None
	 * Output: Pointer to head segment, nullptr if empty
	 */
	const SnakeSegment* getHead() const;

	/**
	 * Get pointer to tail segment
	 * Input: None
	 * Output: Pointer to tail segment, nullptr if empty
	 */
	const SnakeSegment* getTail() const;

	/**
	 * Get current snake length
	 * Input: None
	 * Output: Number of segments
	 */
	size_t getLength() const;

private:
	IBoard* board_;                                         /* Pointer to board interface */
	std::deque<std::unique_ptr<SnakeSegment>> segments_;   /* Snake body segments (deque for O(1) ops) */
	bool shouldGrow_;                                       /* Flag to grow on next move */
};
