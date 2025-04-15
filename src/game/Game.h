#pragma once

#include "game/Board.h"
#include "game/Food.h"
#include "game/Snake.h"
#include "input/InputHandler.h"

namespace GreedySnake
{

/**
 * @brief Main game controller class that coordinates all game elements
 */
class Game
{
  public:
    /**
     * @brief Constructor initializes game components
     * @param boardWidth Width of the game board
     * @param boardHeight Height of the game board
     * @param initialSnakeLength Initial length of the snake
     */
    Game(int boardWidth = 20, int boardHeight = 20, int initialSnakeLength = 3);

    /**
     * @brief Initialize game state and components
     */
    void initialize();

    /**
     * @brief Main game loop
     */
    void run();

    /**
     * @brief Process a single frame update
     * @return True if the game is still running, false if game over
     */
    bool update();

    /**
     * @brief Process player input
     */
    void handleInput();

    /**
     * @brief Check for collisions between snake, food, and walls
     */
    void checkCollisions();

    /**
     * @brief Generate new food at random position
     * @return True if food was successfully generated
     */
    bool generateFood();

    /**
     * @brief Check if game is over
     * @return True if game is over
     */
    [[nodiscard]] bool isGameOver() const;

    /**
     * @brief Get current score
     * @return Current score
     */
    [[nodiscard]] int getScore() const;

    /**
     * @brief Get the game board
     * @return Reference to the game board
     */
    [[nodiscard]] const Board& getBoard() const;

    /**
     * @brief Get the snake
     * @return Reference to the snake
     */
    [[nodiscard]] const Snake& getSnake() const;

    /**
     * @brief Get the food
     * @return Reference to the food
     */
    [[nodiscard]] const Food& getFood() const;

    /**
     * @brief Pause the game
     */
    void pause();

    /**
     * @brief Resume the game
     */
    void resume();

    /**
     * @brief Check if the game is paused
     * @return True if game is paused
     */
    [[nodiscard]] bool isPaused() const;

    /**
     * @brief Process a key press
     * @param keyCode The key code of the pressed key
     */
    void processKeyPress(int keyCode);

    /**
     * @brief Reset game to initial state
     */
    void reset();

  private:
    Board board;
    Snake snake;
    Food food;
    InputHandler inputHandler;
    bool isRunning;
    bool gameOver;
    bool paused;
    int score;
    int gameSpeed;

    /**
     * @brief Initialize the snake position
     */
    void initializeSnake();
};

} // namespace GreedySnake