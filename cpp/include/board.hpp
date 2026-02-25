/**
 * board.hpp
 */

#pragma once

#include "entity.hpp"
#include "constants.hpp"

#include <vector>
#include <memory>

class Food;
class Snake;

/**
 * Game board class managing grid, snake, and food entities
 * Input: None (class definition)
 * Output: None (class definition)
 */
class Board {
public:
	/**
	 * Construct board with specified dimensions
	 * Input: length - board width, height - board height
	 * Output: None (constructor)
	 */
	Board(int length = Config::LENGTH, int height = Config::HEIGHT);

	/**
	 * Destructor to clean up board resources
	 * Input: None
	 * Output: None (destructor)
	 */
	~Board();

	/**
	 * Get board width
	 * Input: None
	 * Output: Board length as integer
	 */
	int getLength() const;

	/**
	 * Get board height
	 * Input: None
	 * Output: Board height as integer
	 */
	int getHeight() const;

	/**
	 * Get pointer to food entity
	 * Input: None
	 * Output: Pointer to Food object
	 */
	Food* getFood() const;

	/**
	 * Get pointer to snake entity
	 * Input: None
	 * Output: Pointer to Snake object
	 */
	Snake* getSnake() const;

	/**
	 * Get reference to the 2D grid of entity pointers
	 * Input: None
	 * Output: Reference to grid vector
	 */
	std::vector<std::vector<Entity*>>& getGrid();

	/**
	 * Synchronize entity positions with the grid representation
	 * Input: None
	 * Output: None (updates grid state)
	 */
	void sync();

	/**
	 * Update game state by moving snake in specified direction
	 * Input: direction - movement direction for snake
	 * Output: None (modifies game state)
	 */
	void update(Direction direction);

	/**
	 * Render the current board state to terminal
	 * Input: None
	 * Output: None (updates terminal display)
	 */
	void render() const;

	/**
	 * Check if a grid cell is occupied by an entity
	 * Input: x - X coordinate, y - Y coordinate
	 * Output: true if occupied, false otherwise
	 */
	bool isOccupied(int x, int y) const;

	/**
	 * Get current game score
	 * Input: None
	 * Output: Current score as integer
	 */
	int getScore() const;

	/**
	 * Get best score from previous games
	 * Input: None
	 * Output: Best score as integer
	 */
	int getBestScore() const;

	/**
	 * Read best score from file
	 * Input: None
	 * Output: Best score as integer, 0 if file doesn't exist
	 */
	int readBestScore();

	/**
	 * Save best score to file
	 * Input: score - score value to save
	 * Output: None (writes to file)
	 */
	void saveBestScore(int score);

	/**
	 * Save final score to history file
	 * Input: score - score value to save
	 * Output: None (appends to file)
	 */
	void saveFinalScore(int score);

private:
	int length_;                                   /* Board width in cells */
	int height_;                                   /* Board height in cells */
	std::vector<std::vector<Entity*>> grid_;       /* 2D grid of entity pointers */

	std::unique_ptr<Food> food_;                   /* Owned food entity */
	std::unique_ptr<Snake> snake_;                 /* Owned snake entity */

	int score_;                                    /* Current game score */
	int bestScore_;                                /* Best score from previous games */
};
