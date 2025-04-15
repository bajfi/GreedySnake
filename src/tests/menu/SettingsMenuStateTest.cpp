#include "menu/SettingsMenuState.h"
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
                    size_t selectedIndex) override
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

class SettingsMenuStateTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        settings = std::make_unique<GameSettings>();
        stateManager = std::make_unique<GameStateManager>();
        settingsState = std::make_unique<SettingsMenuState>(stateManager.get(), settings.get());
        mockRenderer = std::make_unique<MockRenderer>();
    }

    void TearDown() override
    {
        settingsState.reset();
        stateManager.reset();
        settings.reset();
        mockRenderer.reset();
    }

    std::unique_ptr<GameSettings> settings;
    std::unique_ptr<GameStateManager> stateManager;
    std::unique_ptr<SettingsMenuState> settingsState;
    std::unique_ptr<MockRenderer> mockRenderer;
};

// Test initialization
TEST_F(SettingsMenuStateTest, Initialization)
{
    // Check initial settings
    EXPECT_NO_THROW(settingsState->enter());

    // Should have at least 7 menu items (speed, width, height, borders, sound, save, cancel)
    EXPECT_GE(settingsState->getMenuItemCount(), 7);
}

// Test menu navigation
TEST_F(SettingsMenuStateTest, MenuNavigation)
{
    settingsState->enter();

    // Test navigation
    settingsState->processInput(Input::DOWN);
    settingsState->processInput(Input::UP);

    // Renderer should be called but we don't have a way to verify directly
    // For now, just check that these calls don't crash
    EXPECT_NO_THROW(settingsState->render(*mockRenderer));
}

// Test settings changes
TEST_F(SettingsMenuStateTest, SettingsChanges)
{
    // Enter the menu state to initialize everything
    settingsState->enter();

    // Save original settings
    int originalSpeed = settings->getGameSpeed();

    // Get direct access to internal tempSettings through a special test method
    auto& tempSettings = settingsState->getTempSettingsForTest();

    // Directly modify the temporary settings (simulate what would happen when
    // the user interacts with the slider)
    tempSettings.setGameSpeed(originalSpeed + 1);

    // The main settings shouldn't be changed yet
    EXPECT_EQ(settings->getGameSpeed(), originalSpeed);

    // "Click" the Save Settings button by finding and executing it
    // Move down to the save button position (index 5)
    for (int i = 0; i < 5; i++)
    {
        settingsState->processInput(Input::DOWN);
    }

    // Press select on the "Save Settings" button
    settingsState->processInput(Input::SELECT);

    // Now the settings should be updated
    EXPECT_EQ(settings->getGameSpeed(), originalSpeed + 1);
}

// Test cancel operation
TEST_F(SettingsMenuStateTest, CancelOperation)
{
    settingsState->enter();

    // Save original settings
    int originalSpeed = settings->getGameSpeed();

    // Press enter on the current selection (should be game speed)
    settingsState->processInput(Input::SELECT);
    // Press right to increase value
    settingsState->processInput(Input::RIGHT);

    // Move to cancel button
    for (int i = 0; i < 7; i++)
    {
        settingsState->processInput(Input::DOWN);
    }

    // Press select on cancel button
    settingsState->processInput(Input::SELECT);

    // Settings should remain unchanged
    EXPECT_EQ(settings->getGameSpeed(), originalSpeed);
}