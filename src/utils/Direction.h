#pragma once

namespace GreedySnake
{

/**
 * @brief Represents the direction of snake movement
 */
enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
 * @brief Gets the opposite direction
 * @param dir The input direction
 * @return The opposite direction
 */
inline Direction getOppositeDirection(Direction dir)
{
    switch (dir)
    {
    case Direction::UP:
        return Direction::DOWN;
    case Direction::DOWN:
        return Direction::UP;
    case Direction::LEFT:
        return Direction::RIGHT;
    case Direction::RIGHT:
        return Direction::LEFT;
    default:
        return dir;
    }
}

} // namespace GreedySnake