#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

#include "game/GameApp.h"

using namespace GreedySnake;

int main()
{
    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    try
    {
        // Create and initialize the game application
        GameApp app(800, 600, "Greedy Snake - SFML Renderer");

        if (!app.initialize())
        {
            std::cerr << "Failed to initialize the game application!" << std::endl;
            return 1;
        }

        // Run the main game loop
        return app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
