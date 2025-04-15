#include "game/Snake.h"
#include <algorithm>

namespace GreedySnake
{

Snake::Snake(const Position& initialPosition, int initialLength, Direction initialDirection)
    : currentDirection(initialDirection),
      hasGrown(false),
      initialPosition(initialPosition),
      initialLength(initialLength),
      initialDirection(initialDirection)
{
    reset();
}

Position Snake::move()
{
    // Determine the new head position based on current direction
    Position newHead = getHead();

    switch (currentDirection)
    {
    case Direction::UP:
        newHead.y--;
        break;
    case Direction::DOWN:
        newHead.y++;
        break;
    case Direction::LEFT:
        newHead.x--;
        break;
    case Direction::RIGHT:
        newHead.x++;
        break;
    }

    // Add the new head to the front of the body
    body.insert(body.begin(), newHead);

    // Remove the tail segment if the snake hasn't grown
    if (!hasGrown && body.size() > 1)
    {
        body.pop_back();
    }

    // Reset the growth flag
    hasGrown = false;

    return newHead;
}

void Snake::grow()
{
    hasGrown = true;
}

bool Snake::changeDirection(Direction direction)
{
    // Cannot change to opposite direction
    if (direction == getOppositeDirection(currentDirection))
    {
        return false;
    }

    currentDirection = direction;
    return true;
}

Position Snake::getHead() const
{
    if (body.empty())
    {
        return Position();
    }
    return body.front();
}

const std::vector<Position>& Snake::getBody() const
{
    return body;
}

bool Snake::checkSelfCollision() const
{
    if (body.size() <= 1)
    {
        return false;
    }

    // Get the head position
    Position head = getHead();

    // Check if the head collides with any other body segment
    for (size_t i = 1; i < body.size(); ++i)
    {
        if (head == body[i])
        {
            return true;
        }
    }

    return false;
}

bool Snake::containsPosition(const Position& position) const
{
    return std::find(body.begin(), body.end(), position) != body.end();
}

void Snake::reset()
{
    // Clear the body
    body.clear();

    // Initialize with the head at initialPosition
    body.push_back(initialPosition);

    // Add body segments in the opposite direction of initialDirection
    Position offset;
    switch (initialDirection)
    {
    case Direction::UP:
        offset = Position(0, 1);
        break;
    case Direction::DOWN:
        offset = Position(0, -1);
        break;
    case Direction::LEFT:
        offset = Position(1, 0);
        break;
    case Direction::RIGHT:
        offset = Position(-1, 0);
        break;
    }

    // Add the remaining segments
    for (int i = 1; i < initialLength; ++i)
    {
        Position pos = initialPosition;
        pos.x += offset.x * i;
        pos.y += offset.y * i;
        body.push_back(pos);
    }

    // Reset direction and growth flag
    currentDirection = initialDirection;
    hasGrown = false;
}

Direction Snake::getCurrentDirection() const
{
    return currentDirection;
}

} // namespace GreedySnake