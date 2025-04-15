#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

#include "game/Game.h"
#include "renderer/SFMLRenderer.h"

using namespace GreedySnake;

int main()
{
    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    try
    {
        // Create game with 20x20 board
        Game game(20, 20, 3);

        // Create SFML renderer with 800x600 window
        SFMLRenderer renderer(800, 600, "Greedy Snake - SFML Renderer");

        // Initialize the game and renderer
        game.initialize();
        if (!renderer.initialize())
        {
            std::cerr << "Failed to initialize renderer!" << std::endl;
            return 1;
        }

        // Game update interval (milliseconds)
        const int updateInterval = 150; // Adjust speed as needed
        auto lastUpdateTime = std::chrono::steady_clock::now();

        // Main game loop
        while (renderer.isWindowOpen())
        {
            // Process window events and input
            if (!renderer.handleEvents(game))
            {
                break;
            }

            // Update game logic at fixed intervals
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsed =
                std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime)
                    .count();

            // Skip updates if game is paused or over
            if (!game.isPaused() && !game.isGameOver() && elapsed >= updateInterval)
            {
                game.update();
                lastUpdateTime = currentTime;
            }

            // Render current game state
            renderer.render(game);

            // Limit CPU usage
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
