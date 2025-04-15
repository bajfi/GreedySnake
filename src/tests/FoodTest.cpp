#include "game/Food.h"
#include "game/Board.h"
#include "game/Snake.h"
#include <gtest/gtest.h>

using namespace GreedySnake;

class FoodTest : public ::testing::Test
{
  protected:
    // Create test objects
    Board board{10, 10};
    Snake snake{Position(5, 5), 3, Direction::RIGHT};
    Food food{1};
};

// Test food initialization
TEST_F(FoodTest, Initialization)
{
    Food defaultFood;
    EXPECT_EQ(defaultFood.getValue(), 1);

    Food customFood(5);
    EXPECT_EQ(customFood.getValue(), 5);
}

// Test food generation on a mostly empty board
TEST_F(FoodTest, GeneratePosition)
{
    // Reset the board to ensure it's empty
    board.reset();

    // Generate food position
    EXPECT_TRUE(food.generatePosition(board, snake));

    // Check that the food position is within bounds
    Position foodPos = food.getPosition();
    EXPECT_TRUE(board.isWithinBounds(foodPos));

    // Check that the food isn't on the snake
    EXPECT_FALSE(snake.containsPosition(foodPos));
}

// Test food generation on a nearly full board
TEST_F(FoodTest, GeneratePositionNearlyFull)
{
    // Reset the board
    board.reset();

    // Fill almost the entire board with walls
    for (int y = 0; y < board.getHeight(); ++y)
    {
        for (int x = 0; x < board.getWidth(); ++x)
        {
            // Leave only one cell empty for the food (not on the snake)
            if (x != 0 || y != 0 || snake.containsPosition(Position(x, y)))
            {
                board.setCellType(Position(x, y), CellType::WALL);
            }
        }
    }

    // Generate food position - should find the one empty spot
    EXPECT_TRUE(food.generatePosition(board, snake));
    EXPECT_EQ(food.getPosition(), Position(0, 0));
}

// Test food generation when there's no valid position
TEST_F(FoodTest, GeneratePositionNoValidSpot)
{
    // Reset the board
    board.reset();

    // Fill the entire board with walls
    for (int y = 0; y < board.getHeight(); ++y)
    {
        for (int x = 0; x < board.getWidth(); ++x)
        {
            board.setCellType(Position(x, y), CellType::WALL);
        }
    }

    // Try to generate food position - should fail
    EXPECT_FALSE(food.generatePosition(board, snake));
}