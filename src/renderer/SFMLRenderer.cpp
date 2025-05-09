#include "renderer/SFMLRenderer.h"
#include <iostream>

namespace GreedySnake
{

SFMLRenderer::SFMLRenderer(int width, int height, const std::string& title)
    : windowTitle(title),
      windowWidth(width),
      windowHeight(height),
      cellSize(0.0f),
      currentBoardWidth(20),
      currentBoardHeight(20) // Default to 20x20
{
}

SFMLRenderer::~SFMLRenderer()
{
    shutdown();
}

bool SFMLRenderer::initialize()
{
    // Create the SFML window
    window.create(sf::VideoMode(windowWidth, windowHeight),
                  windowTitle,
                  sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // Load resources
    return loadResources();
}

void SFMLRenderer::shutdown()
{
    if (window.isOpen())
    {
        window.close();
    }
}

bool SFMLRenderer::loadResources()
{
    // Create default textures for the game entities
    createDefaultTextures();

    // Load font for text elements
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    {
        std::cerr << "Failed to load primary font, trying alternatives..." << std::endl;
        // Try loading alternative fonts with better Unicode support
        if (!font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf") &&
            !font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf") &&
            !font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"))
        {
            std::cerr << "Failed to load any fonts!" << std::endl;
            return false;
        }
    }

    // Initialize text elements
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over! Press R to restart");

    pausedText.setFont(font);
    pausedText.setCharacterSize(40);
    pausedText.setFillColor(sf::Color::Yellow);
    pausedText.setString("Paused. Press P to resume");

    // Initialize menu text elements
    menuTitleText.setFont(font);
    menuTitleText.setCharacterSize(40);
    menuTitleText.setFillColor(sf::Color::White);

    menuItemText.setFont(font);
    menuItemText.setCharacterSize(24);
    menuItemText.setFillColor(sf::Color::White);

    // Initialize cell size with a default value for testing purposes
    // This will be recalculated during rendering with the actual board
    cellSize = 30.0f;

    return true;
}

void SFMLRenderer::render(const Game& game)
{
    if (!window.isOpen())
    {
        return;
    }

    // Clear the window
    window.clear(sf::Color(0, 32, 48));

    // Update cell size based on the board dimensions
    const Board& board = game.getBoard();

    // Store the current board dimensions
    currentBoardWidth = board.getWidth();
    currentBoardHeight = board.getHeight();

    cellSize =
        std::min(static_cast<float>(windowWidth) / board.getWidth(),
                 static_cast<float>(windowHeight - 60) / board.getHeight() // Leave space for score
        );

    // Center the board on the screen
    float boardWidth = cellSize * board.getWidth();
    float boardHeight = cellSize * board.getHeight();
    float offsetX = (windowWidth - boardWidth) / 2.0f;
    float offsetY = (windowHeight - boardHeight - 30) / 2.0f + 30; // Adjust for score text at top

    // Draw the background
    drawBackground();

    // Draw the board (walls)
    drawBoard(game.getBoard());

    // Draw the food
    drawFood(game.getFood());

    // Draw the snake
    drawSnake(game.getSnake());

    // Draw the score
    drawScore(game.getScore());

    // Draw game state messages
    drawGameState(game.isGameOver(), game.isPaused());

    // Display everything
    window.display();
}

void SFMLRenderer::renderMenu(const std::string& title,
                              const std::vector<std::string>& items,
                              size_t selectedIndex,
                              const std::string& instructions)
{
    if (!window.isOpen())
    {
        return;
    }

    // Clear the window
    window.clear(sf::Color(0, 32, 48));

    // Draw the background
    drawBackground();

    // Draw the menu
    drawMenu(title, items, selectedIndex, instructions);

    // Display everything
    window.display();
}

bool SFMLRenderer::isWindowOpen() const
{
    return window.isOpen();
}

bool SFMLRenderer::handleEvents(Game& game)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return false;
        }

        // Handle keyboard events
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                window.close();
                return false;

            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                game.processKeyPress(119); // W key code
                break;

            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                game.processKeyPress(115); // S key code
                break;

            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                game.processKeyPress(97); // A key code
                break;

            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                game.processKeyPress(100); // D key code
                break;

            case sf::Keyboard::P:
                // Toggle pause state
                if (game.isPaused())
                {
                    game.resume();
                }
                else
                {
                    game.pause();
                }
                break;

            case sf::Keyboard::R:
                // Reset game if it's over
                if (game.isGameOver())
                {
                    game.reset();
                }
                break;

            case sf::Keyboard::Q:
                game.processKeyPress(113); // Q key code (quit)
                break;

            default:
                break;
            }
        }
    }

    return true;
}

