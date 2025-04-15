#ifndef GREEDYSNAKE_GAMEAPP_H
#define GREEDYSNAKE_GAMEAPP_H

#include "menu/GameStateManager.h"
#include "renderer/Renderer.h"
#include "settings/GameSettings.h"
#include <memory>
#include <string>

namespace GreedySnake
{

/**
 * @brief Main application class for the game
 *
 * This class serves as the primary entry point for the game application.
 * It manages the game state, settings, and coordinates the main game loop.
 */
class GameApp
{
  public:
    /**
     * @brief Constructor
     * @param windowWidth The width of the game window
     * @param windowHeight The height of the game window
     * @param windowTitle The title of the game window
     */
    GameApp(int windowWidth, int windowHeight, const std::string& windowTitle);

    /**
     * @brief Destructor
     */
    ~GameApp();

    /**
     * @brief Initialize the application
     * @return True if initialization was successful
     */
    bool initialize();

    /**
     * @brief Run the main game loop
     * @return Exit code (0 for normal exit)
     */
    int run();

    /**
     * @brief Get access to the game settings
     * @return Pointer to the game settings
     */
    GameSettings* getSettings();

    /**
     * @brief Get the game state manager
     * @return Pointer to the game state manager
     */
    GameStateManager* getStateManager();

  private:
    // Game window configuration
    int windowWidth;
    int windowHeight;
    std::string windowTitle;

    // Core components
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<GameSettings> settings;
    std::unique_ptr<GameStateManager> stateManager;

    // Process input events
    void processInput();

    // Update game state
    void update(float deltaTime);

    // Render the current frame
    void render();
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_GAMEAPP_H