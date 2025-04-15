#include "menu/GamePlayState.h"
#include "menu/GameOverState.h"

namespace GreedySnake
{

GamePlayState::GamePlayState(GameStateManager* stateManager, const GameSettings* settings)
    : stateManager(stateManager),
      settings(settings),
      game(settings->getBoardWidth(), settings->getBoardHeight(), 3), // Initial snake length = 3
      paused(false),
      lastUpdateTime(std::chrono::steady_clock::now()),
      updateInterval(1.0f / static_cast<float>(settings->getGameSpeed()))
{
}

void GamePlayState::enter()
{
    // Initialize game board and entities
    game.initialize();

    // Update game speed from settings
    updateInterval = 1.0f / static_cast<float>(settings->getGameSpeed());

    // Reset the timer
    lastUpdateTime = std::chrono::steady_clock::now();

    // Start in non-paused state
    paused = false;
}

void GamePlayState::exit()
{
    // Cleanup if needed
}

void GamePlayState::processInput(Input input)
{
    switch (input)
    {
    case Input::UP:
        game.processKeyPress(119); // 'w'
        break;
    case Input::DOWN:
        game.processKeyPress(115); // 's'
        break;
    case Input::LEFT:
        game.processKeyPress(97); // 'a'
        break;
    case Input::RIGHT:
        game.processKeyPress(100); // 'd'
        break;
    case Input::PAUSE:
        togglePause();
        break;
    case Input::BACK:
        // If paused, return to main menu; otherwise pause first
        if (paused)
        {
            stateManager->popState();
        }
        else
        {
            togglePause();
        }
        break;
    case Input::QUIT:
        stateManager->popState(); // Exit game
        break;
    default:
        break;
    }
}

void GamePlayState::update(float deltaTime)
{
    // Skip updates if paused or game over
    if (paused || game.isGameOver())
    {
        return;
    }

    // Accumulate time and update game when interval is reached
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration<float>(currentTime - lastUpdateTime).count();

    if (elapsed >= updateInterval)
    {
        game.update();
        lastUpdateTime = currentTime;
    }

    // Check for game over condition
    if (game.isGameOver())
    {
        handleGameOver();
    }
}

void GamePlayState::render(Renderer& renderer)
{
    // Render game board and entities
    renderer.render(game);
}

bool GamePlayState::isPaused() const
{
    return paused;
}

bool GamePlayState::isGameOver() const
{
    return game.isGameOver();
}

int GamePlayState::getScore() const
{
    return game.getScore();
}

void GamePlayState::handleGameOver()
{
    // Create and transition to the game over state with the final score
    stateManager->pushState(std::make_unique<GameOverState>(stateManager, game.getScore()));
}

void GamePlayState::togglePause()
{
    paused = !paused;

    if (paused)
    {
        game.pause();
    }
    else
    {
        game.resume();
    }
}

} // namespace GreedySnake