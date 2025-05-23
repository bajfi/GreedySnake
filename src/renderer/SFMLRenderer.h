#pragma once

#include "renderer/Renderer.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

namespace GreedySnake
{

/**
 * @brief SFML implementation of the game renderer
 */
class SFMLRenderer : public Renderer
{
  public:
    /**
     * @brief Constructor for the SFML renderer
     * @param width Window width in pixels
     * @param height Window height in pixels
     * @param title Window title
     */
    SFMLRenderer(int width, int height, const std::string& title);

    /**
     * @brief Destructor to clean up resources
     */
    ~SFMLRenderer() override;

    /**
     * @brief Initialize the SFML renderer
     * @return True if initialization was successful
     */
    bool initialize() override;

    /**
     * @brief Clean up SFML resources
     */
    void shutdown() override;

    /**
     * @brief Render the game state using SFML
     * @param game Reference to the game state to render
     */
    void render(const Game& game) override;

    /**
     * @brief Render a menu with title and items
     * @param title The title to display
     * @param items List of menu items to display
     * @param selectedIndex Index of the currently selected item
     * @param instructions Optional instructions to display below the menu
     */
    void renderMenu(const std::string& title,
                    const std::vector<std::string>& items,
                    size_t selectedIndex,
                    const std::string& instructions = "") override;

    /**
     * @brief Check if the SFML window is still open
     * @return True if the window is open
     */
    bool isWindowOpen() const override;

    /**
     * @brief Process SFML window events and input for a Game object
     * @param game Reference to the game for processing input
     * @return True if the game should continue running
     */
    bool handleEvents(Game& game) override;

    /**
     * @brief Process SFML window events and input
     * @param input Reference to input enum to set
     * @return True if the game should continue running
     */
    bool handleEvents(Input& input) override;

    /**
     * @brief Load textures and other resources
     * @return True if resources were loaded successfully
     */
    bool loadResources();

    /**
     * @brief Get the window title
     * @return Window title
     */
    std::string getWindowTitle() const;

    /**
     * @brief Get the window width
     * @return Window width in pixels
     */
    int getWindowWidth() const;

    /**
     * @brief Get the window height
     * @return Window height in pixels
     */
    int getWindowHeight() const;

    /**
     * @brief Calculate cell size based on board dimensions and window size
     * @return Cell size in pixels
     */
    float getCellSize() const;

    /**
     * @brief Convert game position to screen coordinates
     * @param position Game board position
     * @return Corresponding screen position in pixels
     */
    sf::Vector2f gameToScreenPosition(const Position& position) const;

  private:
    sf::RenderWindow window;
    std::string windowTitle;
    int windowWidth;
    int windowHeight;
    float cellSize;
    int currentBoardWidth;  // Track current board width
    int currentBoardHeight; // Track current board height

    // Game textures and sprites
    sf::Texture snakeHeadTexture;
    sf::Texture snakeBodyTexture;
    sf::Texture foodTexture;
    sf::Texture wallTexture;
    sf::Texture backgroundTexture;

    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text pausedText;
    sf::Text menuTitleText;
    sf::Text menuItemText;

    // Drawing helper methods
    void drawBoard(const Board& board);
    void drawSnake(const Snake& snake);
    void drawFood(const Food& food);
    void drawScore(int score);
    void drawGameState(bool gameOver, bool paused);
    void drawBackground();
    void drawMenu(const std::string& title,
                  const std::vector<std::string>& items,
                  size_t selectedIndex,
                  const std::string& instructions = "");

    // Create default textures when actual textures can't be loaded
    void createDefaultTextures();

    // Convert SFML events to our Input enum
    Input convertSFMLEvent(const sf::Event& event);
};

} // namespace GreedySnake