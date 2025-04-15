#ifndef GREEDYSNAKE_MAINMENUSTATE_H
#define GREEDYSNAKE_MAINMENUSTATE_H

#include "menu/GameState.h"
#include "menu/GameStateManager.h"
#include "menu/Menu.h"
#include <memory>

namespace GreedySnake
{

/**
 * @brief Main menu state of the game
 *
 * This state displays the main menu with options like:
 * - Start Game
 * - Settings
 * - Exit
 */
class MainMenuState : public GameState
{
  public:
    /**
     * @brief Constructor
     * @param stateManager Pointer to the game state manager
     */
    explicit MainMenuState(GameStateManager* stateManager);

    /**
     * @brief Destructor
     */
    virtual ~MainMenuState() = default;

    // GameState interface implementation
    void enter() override;
    void exit() override;
    void processInput(Input input) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

    /**
     * @brief Get the number of menu items for testing
     * @return Number of menu items
     */
    size_t getMenuItemCount() const;

    /**
     * @brief Get the selected menu item index for testing
     * @return Selected menu item index
     */
    size_t getSelectedIndex() const;

  private:
    GameStateManager* stateManager;
    Menu menu;

    // Callback methods for menu items
    void onStartGame();
    void onSettings();
    void onExit();
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_MAINMENUSTATE_H