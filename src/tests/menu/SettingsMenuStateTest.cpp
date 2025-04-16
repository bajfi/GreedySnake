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

// Test Game Speed Setting
TEST_F(SettingsMenuStateTest, TestGameSpeedSetting)
{
    // Enter the menu state to initialize everything
    settingsState->enter();

    // Save original settings
    int originalSpeed = settings->getGameSpeed();

    // First menu item should be Game Speed (already selected by default)
    // We'll modify it directly through the tempSettings
    auto& tempSettings = settingsState->getTempSettingsForTest();

    // Directly simulate what happens when user interacts with slider
    tempSettings.setGameSpeed(originalSpeed + 3);

    // Navigate to the Save button (5th item - index 5)
    for (int i = 0; i < 5; i++)
    {
        settingsState->processInput(Input::DOWN);
    }

    // Press select on the Save button
    settingsState->processInput(Input::SELECT);

    // Check that the original settings were updated
    EXPECT_EQ(settings->getGameSpeed(), originalSpeed + 3);
}

// Test Board Width Setting
TEST_F(SettingsMenuStateTest, TestBoardWidthSetting)
{
    // Enter the menu state to initialize everything
    settingsState->enter();

    // Save original settings
    int originalWidth = settings->getBoardWidth();

    // We'll modify it directly through the tempSettings
    auto& tempSettings = settingsState->getTempSettingsForTest();

    // Directly simulate what happens when user interacts with slider
    tempSettings.setBoardWidth(originalWidth + 5);

    // Navigate to the Save button (5th item - index 5)
    for (int i = 0; i < 5; i++)
    {
        settingsState->processInput(Input::DOWN);
    }

    // Press select on the Save button
    settingsState->processInput(Input::SELECT);

    // Check that the original settings were updated
    EXPECT_EQ(settings->getBoardWidth(), originalWidth + 5);
}

// Test Board Height Setting
TEST_F(SettingsMenuStateTest, TestBoardHeightSetting)
{
    // Enter the menu state to initialize everything
    settingsState->enter();

    // Save original settings
    int originalHeight = settings->getBoardHeight();

    // We'll modify it directly through the tempSettings
    auto& tempSettings = settingsState->getTempSettingsForTest();

    // Directly simulate what happens when user interacts with slider
    tempSettings.setBoardHeight(originalHeight + 4);

    // Navigate to the Save button (5th item - index 5)
    for (int i = 0; i < 5; i++)
    {
        settingsState->processInput(Input::DOWN);
    }

    // Press select on the Save button
    settingsState->processInput(Input::SELECT);

    // Check that the original settings were updated
    EXPECT_EQ(settings->getBoardHeight(), originalHeight + 4);
}

// Test Walls Toggle Setting
TEST_F(SettingsMenuStateTest, TestWallsToggleSetting)
{
    // Enter the menu state to initialize everything
    settingsState->enter();

    // Save original settings
    bool originalWallsEnabled = settings->isWallsEnabled();

    // Move to Walls Enabled (fourth item)
    for (int i = 0; i < 3; i++)
    {
        settingsState->processInput(Input::DOWN);
    }

    // Get temp settings to check the current state
    auto& tempSettings = settingsState->getTempSettingsForTest();

    // Toggle the walls setting
    settingsState->processInput(Input::SELECT);

    // Verify it toggled
    EXPECT_EQ(tempSettings.isWallsEnabled(), !originalWallsEnabled);

    // Toggle again to revert
    settingsState->processInput(Input::SELECT);

    // Verify it reverted
    EXPECT_EQ(tempSettings.isWallsEnabled(), originalWallsEnabled);

    // Toggle once more to change it
    settingsState->processInput(Input::SELECT);

    // Now save the settings
    for (int i = 0; i < 2; i++)
    {
        settingsState->processInput(Input::DOWN);
    }
    settingsState->processInput(Input::SELECT); // Save Settings

    // Check that the original settings were updated
    EXPECT_EQ(settings->isWallsEnabled(), !originalWallsEnabled);
}

// Test Sound Toggle Setting
TEST_F(SettingsMenuStateTest, TestSoundToggleSetting)
{
    // Enter the menu state to initialize everything
    settingsState->enter();

    // Save original settings
    bool originalSoundEnabled = settings->isSoundEnabled();

    // Move to Sound Enabled (fifth item)
    for (int i = 0; i < 4; i++)
    {
        settingsState->processInput(Input::DOWN);
    }

    // Get temp settings to check the current state
    auto& tempSettings = settingsState->getTempSettingsForTest();

    // Toggle the sound setting
    settingsState->processInput(Input::SELECT);

    // Verify it toggled
    EXPECT_EQ(tempSettings.isSoundEnabled(), !originalSoundEnabled);

    // Toggle again to revert
    settingsState->processInput(Input::SELECT);

    // Verify it reverted
    EXPECT_EQ(tempSettings.isSoundEnabled(), originalSoundEnabled);

    // Toggle once more to change it
    settingsState->processInput(Input::SELECT);

    // Now save the settings
    for (int i = 0; i < 1; i++)
    {
        settingsState->processInput(Input::DOWN);
    }
    settingsState->processInput(Input::SELECT); // Save Settings

    // Check that the original settings were updated
    EXPECT_EQ(settings->isSoundEnabled(), !originalSoundEnabled);
}

// Test settings adjustment with input keys
TEST_F(SettingsMenuStateTest, ComprehensiveSettingsAdjustment)
{
    // Initialize settings with known values
    settings->setGameSpeed(5);
    settings->setBoardWidth(20);
    settings->setBoardHeight(20);
    settings->setWallsEnabled(false);
    settings->setSoundEnabled(false);

    // Initialize state
    settingsState->enter();

    // Test Game Speed (first item)
    int originalSpeed = settings->getGameSpeed();

    // Increase speed twice
    settingsState->processInput(Input::RIGHT);
    settingsState->processInput(Input::RIGHT);

    // Go to next item
    settingsState->processInput(Input::DOWN);

    // Test Board Width
    int originalWidth = settings->getBoardWidth();

    // Increase width three times
    settingsState->processInput(Input::RIGHT);
    settingsState->processInput(Input::RIGHT);
    settingsState->processInput(Input::RIGHT);

    // Go to next item
    settingsState->processInput(Input::DOWN);

    // Test Board Height
    int originalHeight = settings->getBoardHeight();

    // Increase height twice
    settingsState->processInput(Input::RIGHT);
    settingsState->processInput(Input::RIGHT);

    // Go to next item (Walls)
    settingsState->processInput(Input::DOWN);

    // Toggle walls setting
    bool originalWallsEnabled = settings->isWallsEnabled();
    settingsState->processInput(Input::SELECT);

    // Go to next item (Sound)
    settingsState->processInput(Input::DOWN);

    // Toggle sound setting
    bool originalSoundEnabled = settings->isSoundEnabled();
    settingsState->processInput(Input::SELECT);

    // Go to Save item
    settingsState->processInput(Input::DOWN);

    // Execute Save
    settingsState->processInput(Input::SELECT);

    // Verify all settings were updated correctly
    EXPECT_EQ(originalSpeed + 2, settings->getGameSpeed());
    EXPECT_EQ(originalWidth + 3, settings->getBoardWidth());
    EXPECT_EQ(originalHeight + 2, settings->getBoardHeight());
    EXPECT_NE(originalWallsEnabled, settings->isWallsEnabled());
    EXPECT_NE(originalSoundEnabled, settings->isSoundEnabled());

    // Check we returned to main menu
    EXPECT_EQ(settingsState->getStatus(), GameState::Status::Finished);
}