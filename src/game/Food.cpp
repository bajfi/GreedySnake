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

    for (int y = 0; y < board.getHeight(); ++y)
    {
        for (int x = 0; x < board.getWidth(); ++x)
        {
            Position pos(x, y);
            if (board.getCellType(pos) == CellType::EMPTY && !snake.containsPosition(pos))
            {
                validPositions.push_back(pos);
            }
        }
    }

    // If no valid positions are available, return false
    if (validPositions.empty())
    {
        return false;
    }

    // Select a random position from valid positions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, validPositions.size() - 1);

    position = validPositions[dis(gen)];
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