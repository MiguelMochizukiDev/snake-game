/**
 * score_manager.cpp
 * Author: Miguel Mochizuki Silva
 * Description: Score management and persistence implementation
 */
#include "score_manager.hpp"

#ifdef _WIN32
	#include <direct.h>
	#include <io.h>
	#define MKDIR(dir) _mkdir(dir)
#else
	#include <sys/stat.h>
	#include <unistd.h>
	#define MKDIR(dir) mkdir(dir, 0755)
#endif

/**
 * Constructor for the ScoreManager class
 */
ScoreManager::ScoreManager() : bestScore_(0) {
	dataDir_ = "data";
	historyFile_ = dataDir_ + "/score_history.txt";
	bestFile_ = dataDir_ + "/best_score.txt";

	createDataDirectory();
	loadBestScore();
	loadHistory();
}

/**
 * Creates data directory if it doesn't exist
 */
void ScoreManager::createDataDirectory() {
#ifdef _WIN32
	if (_access(dataDir_.c_str(), 0) == -1) {
		MKDIR(dataDir_.c_str());
	}
#else
	struct stat st;
	if (stat(dataDir_.c_str(), &st) == -1) {
		MKDIR(dataDir_.c_str());
	}
#endif
}

/**
 * Gets the average score from history
 *
 * Returns double: Average score, or 0 if no scores
 */
double ScoreManager::getAverageScore() const {
	if (scoreHistory_.empty()) {
		return 0.0;
	}

	int sum = 0;
	for (int score : scoreHistory_) {
		sum += score;
	}
	return static_cast<double>(sum) / scoreHistory_.size();
}

/**
 * Gets the best score
 *
 * Returns int: The best score
 */
int ScoreManager::getBestScore() const {
	return bestScore_;
}

/**
 * Gets the score history
 *
 * Returns const std::vector<int>&: Const reference to score history
 */
const std::vector<int>& ScoreManager::getHistory() const {
	return scoreHistory_;
}

/**
 * Gets the total number of games played
 *
 * Returns size_t: Number of games
 */
size_t ScoreManager::getTotalGames() const {
	return scoreHistory_.size();
}

/**
 * Loads best score from file
 */
void ScoreManager::loadBestScore() {
	std::ifstream file(bestFile_);
	if (file.is_open()) {
		file >> bestScore_;
		file.close();
	} else {
		bestScore_ = 0;
	}
}

/**
 * Loads score history from file
 */
void ScoreManager::loadHistory() {
	scoreHistory_.clear();
	std::ifstream file(historyFile_);
	if (file.is_open()) {
		int score;
		while (file >> score) {
			scoreHistory_.push_back(score);
		}
		file.close();
	}
}

/**
 * Saves a new score
 *
 * Parameters:
 * int score: The score to save
 */
void ScoreManager::saveScore(int score) {
	scoreHistory_.push_back(score);

	if (score > bestScore_) {
		bestScore_ = score;
	}

	std::ofstream bestFile(bestFile_);
	if (bestFile.is_open()) {
		bestFile << bestScore_ << "\n";
		bestFile.close();
	}

	std::ofstream historyFile(historyFile_, std::ios::app);
	if (historyFile.is_open()) {
		historyFile << score << "\n";
		historyFile.close();
	}
}
