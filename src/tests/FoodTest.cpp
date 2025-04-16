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

    // Create a set of positions to leave empty
    std::vector<Position> emptyPositions;

    // Add a few positions that are not on the snake to remain empty
    emptyPositions.push_back(Position(1, 1));
    emptyPositions.push_back(Position(8, 8));

    // Fill most of the board with walls
    for (int y = 0; y < board.getHeight(); ++y)
    {
        for (int x = 0; x < board.getWidth(); ++x)
        {
            Position pos(x, y);

            // Skip the positions we want to keep empty
            bool keepEmpty = false;
            for (const auto& emptyPos : emptyPositions)
            {
                if (pos == emptyPos)
                {
                    keepEmpty = true;
                    break;
                }
            }

            // Also keep the snake positions empty
            if (keepEmpty || snake.containsPosition(pos))
            {
                continue;
            }

            // Fill the rest with walls
            board.setCellType(pos, CellType::WALL);
        }
    }

    // Generate food position
    EXPECT_TRUE(food.generatePosition(board, snake));

    // Food should be placed on one of our empty positions
    Position foodPos = food.getPosition();
    bool isOnValidPos = false;

    // Check if food is on one of our empty positions
    for (const auto& emptyPos : emptyPositions)
    {
        if (foodPos == emptyPos)
        {
            isOnValidPos = true;
            break;
        }
    }

    // If food is not on our empty positions, check it's not on the snake
    if (!isOnValidPos)
    {
        EXPECT_FALSE(snake.containsPosition(foodPos));

        // And check it's on an empty cell
        EXPECT_EQ(board.getCellType(foodPos), CellType::EMPTY);
    }
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