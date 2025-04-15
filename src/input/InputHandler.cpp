#include "input/InputHandler.h"

namespace GreedySnake
{

InputHandler::InputHandler() : currentDirection(Direction::RIGHT), quitRequested(false)
{
}

Direction InputHandler::getInput()
{
    return currentDirection;
}

bool InputHandler::isQuitRequested() const
{
    return quitRequested;
}

void InputHandler::processKeyPress(int keyCode)
{
    switch (keyCode)
    {
    case SNAKE_KEY_UP:
        currentDirection = Direction::UP;
        break;
    case SNAKE_KEY_DOWN:
        currentDirection = Direction::DOWN;
        break;
    case SNAKE_KEY_LEFT:
        currentDirection = Direction::LEFT;
        break;
    case SNAKE_KEY_RIGHT:
        currentDirection = Direction::RIGHT;
        break;
    case SNAKE_KEY_QUIT:
        quitRequested = true;
        break;
    default:
        // Ignore unrecognized key presses
        break;
    }
}

void InputHandler::reset()
{
    currentDirection = Direction::RIGHT;
    quitRequested = false;
}

} // namespace GreedySnake