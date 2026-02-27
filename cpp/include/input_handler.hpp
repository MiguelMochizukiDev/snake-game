/**
 * input_handler.hpp
 * Interface for handling user input and direction mapping
 */

#pragma once

#include "constants.hpp"

/**
 * IInputHandler interface for processing input and mapping to directions
 * Follows Open/Closed Principle - easy to add new control schemes
 * Input: None (interface definition)
 * Output: None (interface definition)
 */
class IInputHandler {
public:
	/**
	 * Process input character and update direction if valid
	 * Input: c - input character, currentDirection - current snake direction
	 * Output: new direction based on input
	 */
	virtual Direction processInput(char c, Direction currentDirection) const = 0;

	/**
	 * Virtual destructor for proper polymorphic cleanup
	 * Input: None
	 * Output: None
	 */
	virtual ~IInputHandler() = default;
};

/**
 * WASDInputHandler implements WASD control scheme
 * Input: None (class definition)
 * Output: None (class definition)
 */
class WASDInputHandler : public IInputHandler {
public:
	/**
	 * Process input using WASD keys
	 * Input: c - input character, currentDirection - current snake direction
	 * Output: new direction based on WASD input
	 */
	Direction processInput(char c, Direction currentDirection) const override;
};
