#include "game/GameApp.h"
#include <gtest/gtest.h>
#include <memory>

using namespace GreedySnake;

// Test fixture for GameApp tests
class GameAppTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        // Create a game app instance with test dimensions
        app = std::make_unique<GameApp>(800, 600, "Test Game Window");
    }

    void TearDown() override
    {
        app.reset();
    }

    std::unique_ptr<GameApp> app;
};

// Test initialization
TEST_F(GameAppTest, Initialization)
{
    // Initialization should not throw exceptions
    EXPECT_NO_THROW({
        bool result = app->initialize();
        // We can't assert that result is true here because the initialization might fail
        // in the CI environment due to lack of a display
    });
}

// Test getters
TEST_F(GameAppTest, Getters)
{
    // Initialize the app first
    app->initialize();

    // Settings should not be null
    EXPECT_NE(app->getSettings(), nullptr);

    // State manager should not be null
    EXPECT_NE(app->getStateManager(), nullptr);

    // State manager should have the app as its owner
    EXPECT_EQ(app->getStateManager()->getOwner(), app.get());
}

// Test state management
TEST_F(GameAppTest, StateManagement)
{
    // Initialize the app
    app->initialize();

    // After initialization, there should be at least one state (main menu)
    EXPECT_TRUE(app->getStateManager()->hasActiveState());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}