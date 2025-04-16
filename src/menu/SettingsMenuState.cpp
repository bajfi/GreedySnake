#include "menu/SettingsMenuState.h"
#include "menu/SliderMenuItem.h"
#include "menu/TextMenuItem.h"
#include "menu/ToggleMenuItem.h"

namespace GreedySnake
{

SettingsMenuState::SettingsMenuState(GameStateManager* stateManager, GameSettings* settings)
    : stateManager(stateManager), settings(settings), tempSettings(*settings)
{
}

void SettingsMenuState::enter()
{
    // Reset status
    currentStatus = Status::Running;

    // Copy settings to temp settings
    tempSettings = *settings;

    // Create menu items with current settings values
    menu.clearItems();

    // 1. Game speed slider (1-10)
    menu.addItem<SliderMenuItem>("Game Speed",
                                 1,
                                 10,
                                 tempSettings.getGameSpeed(),
                                 [this](int value) { onGameSpeedChange(value); });

    // 2. Board width slider (10-50)
    menu.addItem<SliderMenuItem>("Board Width",
                                 10,
                                 50,
                                 tempSettings.getBoardWidth(),
                                 [this](int value) { onBoardWidthChange(value); });

    // 3. Board height slider (10-30)
    menu.addItem<SliderMenuItem>("Board Height",
                                 10,
                                 30,
                                 tempSettings.getBoardHeight(),
                                 [this](int value) { onBoardHeightChange(value); });

    // 4. Toggle walls
    menu.addItem<ToggleMenuItem>("Walls Enabled",
                                 tempSettings.isWallsEnabled(),
                                 [this](bool enabled) { onToggleWalls(enabled); });

    // 5. Toggle sound
    menu.addItem<ToggleMenuItem>("Sound Enabled",
                                 tempSettings.isSoundEnabled(),
                                 [this](bool enabled) { onToggleSound(enabled); });

    // 6. Save settings
    menu.addItem<TextMenuItem>("Save Settings", [this]() { onSaveSettings(); });

    // 7. Cancel
    menu.addItem<TextMenuItem>("Cancel", [this]() { onCancel(); });

    // Set instructions for the settings menu
    menu.setInstructions("Use ↑/↓ to select options, ←/→ to adjust values, ↵ to toggle/confirm");
}

void SettingsMenuState::exit()
{
    // Cleanup if needed
}

void SettingsMenuState::processInput(Input input)
{
    menu.handleInput(input);
}

void SettingsMenuState::update(float deltaTime)
{
    // No continuous updates needed for settings menu
}

void SettingsMenuState::render(Renderer& renderer)
{
    menu.render(renderer, "Settings");
}

GameState::Status SettingsMenuState::getStatus() const
{
    return currentStatus;
}

size_t SettingsMenuState::getMenuItemCount() const
{
    return menu.getItemCount();
}

void SettingsMenuState::onGameSpeedChange(int value)
{
    tempSettings.setGameSpeed(value);
}

void SettingsMenuState::onBoardWidthChange(int value)
{
    tempSettings.setBoardWidth(value);
}

void SettingsMenuState::onBoardHeightChange(int value)
{
    tempSettings.setBoardHeight(value);
}

void SettingsMenuState::onToggleWalls(bool enabled)
{
    tempSettings.setWallsEnabled(enabled);
}

void SettingsMenuState::onToggleBorders(bool enabled)
{
    tempSettings.setBorders(enabled);
}

void SettingsMenuState::onToggleSound(bool enabled)
{
    tempSettings.setSoundEnabled(enabled);
}

void SettingsMenuState::onSaveSettings()
{
    // Copy temp settings to actual settings
    *settings = tempSettings;

    // Set the status to finished
    currentStatus = Status::Finished;

    // Return to previous menu
    stateManager->popState();
}

void SettingsMenuState::onCancel()
{
    // Set the status to finished
    currentStatus = Status::Finished;

    // Discard changes and return to previous menu
    stateManager->popState();
}

} // namespace GreedySnake