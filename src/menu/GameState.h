#ifndef GREEDYSNAKE_GAMESTATE_H
#define GREEDYSNAKE_GAMESTATE_H

#include "menu/Input.h"
#include "renderer/Renderer.h"

namespace GreedySnake
{

// Base interface for all game states
class GameState
{
  public:
    // Status enum to track state's completion status
    enum class Status
    {
        Running,  // State is still active
        Finished, // State is finished, should be popped
        Replaced  // State is replaced, should be replaced with another
    };

    virtual ~GameState() = default;

    // Called when entering the state
    virtual void enter() = 0;

    // Called when exiting the state
    virtual void exit() = 0;

    // Process input specific to this state
    virtual void processInput(Input input) = 0;

    // Update logic specific to this state
    virtual void update(float deltaTime) = 0;

    // Render this state
    virtual void render(Renderer& renderer) = 0;

    // Get the current status of the state
    virtual Status getStatus() const
    {
        return Status::Running; // Default implementation
    }
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_GAMESTATE_H