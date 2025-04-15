#ifndef GREEDYSNAKE_SETTINGSMENUSTATE_H
#define GREEDYSNAKE_SETTINGSMENUSTATE_H

#include "menu/GameState.h"
#include "menu/GameStateManager.h"
#include "menu/Menu.h"
#include "settings/GameSettings.h"
#include <memory>

namespace GreedySnake
{

/**
 * @brief Settings menu state of the game
 *
 * This state displays the settings menu with options like:
 * - Game Speed
 * - Board Size
 * - Toggle Borders
 * - Toggle Sound
 * - Save/Cancel
 */
class SettingsMenuState : public GameState
{
  public:
    /**
     * @brief Constructor
     * @param stateManager Pointer to the game state manager
     * @param settings Pointer to the global game settings
     */
    SettingsMenuState(GameStateManager* stateManager, GameSettings* settings);

    /**
     * @brief Destructor
     */
    virtual ~SettingsMenuState() = default;

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
     * @brief Get the temporary settings object for testing purposes
     * This method should only be used in test code.
     * @return Reference to the temporary settings object
     */
    GameSettings& getTempSettingsForTest()
    {
        return tempSettings;
    }

  private:
    GameStateManager* stateManager;
    GameSettings* settings;
    GameSettings tempSettings; // For storing changes before committing
    Menu menu;

    // Callback methods for menu items
    void onGameSpeedChange(int value);
    void onBoardWidthChange(int value);
    void onBoardHeightChange(int value);
    void onToggleBorders(bool enabled);
    void onToggleSound(bool enabled);
    void onSaveSettings();
    void onCancel();
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_SETTINGSMENUSTATE_H