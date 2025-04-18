#include "menu/GameOverState.h"
#include "game/GameApp.h"
#include "menu/GamePlayState.h"
#include "menu/MainMenuState.h"
#include "menu/TextMenuItem.h"
#include "settings/GameSettings.h"
#include <sstream>

namespace GreedySnake
{

GameOverState::GameOverState(GameStateManager* stateManager, int finalScore)
    : stateManager(stateManager), finalScore(finalScore)
{
}

void GameOverState::enter()
{
    // Create menu items
    menu.clearItems();

    // Play again option
    menu.addItem<TextMenuItem>("Play Again", [this]() { onPlayAgain(); });

    // Main menu option
    menu.addItem<TextMenuItem>("Main Menu", [this]() { onMainMenu(); });

    // Set instructions for the game over menu
    menu.setInstructions("Use ↑/↓ to select options, ↵ to confirm, Esc to return to main menu");
}

void GameOverState::exit()
{
    // Cleanup if needed
}

void GameOverState::processInput(Input input)
{
    menu.handleInput(input);

    if (input == Input::BACK)
    {
        // Return to main menu on back button
        onMainMenu();
    }
}

void GameOverState::update(float deltaTime)
{
    // No continuous updates needed for game over screen
}

void GameOverState::render(Renderer& renderer)
{
    // Create title with score
    std::stringstream title;
    title << "Game Over! Score: " << finalScore;

    menu.render(renderer, title.str());
}

int GameOverState::getFinalScore() const
{
    return finalScore;
}

void GameOverState::onPlayAgain()
{
    // Get the game settings from the GameApp
    GameApp* app = dynamic_cast<GameApp*>(stateManager->getOwner());
    if (app == nullptr)
    {
        // Fallback if we can't get the app context
        GameSettings* settings = new GameSettings();
        stateManager->changeState(std::make_unique<GamePlayState>(stateManager, settings));
    }
    else
    {
        // Use app's settings and create a new game play state
        stateManager->changeState(
            std::make_unique<GamePlayState>(stateManager, app->getSettings()));
    }
}

void GameOverState::onMainMenu()
{
    // Pop all states and return to main menu
    stateManager->changeState(std::make_unique<MainMenuState>(stateManager));
}

} // namespace GreedySnake