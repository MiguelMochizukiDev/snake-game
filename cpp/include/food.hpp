/**
 * food.hpp
 */

#pragma once

#include "entity.hpp"
#include "iboard.hpp"

/**
 * Food entity that can be consumed by the snake to grow
 * Input: None (class definition)
 * Output: None (class definition)
 */
class Food : public Entity {
public:
	/**
	 * Construct food on specified board
	 * Input: board - pointer to IBoard interface
	 * Output: None (constructor)
	 */
	explicit Food(IBoard* board);

	/**
	 * Get X coordinate of food
	 * Input: None
	 * Output: X coordinate as integer
	 */
	int getX() const override;

	/**
	 * Get Y coordinate of food
	 * Input: None
	 * Output: Y coordinate as integer
	 */
	int getY() const override;

	/**
	 * Set position of food on the board
	 * Input: x - X coordinate, y - Y coordinate
	 * Output: None (modifies food position)
	 */
	void setPosition(int x, int y) override;

	/**
	 * Get character symbol for display
	 * Input: None
	 * Output: Character '*' representing food
	 */
	char symbol() const override;

	/**
	 * Spawn food at random unoccupied position on board
	 * Input: None
	 * Output: None (modifies food position)
	 */
	void spawn();

private:
	IBoard* board_;  /* Pointer to board interface */
	int x_;          /* X coordinate of food */
	int y_;          /* Y coordinate of food */
};
