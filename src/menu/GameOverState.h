#ifndef GREEDYSNAKE_GAMEOVERSTATE_H
#define GREEDYSNAKE_GAMEOVERSTATE_H

#include "menu/GameState.h"
#include "menu/GameStateManager.h"
#include "menu/Menu.h"
#include <memory>

namespace GreedySnake
{

/**
 * @brief Game over state of the game
 *
 * This state displays the game over screen with the final score
 * and options to restart or return to the main menu.
 */
class GameOverState : public GameState
{
  public:
    /**
     * @brief Constructor
     * @param stateManager Pointer to the game state manager
     * @param finalScore The final score to display
     */
    GameOverState(GameStateManager* stateManager, int finalScore);

    /**
     * @brief Destructor
     */
    virtual ~GameOverState() = default;

    // GameState interface implementation
    void enter() override;
    void exit() override;
    void processInput(Input input) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

    /**
     * @brief Get the final score for testing
     * @return Final score
     */
    int getFinalScore() const;

  private:
    GameStateManager* stateManager;
    int finalScore;
    Menu menu;

    // Callback methods for menu items
    void onPlayAgain();
    void onMainMenu();
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_GAMEOVERSTATE_H