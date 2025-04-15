#include "game/GameApp.h"
#include "menu/MainMenuState.h"
#include "renderer/SFMLRenderer.h"
#include <chrono>
#include <iostream>
#include <thread>

namespace GreedySnake
{

GameApp::GameApp(int windowWidth, int windowHeight, const std::string& windowTitle)
    : windowWidth(windowWidth), windowHeight(windowHeight), windowTitle(windowTitle)
{
}

GameApp::~GameApp()
{
    // Specific cleanup if needed
    if (renderer)
    {
        renderer->shutdown();
    }
}

bool GameApp::initialize()
{
    try
    {
        // Initialize settings (load from file or use defaults)
        settings = std::make_unique<GameSettings>();
        settings->loadFromFile(); // Try to load from default location

        // Create the renderer
        renderer = std::make_unique<SFMLRenderer>(windowWidth, windowHeight, windowTitle);
        if (!renderer->initialize())
        {
            std::cerr << "Failed to initialize renderer!" << std::endl;
            return false;
        }

        // Create state manager with this app as owner
        stateManager = std::make_unique<GameStateManager>(this);

        // Set initial state to main menu
        stateManager->pushState(std::make_unique<MainMenuState>(stateManager.get()));

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error during initialization: " << e.what() << std::endl;
        return false;
    }
}

int GameApp::run()
{
    if (!renderer || !stateManager)
    {
        std::cerr << "Application not properly initialized!" << std::endl;
        return 1;
    }

    // Time tracking for game updates
    auto lastFrameTime = std::chrono::steady_clock::now();

    // Main game loop
    while (renderer->isWindowOpen() && stateManager->hasActiveState())
    {
        // Calculate delta time
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastFrameTime).count();
        lastFrameTime = currentTime;

        // Process input events
        processInput();

        // Update game state
        update(deltaTime);

        // Render the current frame
        render();

        // Limit CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}

GameSettings* GameApp::getSettings()
{
    return settings.get();
}

GameStateManager* GameApp::getStateManager()
{
    return stateManager.get();
}

void GameApp::processInput()
{
    // Process window events and translate to our Input enum
    // This will depend on the renderer implementation
    // For SFML, we'll need to handle events and translate them

    // Example of translating SFML events to our Input type
    // and forwarding them to the state manager
    Input input = Input::NONE;

    if (renderer->handleEvents(input))
    {
        if (input != Input::NONE)
        {
            stateManager->processInput(input);
        }
    }
}

void GameApp::update(float deltaTime)
{
    if (stateManager->hasActiveState())
    {
        stateManager->update(deltaTime);
    }
}

void GameApp::render()
{
    if (stateManager->hasActiveState())
    {
        stateManager->render(*renderer);
    }
}

} // namespace GreedySnake