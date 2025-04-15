#ifndef GREEDYSNAKE_GAMEPLAYSTATE_H
#define GREEDYSNAKE_GAMEPLAYSTATE_H

#include "game/Game.h"
#include "menu/GameState.h"
#include "menu/GameStateManager.h"
#include "settings/GameSettings.h"
#include <chrono>
#include <memory>

namespace GreedySnake
{

/**
 * @brief Gameplay state of the game
 *
 * This state handles the actual snake game, processing input,
 * updating game logic, and rendering the game board.
 */
class GamePlayState : public GameState
{
  public:
    /**
     * @brief Constructor
     * @param stateManager Pointer to the game state manager
     * @param settings Pointer to the game settings
     */
    GamePlayState(GameStateManager* stateManager, const GameSettings* settings);

    /**
     * @brief Destructor
     */
    virtual ~GamePlayState() = default;

    // GameState interface implementation
    void enter() override;
    void exit() override;
    void processInput(Input input) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

    /**
     * @brief Check if the game is paused
     * @return True if paused, false otherwise
     */
    bool isPaused() const;

    /**
     * @brief Check if the game is over
     * @return True if game is over, false otherwise
     */
    bool isGameOver() const;

    /**
     * @brief Get the current score
     * @return Current score
     */
    int getScore() const;

  private:
    GameStateManager* stateManager;
    const GameSettings* settings;

    Game game;
    bool paused;

    // Time tracking for game updates
    std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime;
    float updateInterval; // in seconds

    // Handle the game over condition
    void handleGameOver();

    // Pause or resume the game
    void togglePause();
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_GAMEPLAYSTATE_H