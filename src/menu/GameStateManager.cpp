#include "menu/GameStateManager.h"

namespace GreedySnake
{

void GameStateManager::changeState(std::unique_ptr<GameState> newState)
{
    // Pop all states
    while (!stateStack.empty())
    {
        stateStack.top()->exit();
        stateStack.pop();
    }

    // Push and enter the new state
    if (newState)
    {
        newState->enter();
        stateStack.push(std::move(newState));
    }
}

void GameStateManager::pushState(std::unique_ptr<GameState> newState)
{
    // Enter the new state and push it onto the stack
    if (newState)
    {
        newState->enter();
        stateStack.push(std::move(newState));
    }
}

void GameStateManager::popState()
{
    // If there's a state on the stack, exit and pop it
    if (!stateStack.empty())
    {
        stateStack.top()->exit();
        stateStack.pop();
    }
}

bool GameStateManager::hasActiveState() const
{
    return !stateStack.empty();
}

void GameStateManager::processInput(Input input)
{
    if (!stateStack.empty())
    {
        stateStack.top()->processInput(input);
    }
}

void GameStateManager::update(float deltaTime)
{
    if (!stateStack.empty())
    {
        stateStack.top()->update(deltaTime);
    }
}

void GameStateManager::render(Renderer& renderer)
{
    if (!stateStack.empty())
    {
        stateStack.top()->render(renderer);
    }
}

} // namespace GreedySnake