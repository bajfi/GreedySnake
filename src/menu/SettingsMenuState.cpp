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
    // Copy settings to temp settings
    tempSettings = *settings;

    // Create menu items with current settings values
    menu.clearItems();

    // Game speed slider (1-10)
    auto speedItem = menu.addItem<SliderMenuItem>("Game Speed",
                                                  tempSettings.getGameSpeed(),
                                                  1,
                                                  10,
                                                  [this](int value) { onGameSpeedChange(value); });

    // Board width slider (10-50)
    menu.addItem<SliderMenuItem>("Board Width",
                                 tempSettings.getBoardWidth(),
                                 10,
                                 50,
                                 [this](int value) { onBoardWidthChange(value); });

    // Board height slider (10-30)
    menu.addItem<SliderMenuItem>("Board Height",
                                 tempSettings.getBoardHeight(),
                                 10,
                                 30,
                                 [this](int value) { onBoardHeightChange(value); });

    // Toggle borders
    menu.addItem<ToggleMenuItem>("Walls Enabled",
                                 tempSettings.hasBorders(),
                                 [this](bool enabled) { onToggleBorders(enabled); });

    // Toggle sound
    menu.addItem<ToggleMenuItem>("Sound Enabled",
                                 tempSettings.isSoundEnabled(),
                                 [this](bool enabled) { onToggleSound(enabled); });

    // Save settings
    menu.addItem<TextMenuItem>("Save Settings", [this]() { onSaveSettings(); });

    // Cancel
    menu.addItem<TextMenuItem>("Cancel", [this]() { onCancel(); });
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

    // Return to previous menu
    stateManager->popState();
}

void SettingsMenuState::onCancel()
{
    // Discard changes and return to previous menu
    stateManager->popState();
}

} // namespace GreedySnake