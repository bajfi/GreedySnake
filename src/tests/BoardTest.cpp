#include "game/Board.h"
#include <gtest/gtest.h>

using namespace GreedySnake;

class BoardTest : public ::testing::Test
{
  protected:
    // Create a standard test board (10x10)
    Board standardBoard{10, 10};

    // Create a small test board (3x3)
    Board smallBoard{3, 3};
};

// Test board initialization
TEST_F(BoardTest, Initialization)
{
    EXPECT_EQ(standardBoard.getWidth(), 10);
    EXPECT_EQ(standardBoard.getHeight(), 10);
    EXPECT_EQ(smallBoard.getWidth(), 3);
    EXPECT_EQ(smallBoard.getHeight(), 3);
}

// Test boundary checking
TEST_F(BoardTest, BoundaryChecking)
{
    // Valid positions
    EXPECT_TRUE(standardBoard.isWithinBounds(Position(0, 0)));
    EXPECT_TRUE(standardBoard.isWithinBounds(Position(5, 5)));
    EXPECT_TRUE(standardBoard.isWithinBounds(Position(9, 9)));

    // Invalid positions
    EXPECT_FALSE(standardBoard.isWithinBounds(Position(-1, 0)));
    EXPECT_FALSE(standardBoard.isWithinBounds(Position(0, -1)));
    EXPECT_FALSE(standardBoard.isWithinBounds(Position(10, 5)));
    EXPECT_FALSE(standardBoard.isWithinBounds(Position(5, 10)));
}

// Test cell types setting and getting
TEST_F(BoardTest, CellTypes)
{
    // Initialize all cells to EMPTY
    standardBoard.reset();

    // Test a few cells are EMPTY after reset
    EXPECT_EQ(standardBoard.getCellType(Position(1, 1)), CellType::EMPTY);
    EXPECT_EQ(standardBoard.getCellType(Position(5, 5)), CellType::EMPTY);
    EXPECT_EQ(standardBoard.getCellType(Position(8, 8)), CellType::EMPTY);

    // Set and verify cell types
    EXPECT_TRUE(standardBoard.setCellType(Position(1, 1), CellType::SNAKE));
    EXPECT_TRUE(standardBoard.setCellType(Position(5, 5), CellType::FOOD));
    EXPECT_TRUE(standardBoard.setCellType(Position(8, 8), CellType::WALL));

    EXPECT_EQ(standardBoard.getCellType(Position(1, 1)), CellType::SNAKE);
    EXPECT_EQ(standardBoard.getCellType(Position(5, 5)), CellType::FOOD);
    EXPECT_EQ(standardBoard.getCellType(Position(8, 8)), CellType::WALL);

    // Test out of bounds setting returns false
    EXPECT_FALSE(standardBoard.setCellType(Position(-1, 0), CellType::SNAKE));
    EXPECT_FALSE(standardBoard.setCellType(Position(10, 10), CellType::FOOD));

    // Test out of bounds getting returns WALL
    EXPECT_EQ(standardBoard.getCellType(Position(-1, 0)), CellType::WALL);
    EXPECT_EQ(standardBoard.getCellType(Position(10, 10)), CellType::WALL);
}

// Test board reset
TEST_F(BoardTest, Reset)
{
    // Set some cells to non-empty
    standardBoard.setCellType(Position(1, 1), CellType::SNAKE);
    standardBoard.setCellType(Position(5, 5), CellType::FOOD);

    // Reset the board
    standardBoard.reset();

    // Check that cells are now EMPTY
    EXPECT_EQ(standardBoard.getCellType(Position(1, 1)), CellType::EMPTY);
    EXPECT_EQ(standardBoard.getCellType(Position(5, 5)), CellType::EMPTY);
}