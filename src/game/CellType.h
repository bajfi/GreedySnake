#pragma once

namespace GreedySnake
{

/**
 * @brief Represents the type of cell on the game board
 */
enum class CellType
{
    EMPTY, // Empty cell
    SNAKE, // Cell occupied by snake
    FOOD,  // Cell containing food
    WALL   // Wall/boundary cell
};

} // namespace GreedySnake