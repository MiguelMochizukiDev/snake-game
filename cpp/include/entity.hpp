/**
 * entity.hpp
 */

#pragma once

/**
 * Enumeration of entity types for fast type checking
 * Input: None (enum definition)
 * Output: None (enum definition)
 */
enum class EntityType {
    SNAKE_SEGMENT,
    FOOD
};

/**
 * Abstract base class for all game entities (snake segments, food)
 * Input: None (class definition)
 * Output: None (class definition)
 */
class Entity {
public:
	/**
	 * Get X coordinate of the entity
	 * Input: None
	 * Output: X coordinate as integer
	 */
	virtual int getX() const = 0;

	/**
	 * Get Y coordinate of the entity
	 * Input: None
	 * Output: Y coordinate as integer
	 */
	virtual int getY() const = 0;

	/**
	 * Set position of the entity on the board
	 * Input: x - X coordinate, y - Y coordinate
	 * Output: None (modifies entity position)
	 */
	virtual void setPosition(int x, int y) = 0;

	/**
	 * Get character symbol representing this entity on the board
	 * Input: None
	 * Output: Character symbol for display
	 */
	virtual char symbol() const = 0;

	/**
	 * Get the type of this entity (for fast RTTI replacement)
	 * Input: None
	 * Output: EntityType enum value
	 */
	virtual EntityType getType() const = 0;

	/**
	 * Virtual destructor for proper polymorphic cleanup
	 * Input: None
	 * Output: None
	 */
	virtual ~Entity() = default;
};
