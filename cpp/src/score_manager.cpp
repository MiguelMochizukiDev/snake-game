/**
 * score_manager.cpp
 */

#include "score_manager.hpp"

#include <fstream>
#include <string>

ScoreManager::ScoreManager(const std::string& bestScoreFile, const std::string& historyFile)
	: bestScoreFile_(bestScoreFile), historyFile_(historyFile) {}

int ScoreManager::readBestScore() const {
	std::ifstream file(bestScoreFile_);
	if (!file.is_open()) {
		return 0;
	}

	int score = 0;
	std::string line;
	while (std::getline(file, line)) {
		try {
			score = std::stoi(line);
		} catch (...) {
		}
	}

	file.close();
	return score;
}

void ScoreManager::saveBestScore(int score) const {
	std::ofstream file(bestScoreFile_);
	if (!file.is_open()) {
		return;
	}

	file << score << "\n";
	file.close();
}

void ScoreManager::saveFinalScore(int score) const {
	std::ofstream file(historyFile_, std::ios::app);
	if (!file.is_open()) {
		return;
	}

	file << score << "\n";
	file.close();
}
