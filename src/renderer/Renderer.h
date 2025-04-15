#pragma once

#include "game/Game.h"

namespace GreedySnake
{

/**
 * @brief Abstract interface for game renderers
 *
 * This class defines the interface that all renderers must implement
 * to draw the game on screen, whether it's console-based or graphical.
 */
class Renderer
{
  public:
    /**
     * @brief Virtual destructor for proper cleanup
     */
    virtual ~Renderer() = default;

    /**
     * @brief Initialize the renderer
     * @return True if initialization was successful
     */
    virtual bool initialize() = 0;

    /**
     * @brief Clean up resources used by the renderer
     */
    virtual void shutdown() = 0;

    /**
     * @brief Render a frame of the game
     * @param game Reference to the game state to render
     */
    virtual void render(const Game& game) = 0;

    /**
     * @brief Check if the render window is still open
     * @return True if the window is open
     */
    virtual bool isWindowOpen() const = 0;

    /**
     * @brief Handle input events from the window system
     * @param game Reference to the game for processing input
     * @return True if the game should continue running
     */
    virtual bool handleEvents(Game& game) = 0;
};

} // namespace GreedySnake