#include "input/InputHandler.h"
#include <gtest/gtest.h>

using namespace GreedySnake;

class InputHandlerTest : public ::testing::Test
{
  protected:
    InputHandler inputHandler;
};

// Test initial state
TEST_F(InputHandlerTest, InitialState)
{
    EXPECT_EQ(inputHandler.getInput(), Direction::RIGHT); // Default direction
    EXPECT_FALSE(inputHandler.isQuitRequested());
}

// Test direction changes
TEST_F(InputHandlerTest, DirectionChanges)
{
    // Process key presses and check direction changes
    inputHandler.processKeyPress(119); // W (UP)
    EXPECT_EQ(inputHandler.getInput(), Direction::UP);

    inputHandler.processKeyPress(115); // S (DOWN)
    EXPECT_EQ(inputHandler.getInput(), Direction::DOWN);

    inputHandler.processKeyPress(97); // A (LEFT)
    EXPECT_EQ(inputHandler.getInput(), Direction::LEFT);

    inputHandler.processKeyPress(100); // D (RIGHT)
    EXPECT_EQ(inputHandler.getInput(), Direction::RIGHT);
}

// Test quit request
TEST_F(InputHandlerTest, QuitRequest)
{
    EXPECT_FALSE(inputHandler.isQuitRequested());

    inputHandler.processKeyPress(113); // Q (QUIT)
    EXPECT_TRUE(inputHandler.isQuitRequested());

    // Reset should clear the quit request
    inputHandler.reset();
    EXPECT_FALSE(inputHandler.isQuitRequested());
}

// Test invalid key presses
TEST_F(InputHandlerTest, InvalidKeyPress)
{
    // Set a known direction first
    inputHandler.processKeyPress(100); // D (RIGHT)
    EXPECT_EQ(inputHandler.getInput(), Direction::RIGHT);

    // Press an invalid key, direction should not change
    inputHandler.processKeyPress(200); // Invalid key code
    EXPECT_EQ(inputHandler.getInput(), Direction::RIGHT);
}

// Test reset function
TEST_F(InputHandlerTest, Reset)
{
    // Change direction and set quit flag
    inputHandler.processKeyPress(119); // W (UP)
    inputHandler.processKeyPress(113); // Q (QUIT)

    EXPECT_EQ(inputHandler.getInput(), Direction::UP);
    EXPECT_TRUE(inputHandler.isQuitRequested());

    // Reset should restore defaults
    inputHandler.reset();
    EXPECT_EQ(inputHandler.getInput(), Direction::RIGHT);
    EXPECT_FALSE(inputHandler.isQuitRequested());
}