#pragma once

#include "game/CellType.h"
#include "utils/Position.h"
#include <vector>

namespace GreedySnake
{

/**
 * @brief Represents the game board/grid where the game takes place
 */
class Board
{
  public:
    /**
     * @brief Constructor creates board with specified dimensions
     * @param width Width of the board
     * @param height Height of the board
     */
    Board(int width, int height);

    /**
     * @brief Check if position is within board boundaries
     * @param position Position to check
     * @return True if position is within bounds
     */
    [[nodiscard]] bool isWithinBounds(const Position& position) const;

    /**
     * @brief Get cell type at the specified position
     * @param position Position to check
     * @return Cell type at the position (WALL if out of bounds)
     */
    [[nodiscard]] CellType getCellType(const Position& position) const;

    /**
     * @brief Set cell type at the specified position
     * @param position Position to set
     * @param cellType Cell type to set
     * @return True if successful, false if out of bounds
     */
    bool setCellType(const Position& position, CellType cellType);

    /**
     * @brief Get the board width
     * @return Width of the board
     */
    [[nodiscard]] int getWidth() const;

    /**
     * @brief Get the board height
     * @return Height of the board
     */
    [[nodiscard]] int getHeight() const;

    /**
     * @brief Reset board to initial state
     * Sets all cells to EMPTY except the border cells which are set to WALL
     */
    void reset();

  private:
    int width;
    int height;
    std::vector<std::vector<CellType>> grid;
};

} // namespace GreedySnake