#pragma once

#include "utils/Direction.h"
#include "utils/Position.h"
#include <vector>

namespace GreedySnake
{

/**
 * @brief Represents the player-controlled snake entity
 */
class Snake
{
  public:
    /**
     * @brief Constructor creates snake with initial position and length
     * @param initialPosition The starting position (head) of the snake
     * @param initialLength The initial length of the snake
     * @param initialDirection The initial direction of the snake
     */
    Snake(const Position& initialPosition = Position(0, 0),
          int initialLength = 3,
          Direction initialDirection = Direction::RIGHT);

    /**
     * @brief Move snake in the current direction
     * If the snake has grown in the previous step, it keeps the full length
     * @return The new position of the head
     */
    Position move();

    /**
     * @brief Increase snake length
     * The snake will grow by one segment in the next move
     */
    void grow();

    /**
     * @brief Change snake's direction
     * Cannot change to the opposite of the current direction
     * @param direction New direction
     * @return True if direction was changed, false if invalid direction
     */
    bool changeDirection(Direction direction);

    /**
     * @brief Get position of snake's head
     * @return Position of the head
     */
    [[nodiscard]] Position getHead() const;

    /**
     * @brief Get positions of all snake body segments
     * @return Vector of positions
     */
    [[nodiscard]] const std::vector<Position>& getBody() const;

    /**
     * @brief Check if snake has collided with itself
     * @return True if any body segment overlaps with the head
     */
    [[nodiscard]] bool checkSelfCollision() const;

    /**
     * @brief Check if a position is part of the snake's body
     * @param position Position to check
     * @return True if position is part of the snake
     */
    [[nodiscard]] bool containsPosition(const Position& position) const;

    /**
     * @brief Reset snake to initial state
     */
    void reset();

    /**
     * @brief Get the current direction of the snake
     * @return Current direction
     */
    [[nodiscard]] Direction getCurrentDirection() const;

  private:
    std::vector<Position> body;
    Direction currentDirection;
    bool hasGrown;
    Position initialPosition;
    int initialLength;
    Direction initialDirection;
};

} // namespace GreedySnake