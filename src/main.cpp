#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <thread>

#include "game/Game.h"

using namespace GreedySnake;

// Simple console renderer for the game
class ConsoleRenderer
{
  public:
    ConsoleRenderer()
    {
        // Initialize ncurses
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);  // Hide cursor
        timeout(100); // Non-blocking input with 100ms timeout

        // Initialize colors if supported
        if (has_colors())
        {
            start_color();
            init_pair(1, COLOR_GREEN, COLOR_BLACK); // Snake
            init_pair(2, COLOR_RED, COLOR_BLACK);   // Food
            init_pair(3, COLOR_BLUE, COLOR_BLACK);  // Wall
            init_pair(4, COLOR_WHITE, COLOR_BLACK); // Text
        }
    }

    ~ConsoleRenderer()
    {
        endwin();
    }

    void render(const Game& game)
    {
        clear();

        // Render board and entities
        const Board& board = game.getBoard();
        const Snake& snake = game.getSnake();
        const Food& food = game.getFood();

        // Draw border
        for (int y = 0; y < board.getHeight(); ++y)
        {
            mvaddch(y, 0, '#');
            mvaddch(y, board.getWidth() - 1, '#');
        }
        for (int x = 0; x < board.getWidth(); ++x)
        {
            mvaddch(0, x, '#');
            mvaddch(board.getHeight() - 1, x, '#');
        }

        // Draw snake
        attron(COLOR_PAIR(1));
        for (const auto& pos : snake.getBody())
        {
            if (pos == snake.getHead())
            {
                mvaddch(pos.y, pos.x, '@'); // Head
            }
            else
            {
                mvaddch(pos.y, pos.x, 'o'); // Body
            }
        }
        attroff(COLOR_PAIR(1));

        // Draw food
        attron(COLOR_PAIR(2));
        Position foodPos = food.getPosition();
        mvaddch(foodPos.y, foodPos.x, '*');
        attroff(COLOR_PAIR(2));

        // Draw score
        attron(COLOR_PAIR(4));
        mvprintw(board.getHeight(), 0, "Score: %d", game.getScore());

        // Draw game state
        if (game.isGameOver())
        {
            mvprintw(board.getHeight() + 1, 0, "Game Over! Press 'r' to restart or 'q' to quit");
        }
        else if (game.isPaused())
        {
            mvprintw(board.getHeight() + 1, 0, "Paused. Press 'p' to resume");
        }
        attroff(COLOR_PAIR(4));

        refresh();
    }

    int getInput()
    {
        return getch();
    }
};

int main()
{
    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    try
    {
        // Create game with 20x20 board
        Game game(20, 20, 3);

        // Create console renderer
        ConsoleRenderer renderer;

        // Initialize the game
        game.initialize();

        bool running = true;

        // Main game loop
        while (running)
        {
            // Render the game
            renderer.render(game);

            // Get input
            int key = renderer.getInput();

            // Process input
            switch (key)
            {
            case 'q': // Quit
                running = false;
                break;
            case 'p': // Pause/Resume
                if (game.isPaused())
                {
                    game.resume();
                }
                else
                {
                    game.pause();
                }
                break;
            case 'r': // Restart
                if (game.isGameOver())
                {
                    game.reset();
                }
                break;
            case KEY_UP:
            case 'w':
                game.processKeyPress(119); // W (UP)
                break;
            case KEY_DOWN:
            case 's':
                game.processKeyPress(115); // S (DOWN)
                break;
            case KEY_LEFT:
            case 'a':
                game.processKeyPress(97); // A (LEFT)
                break;
            case KEY_RIGHT:
            case 'd':
                game.processKeyPress(100); // D (RIGHT)
                break;
            default:
                break;
            }

            // Skip updates if game is paused or over
            if (!game.isPaused() && !game.isGameOver())
            {
                // Update game state
                game.update();

                // Control game speed
                std::this_thread::sleep_for(std::chrono::milliseconds(150));
            }
        }

        return 0;
    }
    catch (const std::exception& e)
    {
        endwin(); // Restore terminal in case of error
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
