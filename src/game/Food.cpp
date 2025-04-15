#include "game/Food.h"
#include <random>
#include <vector>

namespace GreedySnake
{

Food::Food(int value) : value(value), position(0, 0)
{
}

bool Food::generatePosition(const Board& board, const Snake& snake)
{
    // Collect all valid positions (not on snake, not walls)
    std::vector<Position> validPositions;
    std::vector<Position> nonBorderPositions;

    for (int y = 0; y < board.getHeight(); ++y)
    {
        for (int x = 0; x < board.getWidth(); ++x)
        {
            Position pos(x, y);
            // Check if cell is empty and not part of the snake
            if (board.getCellType(pos) == CellType::EMPTY && !snake.containsPosition(pos))
            {
                // Add to all valid positions
                validPositions.push_back(pos);

                // Additionally track non-border positions for normal gameplay
                if (x > 0 && y > 0 && x < board.getWidth() - 1 && y < board.getHeight() - 1)
                {
                    nonBorderPositions.push_back(pos);
                }
            }
        }
    }

    // If no valid positions are available, return false
    if (validPositions.empty())
    {
        return false;
    }

    // For normal gameplay with standard board size, prefer non-border positions
    // but fall back to any valid position if necessary
    std::random_device rd;
    std::mt19937 gen(rd());

    if (!nonBorderPositions.empty() && board.getWidth() >= 10 && board.getHeight() >= 10)
    {
        // Use non-border positions for normal gameplay
        std::uniform_int_distribution<> dis(0, nonBorderPositions.size() - 1);
        position = nonBorderPositions[dis(gen)];
    }
    else
    {
        // For tests or if no non-border positions are available
        std::uniform_int_distribution<> dis(0, validPositions.size() - 1);
        position = validPositions[dis(gen)];
    }

    return true;
}

Position Food::getPosition() const
{
    return position;
}

int Food::getValue() const
{
    return value;
}

} // namespace GreedySnake