bool SFMLRenderer::handleEvents(Input& input)
{
    // Default to no input
    input = Input::NONE;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            input = Input::QUIT;
            return false;
        }

        // Handle keyboard events for menu navigation
        if (event.type == sf::Event::KeyPressed)
        {
            input = convertSFMLEvent(event);
            // Stop processing after the first meaningful input
            if (input != Input::NONE)
            {
                break;
            }
        }
    }

    return true;
}

Input SFMLRenderer::convertSFMLEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return Input::NONE;

    switch (event.key.code)
    {
    case sf::Keyboard::Up:
    case sf::Keyboard::W:
        return Input::UP;
    case sf::Keyboard::Down:
    case sf::Keyboard::S:
        return Input::DOWN;
    case sf::Keyboard::Left:
    case sf::Keyboard::A:
        return Input::LEFT;
    case sf::Keyboard::Right:
    case sf::Keyboard::D:
        return Input::RIGHT;
    case sf::Keyboard::Return:
    case sf::Keyboard::Space:
        return Input::SELECT;
    case sf::Keyboard::Escape:
        return Input::BACK;
    case sf::Keyboard::P:
        return Input::PAUSE;
    case sf::Keyboard::Q:
        return Input::QUIT;
    default:
        return Input::NONE;
    }
}

std::string SFMLRenderer::getWindowTitle() const
{
    return windowTitle;
}

int SFMLRenderer::getWindowWidth() const
{
    return windowWidth;
}

int SFMLRenderer::getWindowHeight() const
{
    return windowHeight;
}

float SFMLRenderer::getCellSize() const
{
    return cellSize > 0.0f ? cellSize : 30.0f; // Return default if not yet calculated
}

sf::Vector2f SFMLRenderer::gameToScreenPosition(const Position& position) const
{
    // Calculate the top-left corner of the game board
    const float offsetX = (windowWidth - cellSize * currentBoardWidth) / 2.0f;
    const float offsetY =
        (windowHeight - cellSize * currentBoardHeight - 30) / 2.0f + 30; // Space for score

    return sf::Vector2f(offsetX + position.x * cellSize, offsetY + position.y * cellSize);
}

void SFMLRenderer::drawBoard(const Board& board)
{
    sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
    sf::RectangleShape borderShape(sf::Vector2f(cellSize, cellSize));
    borderShape.setFillColor(sf::Color(100, 100, 100));

    // Calculate board offset to center it
    float offsetX = (windowWidth - cellSize * board.getWidth()) / 2.0f;
    float offsetY = (windowHeight - cellSize * board.getHeight() - 30) / 2.0f + 30;

    // Draw the grid and walls
    for (int y = 0; y < board.getHeight(); ++y)
    {
        for (int x = 0; x < board.getWidth(); ++x)
        {
            Position pos(x, y);

            if (x == 0 || y == 0 || x == board.getWidth() - 1 || y == board.getHeight() - 1)
            {
                // Draw wall/border
                borderShape.setPosition(offsetX + x * cellSize, offsetY + y * cellSize);
                window.draw(borderShape);
            }
        }
    }
}

void SFMLRenderer::drawSnake(const Snake& snake)
{
    // Get the snake body segments
    const std::vector<Position>& body = snake.getBody();
    if (body.empty())
        return;

    // Calculate board offset to center it
    float offsetX = (windowWidth - cellSize * currentBoardWidth) / 2.0f;
    float offsetY = (windowHeight - cellSize * currentBoardHeight - 30) / 2.0f + 30;

    // Draw the head
    sf::CircleShape headShape(cellSize / 2.f);
    headShape.setFillColor(sf::Color::Green);
    headShape.setPosition(offsetX + body[0].x * cellSize, offsetY + body[0].y * cellSize);
    window.draw(headShape);

    // Draw the body segments
    sf::RectangleShape bodyShape(sf::Vector2f(cellSize * 0.9f, cellSize * 0.9f));
    bodyShape.setFillColor(sf::Color(0, 180, 0));

    for (size_t i = 1; i < body.size(); ++i)
    {
        bodyShape.setPosition(offsetX + body[i].x * cellSize + cellSize * 0.05f,
                              offsetY + body[i].y * cellSize + cellSize * 0.05f);
        window.draw(bodyShape);
    }
}

void SFMLRenderer::drawFood(const Food& food)
{
    // Calculate board offset to center it
    float offsetX = (windowWidth - cellSize * currentBoardWidth) / 2.0f;
    float offsetY = (windowHeight - cellSize * currentBoardHeight - 30) / 2.0f + 30;

    // Draw the food
    sf::CircleShape foodShape(cellSize / 2.5f);
    foodShape.setFillColor(sf::Color::Red);
    foodShape.setPosition(offsetX + food.getPosition().x * cellSize + cellSize / 4.f,
                          offsetY + food.getPosition().y * cellSize + cellSize / 4.f);
    window.draw(foodShape);
}

