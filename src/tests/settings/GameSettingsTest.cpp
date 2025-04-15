#include "settings/GameSettings.h"
#include <cstdio> // For std::remove
#include <fstream>
#include <gtest/gtest.h>

using namespace GreedySnake;

class GameSettingsTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        // Set up any test-specific data
    }

    void TearDown() override
    {
        // Clean up any test-specific data
        // Remove any test settings file if it exists
        std::remove("test_settings.ini");
    }
};

TEST_F(GameSettingsTest, DefaultSettings)
{
    GameSettings settings;

    // Check default values
    EXPECT_EQ(5, settings.getGameSpeed());
    EXPECT_EQ(20, settings.getBoardWidth());
    EXPECT_EQ(20, settings.getBoardHeight());
    EXPECT_TRUE(settings.hasBorders());
    EXPECT_TRUE(settings.isSoundEnabled());
}

TEST_F(GameSettingsTest, ModifySettings)
{
    GameSettings settings;

    // Modify settings
    settings.setGameSpeed(8);
    settings.setBoardWidth(30);
    settings.setBoardHeight(25);
    settings.setBorders(false);
    settings.setSoundEnabled(false);

    // Check modified values
    EXPECT_EQ(8, settings.getGameSpeed());
    EXPECT_EQ(30, settings.getBoardWidth());
    EXPECT_EQ(25, settings.getBoardHeight());
    EXPECT_FALSE(settings.hasBorders());
    EXPECT_FALSE(settings.isSoundEnabled());
}

TEST_F(GameSettingsTest, BoundaryValues)
{
    GameSettings settings;

    // Test minimum values
    settings.setGameSpeed(1);
    EXPECT_EQ(1, settings.getGameSpeed());

    // Test maximum values
    settings.setGameSpeed(10);
    EXPECT_EQ(10, settings.getGameSpeed());

    // Test out-of-range values (should be clamped or rejected)
    settings.setGameSpeed(0);
    EXPECT_EQ(1, settings.getGameSpeed()); // Should be clamped to min value

    settings.setGameSpeed(15);
    EXPECT_EQ(10, settings.getGameSpeed()); // Should be clamped to max value

    // Test boundary values for board dimensions
    settings.setBoardWidth(10); // Minimum acceptable width
    EXPECT_EQ(10, settings.getBoardWidth());

    settings.setBoardHeight(10); // Minimum acceptable height
    EXPECT_EQ(10, settings.getBoardHeight());

    // Test invalid values for board dimensions
    settings.setBoardWidth(5);               // Too small
    EXPECT_EQ(10, settings.getBoardWidth()); // Should be clamped to min

    settings.setBoardHeight(5);               // Too small
    EXPECT_EQ(10, settings.getBoardHeight()); // Should be clamped to min
}

TEST_F(GameSettingsTest, SaveAndLoadSettings)
{
    GameSettings settings;

    // Modify settings
    settings.setGameSpeed(7);
    settings.setBoardWidth(25);
    settings.setBoardHeight(30);
    settings.setBorders(false);
    settings.setSoundEnabled(false);

    // Save settings to file
    EXPECT_TRUE(settings.saveToFile("test_settings.ini"));

    // Create new settings object with default values
    GameSettings loadedSettings;

    // Load settings from file
    EXPECT_TRUE(loadedSettings.loadFromFile("test_settings.ini"));

    // Check if loaded settings match the saved ones
    EXPECT_EQ(settings.getGameSpeed(), loadedSettings.getGameSpeed());
    EXPECT_EQ(settings.getBoardWidth(), loadedSettings.getBoardWidth());
    EXPECT_EQ(settings.getBoardHeight(), loadedSettings.getBoardHeight());
    EXPECT_EQ(settings.hasBorders(), loadedSettings.hasBorders());
    EXPECT_EQ(settings.isSoundEnabled(), loadedSettings.isSoundEnabled());
}

TEST_F(GameSettingsTest, LoadNonexistentFile)
{
    GameSettings settings;

    // Try to load settings from a nonexistent file
    EXPECT_FALSE(settings.loadFromFile("nonexistent_file.ini"));

    // Settings should remain at default values
    EXPECT_EQ(5, settings.getGameSpeed());
    EXPECT_EQ(20, settings.getBoardWidth());
    EXPECT_EQ(20, settings.getBoardHeight());
    EXPECT_TRUE(settings.hasBorders());
    EXPECT_TRUE(settings.isSoundEnabled());
}