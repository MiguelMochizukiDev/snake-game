/**
 * score_manager.hpp
 * Handles persistent storage of game scores
 */

#pragma once

#include <string>

/**
 * ScoreManager class responsible for reading and writing scores to files
 * Follows Single Responsibility Principle - only handles persistence
 * Input: None (class definition)
 * Output: None (class definition)
 */
class ScoreManager {
public:
	/**
	 * Construct score manager with file paths
	 * Input: bestScoreFile - path to best score file, historyFile - path to score history file
	 * Output: None (constructor)
	 */
	ScoreManager(const std::string& bestScoreFile = "best_scores.txt",
	             const std::string& historyFile = "score_history.txt");

	/**
	 * Read best score from persistent storage
	 * Input: None
	 * Output: Best score as integer, 0 if file doesn't exist or on error
	 */
	int readBestScore() const;

	/**
	 * Save best score to persistent storage
	 * Input: score - score value to save
	 * Output: None (writes to file)
	 */
	void saveBestScore(int score) const;

	/**
	 * Append final score to history file
	 * Input: score - score value to save
	 * Output: None (appends to file)
	 */
	void saveFinalScore(int score) const;

private:
	std::string bestScoreFile_;   /* Path to best score file */
	std::string historyFile_;     /* Path to score history file */
};
