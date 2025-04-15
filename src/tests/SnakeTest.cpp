#include "game/Snake.h"
#include <gtest/gtest.h>

using namespace GreedySnake;

class SnakeTest : public ::testing::Test
{
  protected:
    // Default snake at position (5, 5) with length 3 and moving right
    Snake defaultSnake{Position(5, 5), 3, Direction::RIGHT};
};

// Test snake initialization
TEST_F(SnakeTest, Initialization)
{
    // Check the initial position, length, and direction
    EXPECT_EQ(defaultSnake.getHead(), Position(5, 5));
    EXPECT_EQ(defaultSnake.getBody().size(), 3);
    EXPECT_EQ(defaultSnake.getCurrentDirection(), Direction::RIGHT);

    // Test different initialization
    Snake customSnake(Position(10, 10), 5, Direction::DOWN);
    EXPECT_EQ(customSnake.getHead(), Position(10, 10));
    EXPECT_EQ(customSnake.getBody().size(), 5);
    EXPECT_EQ(customSnake.getCurrentDirection(), Direction::DOWN);
}

// Test snake movement
TEST_F(SnakeTest, Movement)
{
    // Initial position should be (5, 5)
    EXPECT_EQ(defaultSnake.getHead(), Position(5, 5));

    // Move right (current direction)
    Position newHead = defaultSnake.move();
    EXPECT_EQ(newHead, Position(6, 5));
    EXPECT_EQ(defaultSnake.getHead(), Position(6, 5));
    EXPECT_EQ(defaultSnake.getBody().size(), 3);

    // Change direction to down and move
    defaultSnake.changeDirection(Direction::DOWN);
    newHead = defaultSnake.move();
    EXPECT_EQ(newHead, Position(6, 6));
    EXPECT_EQ(defaultSnake.getHead(), Position(6, 6));
}

// Test direction changes
TEST_F(SnakeTest, DirectionChanges)
{
    // Test valid direction changes
    EXPECT_TRUE(defaultSnake.changeDirection(Direction::UP));
    EXPECT_EQ(defaultSnake.getCurrentDirection(), Direction::UP);

    EXPECT_TRUE(defaultSnake.changeDirection(Direction::RIGHT));
    EXPECT_EQ(defaultSnake.getCurrentDirection(), Direction::RIGHT);

    // Test invalid direction change (opposite of current)
    EXPECT_FALSE(defaultSnake.changeDirection(Direction::LEFT));
    EXPECT_EQ(defaultSnake.getCurrentDirection(), Direction::RIGHT);
}

// Test snake growth
TEST_F(SnakeTest, Growth)
{
    // Initial length is 3
    EXPECT_EQ(defaultSnake.getBody().size(), 3);

    // Move without growing
    defaultSnake.move();
    EXPECT_EQ(defaultSnake.getBody().size(), 3);

    // Call grow, then move
    defaultSnake.grow();
    defaultSnake.move();
    EXPECT_EQ(defaultSnake.getBody().size(), 4);

    // Regular move again (should not grow further)
    defaultSnake.move();
    EXPECT_EQ(defaultSnake.getBody().size(), 4);
}

// Test self-collision detection
TEST_F(SnakeTest, SelfCollision)
{
    // Create a snake that will circle back on itself
    Snake snake(Position(5, 5), 5, Direction::RIGHT);

    // No collision initially
    EXPECT_FALSE(snake.checkSelfCollision());

    // Move in a square pattern to create a collision
    snake.move(); // Right to (6, 5)
    snake.move(); // Right to (7, 5)

    snake.changeDirection(Direction::DOWN);
    snake.move(); // Down to (7, 6)

    snake.changeDirection(Direction::LEFT);
    snake.move(); // Left to (6, 6)

    snake.changeDirection(Direction::UP);
    snake.move(); // Up to (6, 5) - should collide with body

    EXPECT_TRUE(snake.checkSelfCollision());
}

// Test contains position
TEST_F(SnakeTest, ContainsPosition)
{
    // Create a snake with known positions
    Snake snake(Position(5, 5), 3, Direction::RIGHT);
    // Body should be [(5,5), (4,5), (3,5)]

    // Check head and body segments
    EXPECT_TRUE(snake.containsPosition(Position(5, 5))); // Head
    EXPECT_TRUE(snake.containsPosition(Position(4, 5))); // Body segment 1
    EXPECT_TRUE(snake.containsPosition(Position(3, 5))); // Body segment 2

    // Check positions that are not part of the snake
    EXPECT_FALSE(snake.containsPosition(Position(6, 5)));
    EXPECT_FALSE(snake.containsPosition(Position(5, 6)));
    EXPECT_FALSE(snake.containsPosition(Position(2, 5)));
}

// Test snake reset
TEST_F(SnakeTest, Reset)
{
    // Move and grow the snake
    defaultSnake.move();
    defaultSnake.grow();
    defaultSnake.move();
    defaultSnake.changeDirection(Direction::DOWN);

    // Reset the snake
    defaultSnake.reset();

    // Check that the snake is back to initial state
    EXPECT_EQ(defaultSnake.getHead(), Position(5, 5));
    EXPECT_EQ(defaultSnake.getBody().size(), 3);
    EXPECT_EQ(defaultSnake.getCurrentDirection(), Direction::RIGHT);
}