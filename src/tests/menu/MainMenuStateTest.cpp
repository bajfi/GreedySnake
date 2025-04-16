#include "menu/MainMenuState.h"
#include "menu/GameStateManager.h"
#include "renderer/Renderer.h"
#include <gtest/gtest.h>
#include <memory>

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
    void renderMenu(const std::string& title,
                    const std::vector<std::string>& items,
                    size_t selectedIndex,
                    const std::string& instructions = "") override
    {
        lastTitle = title;
        lastItems = items;
        lastSelectedIndex = selectedIndex;
        lastInstructions = instructions;
    }

    std::string lastTitle;
    std::vector<std::string> lastItems;
    size_t lastSelectedIndex = 0;
    std::string lastInstructions;
};

class MainMenuStateTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        // Set up the test environment
        stateManager = std::make_unique<GameStateManager>();
        mainMenuState = std::make_unique<MainMenuState>(stateManager.get());

        // Initialize the menu items
        mainMenuState->enter();
    }

    // Mock renderer for testing
    MockRenderer renderer;
    std::unique_ptr<GameStateManager> stateManager;
    std::unique_ptr<MainMenuState> mainMenuState;
};

TEST_F(MainMenuStateTest, ConstructorInitializesMenu)
{
    // Verify that the menu has been properly initialized with items
    ASSERT_GT(mainMenuState->getMenuItemCount(), 0);
}

TEST_F(MainMenuStateTest, ProcessInputHandlesMenuNavigation)
{
    // Get the initial selected index
    int initialIndex = mainMenuState->getSelectedIndex();

    // Create down input to navigate down in the menu
    Input downInput = Input::DOWN;

    // Process the input
    mainMenuState->processInput(downInput);

    // Verify that the selected index has changed
    EXPECT_NE(mainMenuState->getSelectedIndex(), initialIndex);

    // Create up input to navigate up in the menu
    Input upInput = Input::UP;

    // Process the input and verify we go back to the initial index
    mainMenuState->processInput(upInput);
    EXPECT_EQ(mainMenuState->getSelectedIndex(), initialIndex);
}

TEST_F(MainMenuStateTest, ProcessInputHandlesSelection)
{
    // Create select input to select the current menu item
    Input selectInput = Input::SELECT;

    // This should trigger some action, but since we can't easily test the actual
    // action being performed, we'll just make sure it doesn't crash
    ASSERT_NO_THROW(mainMenuState->processInput(selectInput));
}

TEST_F(MainMenuStateTest, EnterAndExitDoNotCrash)
{
    // Make sure the enter and exit methods don't crash
    ASSERT_NO_THROW(mainMenuState->enter());
    ASSERT_NO_THROW(mainMenuState->exit());
}

TEST_F(MainMenuStateTest, UpdateDoesNotCrash)
{
    // Make sure the update method doesn't crash
    ASSERT_NO_THROW(mainMenuState->update(0.016f));
}

TEST_F(MainMenuStateTest, RenderDoesNotCrash)
{
    // Make sure the render method doesn't crash
    ASSERT_NO_THROW(mainMenuState->render(renderer));
}