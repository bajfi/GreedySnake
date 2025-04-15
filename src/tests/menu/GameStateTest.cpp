#include "menu/GameState.h"
#include "menu/GameStateManager.h"
#include "renderer/Renderer.h"
#include <gtest/gtest.h>

using namespace GreedySnake;

// Mock renderer for testing
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
    bool isWindowOpen() const override
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
    void renderMenu(const std::string& title,
                    const std::vector<std::string>& items,
                    size_t selectedIndex) override
    {
    }
};

// Mock GameState implementation for testing
class MockGameState : public GameState
{
  public:
    // Track method calls
    bool enterCalled = false;
    bool exitCalled = false;
    bool processInputCalled = false;
    bool updateCalled = false;
    bool renderCalled = false;

    void enter() override
    {
        enterCalled = true;
    }
    void exit() override
    {
        exitCalled = true;
    }
    void processInput(Input input) override
    {
        processInputCalled = true;
    }
    void update(float deltaTime) override
    {
        updateCalled = true;
    }
    void render(Renderer& renderer) override
    {
        renderCalled = true;
    }
};

class GameStateTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }
};

TEST_F(GameStateTest, GameStateManagerInitialization)
{
    GameStateManager manager;
    // Initially, there should be no current state
    EXPECT_FALSE(manager.hasActiveState());
}

TEST_F(GameStateTest, ChangeState)
{
    GameStateManager manager;
    auto state1 = std::make_unique<MockGameState>();
    auto state2 = std::make_unique<MockGameState>();

    MockGameState* state1Ptr = state1.get();
    MockGameState* state2Ptr = state2.get();

    // Change to the first state
    manager.changeState(std::move(state1));
    EXPECT_TRUE(manager.hasActiveState());
    EXPECT_TRUE(state1Ptr->enterCalled);

    // Change to the second state
    manager.changeState(std::move(state2));
    EXPECT_TRUE(state1Ptr->exitCalled);
    EXPECT_TRUE(state2Ptr->enterCalled);
}

TEST_F(GameStateTest, PushAndPopState)
{
    GameStateManager manager;
    auto state1 = std::make_unique<MockGameState>();
    auto state2 = std::make_unique<MockGameState>();

    MockGameState* state1Ptr = state1.get();
    MockGameState* state2Ptr = state2.get();

    // Push the first state
    manager.pushState(std::move(state1));
    EXPECT_TRUE(manager.hasActiveState());
    EXPECT_TRUE(state1Ptr->enterCalled);

    // Push the second state
    manager.pushState(std::move(state2));
    EXPECT_TRUE(state2Ptr->enterCalled);
    // First state should not exit when another is pushed
    EXPECT_FALSE(state1Ptr->exitCalled);

    // Pop back to the first state
    manager.popState();
    EXPECT_TRUE(state2Ptr->exitCalled);
    EXPECT_TRUE(manager.hasActiveState());
}

TEST_F(GameStateTest, ProcessInputAndUpdate)
{
    GameStateManager manager;
    auto state = std::make_unique<MockGameState>();
    MockGameState* statePtr = state.get();

    manager.changeState(std::move(state));

    // Test that methods are forwarded to the current state
    Input input;
    manager.processInput(input);
    EXPECT_TRUE(statePtr->processInputCalled);

    float deltaTime = 0.016f;
    manager.update(deltaTime);
    EXPECT_TRUE(statePtr->updateCalled);
}

TEST_F(GameStateTest, RenderState)
{
    GameStateManager manager;
    auto state = std::make_unique<MockGameState>();
    MockGameState* statePtr = state.get();

    manager.changeState(std::move(state));

    // Create a mock renderer
    MockRenderer renderer;

    manager.render(renderer);
    EXPECT_TRUE(statePtr->renderCalled);
}