/**
 * score_manager.hpp
 * Author: Miguel Mochizuki Silva
 * Description: Score management and persistence
 */
#ifndef SCORE_MANAGER_HPP
#define SCORE_MANAGER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>

/**
 * Manages score persistence including best score and score history
 *
 * Attributes:
 * std::string dataDir_: Directory for storing score files
 * std::string historyFile_: Path to score history file
 * std::string bestFile_: Path to best score file
 * int bestScore_: Current best score
 * std::vector<int> scoreHistory_: History of all scores
 */
class ScoreManager {
private:
	std::string dataDir_;
	std::string historyFile_;
	std::string bestFile_;
	int bestScore_;
	std::vector<int> scoreHistory_;

	/**
	 * Creates data directory if it doesn't exist
	 */
	void createDataDirectory();

	/**
	 * Loads best score from file
	 */
	void loadBestScore();

	/**
	 * Loads score history from file
	 */
	void loadHistory();

public:
	/**
	 * Constructor for the ScoreManager class
	 */
	ScoreManager();

	/**
	 * Destructor for the ScoreManager class
	 */
	~ScoreManager() = default;

	/**
	 * Gets the average score from history
	 *
	 * Returns double: Average score, or 0 if no scores
	 */
	double getAverageScore() const;

	/**
	 * Gets the best score
	 *
	 * Returns int: The best score
	 */
	int getBestScore() const;

	/**
	 * Gets the score history
	 *
	 * Returns const std::vector<int>&: Const reference to score history
	 */
	const std::vector<int>& getHistory() const;

	/**
	 * Gets the total number of games played
	 *
	 * Returns size_t: Number of games
	 */
	size_t getTotalGames() const;

	/**
	 * Saves a new score
	 *
	 * Parameters:
	 * int score: The score to save
	 */
	void saveScore(int score);
};

#endif
