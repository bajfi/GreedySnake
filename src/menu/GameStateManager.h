#ifndef GREEDYSNAKE_GAMESTATEMANAGER_H
#define GREEDYSNAKE_GAMESTATEMANAGER_H

#include "menu/GameState.h"
#include "menu/Input.h"
#include <memory>
#include <stack>

namespace GreedySnake
{

// Forward declaration
class GameApp;

// The central controller for managing different game states
class GameStateManager
{
  public:
    GameStateManager() : owner(nullptr)
    {
    }
    explicit GameStateManager(GameApp* owner) : owner(owner)
    {
    }
    ~GameStateManager() = default;

    // Change to a new state, replacing the current one
    void changeState(std::unique_ptr<GameState> newState);

    // Add a new state on top of the current one
    void pushState(std::unique_ptr<GameState> newState);

    // Remove the current state and return to the previous one
    void popState();

    // Check if there's an active state
    [[nodiscard]] bool hasActiveState() const;

    // Forward input events to the current state
    void processInput(Input input);

    // Update logic for the current state
    void update(float deltaTime);

    // Render the current state
    void render(Renderer& renderer);

    // Get the owner application object
    [[nodiscard]] GameApp* getOwner() const
    {
        return owner;
    }

    // Set the owner application object
    void setOwner(GameApp* owner)
    {
        this->owner = owner;
    }

  private:
    std::stack<std::unique_ptr<GameState>> stateStack;
    GameApp* owner; // Pointer to the owning application
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_GAMESTATEMANAGER_H