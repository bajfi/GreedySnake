#include "menu/GamePlayState.h"
#include "menu/GameStateManager.h"
#include "settings/GameSettings.h"
#include <gtest/gtest.h>
#include <memory>

using namespace GreedySnake;

// Mock Renderer for testing
class MockRenderer : public Renderer
{
  public:
    bool initialize() override
    {
        return true;
    }
    void shutdown() override
    {
    }
    void render(const Game& game) override
    {
    }
    void renderMenu(const std::string& title,
                    const std::vector<std::string>& items,
                    size_t selectedIndex,
                    const std::string& instructions = "") override
    {
    }
    [[nodiscard]] bool isWindowOpen() const override
    {
        return true;
    }
    bool handleEvents(Game& game) override
    {
        return true;
    }
    bool handleEvents(Input& input) override
    {
        return true;
    }
};

// Test fixture for GamePlayState
class GamePlayStateTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        settings = std::make_unique<GameSettings>();
        // Configure settings for testing
        settings->setGameSpeed(5);
        settings->setBoardWidth(20);
        settings->setBoardHeight(20);
        settings->setBorders(true);
        settings->setSoundEnabled(true);

        stateManager = std::make_unique<GameStateManager>();
        gamePlayState = std::make_unique<GamePlayState>(stateManager.get(), settings.get());
        mockRenderer = std::make_unique<MockRenderer>();

        gamePlayState->enter(); // Initialize the game state
    }

    void TearDown() override
    {
        gamePlayState.reset();
        stateManager.reset();
        settings.reset();
        mockRenderer.reset();
    }

    std::unique_ptr<GameSettings> settings;
    std::unique_ptr<GameStateManager> stateManager;
    std::unique_ptr<GamePlayState> gamePlayState;
    std::unique_ptr<MockRenderer> mockRenderer;
};

// Test initialization
TEST_F(GamePlayStateTest, Initialization)
{
    // After initialization, game should not be paused or over
    EXPECT_FALSE(gamePlayState->isPaused());
    EXPECT_FALSE(gamePlayState->isGameOver());

    // Score should be 0
    EXPECT_EQ(gamePlayState->getScore(), 0);
}

// Test pausing
TEST_F(GamePlayStateTest, Pausing)
{
    // Initially not paused
    EXPECT_FALSE(gamePlayState->isPaused());

    // Pause the game
    gamePlayState->processInput(Input::PAUSE);
    EXPECT_TRUE(gamePlayState->isPaused());

    // Unpause the game
    gamePlayState->processInput(Input::PAUSE);
    EXPECT_FALSE(gamePlayState->isPaused());
}

// Test movement
TEST_F(GamePlayStateTest, Movement)
{
    // Test that we can process movement inputs without crashing
    EXPECT_NO_THROW(gamePlayState->processInput(Input::UP));
    EXPECT_NO_THROW(gamePlayState->processInput(Input::DOWN));
    EXPECT_NO_THROW(gamePlayState->processInput(Input::LEFT));
    EXPECT_NO_THROW(gamePlayState->processInput(Input::RIGHT));
}

// Test rendering
TEST_F(GamePlayStateTest, Rendering)
{
    // Make sure rendering doesn't crash
    EXPECT_NO_THROW(gamePlayState->render(*mockRenderer));
}

// Test update
TEST_F(GamePlayStateTest, Update)
{
    // Update should not crash
    EXPECT_NO_THROW(gamePlayState->update(0.1f));

    // Update several times to simulate gameplay
    for (int i = 0; i < 10; i++)
    {
        gamePlayState->update(0.1f);
    }

    // Game should still be running
    EXPECT_FALSE(gamePlayState->isGameOver());
}