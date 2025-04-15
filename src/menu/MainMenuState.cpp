#include "menu/MainMenuState.h"
#include "game/GameApp.h"
#include "menu/GamePlayState.h"
#include "menu/SettingsMenuState.h"
#include "menu/TextMenuItem.h"

namespace GreedySnake
{

MainMenuState::MainMenuState(GameStateManager* stateManager) : stateManager(stateManager)
{
}

void MainMenuState::enter()
{
    // Create menu items
    menu.clearItems();

    // Start Game
    menu.addItem<TextMenuItem>("Start Game", [this]() { onStartGame(); });

    // Settings
    menu.addItem<TextMenuItem>("Settings", [this]() { onSettings(); });

    // Exit
    menu.addItem<TextMenuItem>("Exit", [this]() { onExit(); });
}

void MainMenuState::exit()
{
    // Cleanup if needed
}

void MainMenuState::processInput(Input input)
{
    menu.handleInput(input);
}

void MainMenuState::update(float deltaTime)
{
    // No continuous updates needed for main menu
}

void MainMenuState::render(Renderer& renderer)
{
    menu.render(renderer, "Greedy Snake");
}

size_t MainMenuState::getMenuItemCount() const
{
    return menu.getItemCount();
}

size_t MainMenuState::getSelectedIndex() const
{
    return menu.getSelectedIndex();
}

void MainMenuState::onStartGame()
{
    // Look up game settings from the application context
    // For now, we access it from GameApp
    GameApp* app = dynamic_cast<GameApp*>(stateManager->getOwner());
    if (app == nullptr)
    {
        // Fallback if we can't get the app context
        GameSettings* settings = new GameSettings();
        stateManager->pushState(std::make_unique<GamePlayState>(stateManager, settings));
    }
    else
    {
        // Use app's settings
        stateManager->pushState(std::make_unique<GamePlayState>(stateManager, app->getSettings()));
    }
}

void MainMenuState::onSettings()
{
    // Look up game settings from the application context
    GameApp* app = dynamic_cast<GameApp*>(stateManager->getOwner());
    if (app == nullptr)
    {
        // Fallback if we can't get the app context
        GameSettings* settings = new GameSettings();
        stateManager->pushState(std::make_unique<SettingsMenuState>(stateManager, settings));
    }
    else
    {
        // Use app's settings
        stateManager->pushState(
            std::make_unique<SettingsMenuState>(stateManager, app->getSettings()));
    }
}

void MainMenuState::onExit()
{
    // Exit the application by popping the main menu state
    stateManager->popState();
}

} // namespace GreedySnake