void SFMLRenderer::drawScore(int score)
{
    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);
}

void SFMLRenderer::drawGameState(bool gameOver, bool paused)
{
    if (gameOver)
    {
        // Position game over text in the center
        sf::FloatRect textBounds = gameOverText.getLocalBounds();
        gameOverText.setPosition((windowWidth - textBounds.width) / 2.f,
                                 (windowHeight - textBounds.height) / 2.f - 50.f);
        window.draw(gameOverText);
    }
    else if (paused)
    {
        // Position paused text in the center
        sf::FloatRect textBounds = pausedText.getLocalBounds();
        pausedText.setPosition((windowWidth - textBounds.width) / 2.f,
                               (windowHeight - textBounds.height) / 2.f - 50.f);
        window.draw(pausedText);
    }
}

void SFMLRenderer::drawBackground()
{
    sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));
    background.setFillColor(sf::Color(0, 32, 48));
    window.draw(background);
}

void SFMLRenderer::createDefaultTextures()
{
    // Create default colored textures when we can't load from files

    // Snake head (green circle)
    sf::Image headImage;
    headImage.create(32, 32, sf::Color::Transparent);
    for (unsigned int y = 0; y < 32; ++y)
    {
        for (unsigned int x = 0; x < 32; ++x)
        {
            int dx = x - 16;
            int dy = y - 16;
            if (dx * dx + dy * dy < 16 * 16)
            {
                headImage.setPixel(x, y, sf::Color::Green);
            }
        }
    }
    snakeHeadTexture.loadFromImage(headImage);

    // Snake body (green square)
    sf::Image bodyImage;
    bodyImage.create(32, 32, sf::Color(0, 180, 0));
    snakeBodyTexture.loadFromImage(bodyImage);

    // Food (red circle)
    sf::Image foodImage;
    foodImage.create(32, 32, sf::Color::Transparent);
    for (unsigned int y = 0; y < 32; ++y)
    {
        for (unsigned int x = 0; x < 32; ++x)
        {
            int dx = x - 16;
            int dy = y - 16;
            if (dx * dx + dy * dy < 12 * 12)
            {
                foodImage.setPixel(x, y, sf::Color::Red);
            }
        }
    }
    foodTexture.loadFromImage(foodImage);

    // Wall (gray square)
    sf::Image wallImage;
    wallImage.create(32, 32, sf::Color(100, 100, 100));
    wallTexture.loadFromImage(wallImage);

    // Background (dark blue)
    sf::Image backgroundImage;
    backgroundImage.create(32, 32, sf::Color(0, 32, 48));
    backgroundTexture.loadFromImage(backgroundImage);
}

void SFMLRenderer::drawMenu(const std::string& title,
                            const std::vector<std::string>& items,
                            size_t selectedIndex,
                            const std::string& instructions)
{
    const float padding = 20.0f;
    const float itemHeight = 40.0f;
    const float startY = 150.0f;

    // Draw title
    menuTitleText.setString(sf::String::fromUtf8(title.begin(), title.end()));
    menuTitleText.setPosition((windowWidth - menuTitleText.getLocalBounds().width) / 2.0f, 50.0f);
    window.draw(menuTitleText);

    // Draw menu items
    for (size_t i = 0; i < items.size(); ++i)
    {
        // Highlight selected item
        if (i == selectedIndex)
        {
            menuItemText.setFillColor(sf::Color::Yellow);

            // Draw selection indicator (arrow)
            sf::String itemText = sf::String::fromUtf8(items[i].begin(), items[i].end());
            menuItemText.setString("> " + itemText);
        }
        else
        {
            menuItemText.setFillColor(sf::Color::White);
            sf::String itemText = sf::String::fromUtf8(items[i].begin(), items[i].end());
            menuItemText.setString("  " + itemText);
        }

        // Center horizontally, position vertically
        menuItemText.setPosition((windowWidth - menuItemText.getLocalBounds().width) / 2.0f,
                                 startY + i * itemHeight);

        window.draw(menuItemText);
    }

    // Draw instructions if provided
    if (!instructions.empty())
    {
        sf::Text instructionsText;
        instructionsText.setFont(font);
        instructionsText.setCharacterSize(16);
        instructionsText.setFillColor(sf::Color(150, 150, 150)); // Light gray

        // Convert UTF-8 string to sf::String for proper Unicode display
        sf::String utf8Instructions =
            sf::String::fromUtf8(instructions.begin(), instructions.end());
        instructionsText.setString(utf8Instructions);

        // Position at bottom of menu items with some spacing
        float instructionsY = startY + items.size() * itemHeight + 40.0f;
        instructionsText.setPosition((windowWidth - instructionsText.getLocalBounds().width) / 2.0f,
                                     instructionsY);

        window.draw(instructionsText);
    }
}

} // namespace GreedySnake