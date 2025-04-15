#ifndef GREEDYSNAKE_INPUT_H
#define GREEDYSNAKE_INPUT_H

namespace GreedySnake
{

/**
 * @brief Enum for input actions
 */
enum class Input
{
    NONE,   // No input
    UP,     // Move up
    DOWN,   // Move down
    LEFT,   // Move left
    RIGHT,  // Move right
    SELECT, // Select item
    BACK,   // Go back/cancel
    PAUSE,  // Pause/resume game
    QUIT    // Quit the game
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_INPUT_H