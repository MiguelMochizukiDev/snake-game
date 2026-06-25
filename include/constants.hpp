/**
 * constants.hpp
 */

#pragma once

/**
 * Movement direction enumeration for snake navigation
 * Input: None (enum definition)
 * Output: None (enum definition)
 */
enum class Direction { UP, DOWN, LEFT, RIGHT };

/**
 * Game configuration constants namespace
 * Input: None (namespace definition)
 * Output: None (namespace definition)
 */
namespace Config {
	constexpr int LENGTH = 20;              /* Game board width in cells */
	constexpr int HEIGHT = 20;              /* Game board height in cells */
	constexpr int INITIAL_SNAKE_SIZE = 3;   /* Starting snake length */
	constexpr int GAME_SPEED_MS = 200;      /* Game loop delay in milliseconds */
}
