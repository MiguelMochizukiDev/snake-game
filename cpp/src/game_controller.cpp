/**
 * game_controller.cpp
 */

#include "game_controller.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#ifdef _WIN32
	#include <conio.h>
#else
	#include <termios.h>
	#include <unistd.h>
	#include <fcntl.h>
	static struct termios original;
	static int originalFlags;
#endif

GameController::GameController(int width, int height)
	: board_(width, height),
	  direction_(Direction::RIGHT),
	  running_(true) {
	setupTerminal();
}

GameController::~GameController() {
	restoreTerminal();
}

void GameController::setupTerminal() {
#ifndef _WIN32
	tcgetattr(STDIN_FILENO, &original);

	struct termios raw = original;
	raw.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

	originalFlags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, originalFlags | O_NONBLOCK);
#endif
}

void GameController::restoreTerminal() {
#ifndef _WIN32
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
	fcntl(STDIN_FILENO, F_SETFL, originalFlags);
#endif
}

bool GameController::readInput(char& c) {
#ifdef _WIN32
	if (_kbhit()) {
		c = _getch();
		return true;
	}
	return false;
#else
	if (read(STDIN_FILENO, &c, 1) > 0)
		return true;
	return false;
#endif
}

void GameController::run() {
	while (running_) {
		try {
			processInput();
			update();
			render();

			std::this_thread::sleep_for(
				std::chrono::milliseconds(Config::GAME_SPEED_MS)
			);

		} catch (const std::runtime_error&) {
			running_ = false;
		}
	}

	int finalScore = board_.getScore();
	int bestScore = board_.getBestScore();

	board_.saveFinalScore(finalScore);

	if (finalScore == bestScore && finalScore > 0) {
		board_.saveBestScore(bestScore);
	}

#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	board_.render();

	std::cout << "\nGame Over! Press \"enter\" to exit...\n";

	restoreTerminal();

	std::string line;
	std::getline(std::cin, line);

	std::cout << "Game Over! Final Score: " << finalScore << "\n";
}

void GameController::processInput() {
	char c;

	if (readInput(c)) {
		if ((c == 'w' || c == 'W') && direction_ != Direction::DOWN)  direction_ = Direction::UP;
		if ((c == 's' || c == 'S') && direction_ != Direction::UP)    direction_ = Direction::DOWN;
		if ((c == 'a' || c == 'A') && direction_ != Direction::RIGHT) direction_ = Direction::LEFT;
		if ((c == 'd' || c == 'D') && direction_ != Direction::LEFT)  direction_ = Direction::RIGHT;
	}
}

void GameController::update() {
	board_.update(direction_);
}

void GameController::render() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	board_.render();
}
