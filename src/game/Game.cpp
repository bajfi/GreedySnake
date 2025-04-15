#include "game/Game.h"
#include <chrono>
#include <thread>

namespace GreedySnake
{

Game::Game(int boardWidth, int boardHeight, int initialSnakeLength)
    : board(boardWidth, boardHeight),
      snake(Position(boardWidth / 2, boardHeight / 2), initialSnakeLength, Direction::RIGHT),
      food(1),
      isRunning(false),
      gameOver(false),
      paused(false),
      score(0),
      gameSpeed(5)
{
}

void Game::initialize()
{
    // Initialize the game components
    board.reset();
    snake.reset();
    inputHandler.reset();

    // Initialize snake on the board
    initializeSnake();

    // Generate initial food
    generateFood();

    // Reset game state
    isRunning = true;
    gameOver = false;
    paused = false;
    score = 0;
}

void Game::run()
{
    // Main game loop
    isRunning = true;

    while (isRunning && !gameOver)
    {
        // Handle input
        handleInput();

        // Check if user requested to quit
        if (inputHandler.isQuitRequested())
        {
            isRunning = false;
            continue;
        }

        // Skip update if game is paused
        if (paused)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        // Update game state
        if (!update())
        {
            gameOver = true;
        }

        // Control game speed
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / gameSpeed));
    }
}

bool Game::update()
{
    if (gameOver)
    {
        return false;
    }

    // Move snake
    Position newHead = snake.move();

    // Check for collisions
    checkCollisions();

    // Update board with new snake position
    for (const auto& pos : snake.getBody())
    {
        board.setCellType(pos, CellType::SNAKE);
    }

    return !gameOver;
}

void Game::handleInput()
{
    Direction dir = inputHandler.getInput();
    snake.changeDirection(dir);
}

void Game::checkCollisions()
{
    Position head = snake.getHead();

    // Check for wall collision
    if (board.getCellType(head) == CellType::WALL)
    {
        gameOver = true;
        return;
    }

    // Check for self collision
    if (snake.checkSelfCollision())
    {
        gameOver = true;
        return;
    }

    // Check for food collision
    if (head == food.getPosition())
    {
        // Eat food
        snake.grow();
        score += food.getValue();

        // Generate new food
        if (!generateFood())
        {
            // No more space for food, game won!
            gameOver = true;
        }
    }
}

bool Game::generateFood()
{
    return food.generatePosition(board, snake);
}

bool Game::isGameOver() const
{
    return gameOver;
}

int Game::getScore() const
{
    return score;
}

const Board& Game::getBoard() const
{
    return board;
}

const Snake& Game::getSnake() const
{
    return snake;
}

const Food& Game::getFood() const
{
    return food;
}

void Game::pause()
{
    paused = true;
}

void Game::resume()
{
    paused = false;
}

bool Game::isPaused() const
{
    return paused;
}

void Game::processKeyPress(int keyCode)
{
    // Forward the key press to our input handler
    inputHandler.processKeyPress(keyCode);

    // Apply the new direction to the snake immediately
    snake.changeDirection(inputHandler.getInput());

    // Process special key presses for game control (like pause)
    if (keyCode == 'p')
    {
        if (paused)
        {
            resume();
        }
        else
        {
            pause();
        }
    }
    else if (keyCode == 'r' && gameOver)
    {
        reset();
    }
}

void Game::reset()
{
    initialize();
}

void Game::initializeSnake()
{
    // Place snake on board
    for (const auto& pos : snake.getBody())
    {
        board.setCellType(pos, CellType::SNAKE);
    }
}

} // namespace GreedySnake