#include "game/Board.h"

namespace GreedySnake
{

Board::Board(int width, int height) : width(width), height(height)
{
    // Initialize the grid with the specified dimensions
    grid.resize(height, std::vector<CellType>(width, CellType::EMPTY));
    reset();
}

bool Board::isWithinBounds(const Position& position) const
{
    return position.x >= 0 && position.x < width && position.y >= 0 && position.y < height;
}

CellType Board::getCellType(const Position& position) const
{
    if (!isWithinBounds(position))
    {
        return CellType::WALL;
    }
    return grid[position.y][position.x];
}

bool Board::setCellType(const Position& position, CellType cellType)
{
    if (!isWithinBounds(position))
    {
        return false;
    }
    grid[position.y][position.x] = cellType;
    return true;
}

int Board::getWidth() const
{
    return width;
}

int Board::getHeight() const
{
    return height;
}

void Board::reset()
{
    // Set all cells to EMPTY
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            grid[y][x] = CellType::EMPTY;
        }
    }

    // Set border cells to WALL
    for (int x = 0; x < width; ++x)
    {
        grid[0][x] = CellType::WALL;          // Top border
        grid[height - 1][x] = CellType::WALL; // Bottom border
    }

    for (int y = 0; y < height; ++y)
    {
        grid[y][0] = CellType::WALL;         // Left border
        grid[y][width - 1] = CellType::WALL; // Right border
    }
}

} // namespace GreedySnake