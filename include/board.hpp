/**
 * board.hpp
 */

#pragma once

#include "iboard.hpp"
#include "entity.hpp"
#include "constants.hpp"
#include "score_manager.hpp"

#include <vector>
#include <memory>

class Food;
class Snake;

/**
 * Game board class managing grid, snake, and food entities
 * Implements IBoard interface for dependency inversion
 * Input: None (class definition)
 * Output: None (class definition)
 */
class Board : public IBoard {
public:
	/**
	 * Construct board with specified dimensions and score manager
	 * Input: length - board width, height - board height, scoreManager - score persistence handler
	 * Output: None (constructor)
	 */
	Board(int length = Config::LENGTH, int height = Config::HEIGHT,
	      std::shared_ptr<ScoreManager> scoreManager = std::make_shared<ScoreManager>());

	/**
	 * Destructor to clean up board resources
	 * Input: None
	 * Output: None (destructor)
	 */
	~Board();

	/**
	 * Get board width (IBoard implementation)
	 * Input: None
	 * Output: Board length as integer
	 */
	int getLength() const override;

	/**
	 * Get board height (IBoard implementation)
	 * Input: None
	 * Output: Board height as integer
	 */
	int getHeight() const override;

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
	 * Get const reference to the 2D grid of entity pointers
	 * Input: None
	 * Output: Const reference to grid vector
	 */
	const std::vector<std::vector<Entity*>>& getGrid() const;

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
	 * Check if a grid cell is occupied by an entity (IBoard implementation)
	 * Input: x - X coordinate, y - Y coordinate
	 * Output: true if occupied, false otherwise
	 */
	bool isOccupied(int x, int y) const override;

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
	 * Save best score using score manager
	 * Input: score - score value to save
	 * Output: None (delegates to ScoreManager)
	 */
	void saveBestScore(int score);

	/**
	 * Save final score to history using score manager
	 * Input: score - score value to save
	 * Output: None (delegates to ScoreManager)
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

	std::shared_ptr<ScoreManager> scoreManager_;   /* Score persistence handler */
};
