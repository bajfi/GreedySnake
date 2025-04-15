#pragma once

#include "game/Board.h"
#include "game/Snake.h"
#include "utils/Position.h"

namespace GreedySnake
{

/**
 * @brief Represents the food that the snake consumes
 */
class Food
{
  public:
    /**
     * @brief Constructor
     * @param value The point value of the food (default: 1)
     */
    Food(int value = 1);

    /**
     * @brief Generate a new random position for food
     * Ensures food isn't placed on the snake or walls
     * @param board Reference to the game board
     * @param snake Reference to the snake
     * @return True if a valid position was found, false otherwise
     */
    bool generatePosition(const Board& board, const Snake& snake);

    /**
     * @brief Get current position of food
     * @return Position of the food
     */
    [[nodiscard]] Position getPosition() const;

    /**
     * @brief Get value/points of current food
     * @return Point value of the food
     */
    [[nodiscard]] int getValue() const;

  private:
    Position position;
    int value;
};

} // namespace GreedySnake