#pragma once

#include "utils/Direction.h"

namespace GreedySnake
{

/**
 * @brief Handles player input for controlling the game
 */
class InputHandler
{
  public:
    /**
     * @brief Constructor
     */
    InputHandler();

    /**
     * @brief Gets the current input direction from player
     * @return Direction to move the snake
     */
    Direction getInput();

    /**
     * @brief Check if the user has requested to quit game
     * @return True if quit requested
     */
    [[nodiscard]] bool isQuitRequested() const;

    /**
     * @brief Process a key press
     * @param keyCode The key code of the pressed key
     */
    void processKeyPress(int keyCode);

    /**
     * @brief Reset the input state
     */
    void reset();

  private:
    Direction currentDirection;
    bool quitRequested;

    // Key codes (can be platform-specific)
    static const int SNAKE_KEY_UP = 119;    // W
    static const int SNAKE_KEY_DOWN = 115;  // S
    static const int SNAKE_KEY_LEFT = 97;   // A
    static const int SNAKE_KEY_RIGHT = 100; // D
    static const int SNAKE_KEY_QUIT = 113;  // Q
};

} // namespace GreedySnake