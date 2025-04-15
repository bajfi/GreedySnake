#include "renderer/SFMLRenderer.h"
#include "game/Game.h"
#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>

using namespace GreedySnake;

class SFMLRendererTest : public ::testing::Test
{
  protected:
    // Test game with a small board
    Game game{10, 10, 3};
    SFMLRenderer renderer{800, 600, "Test Window"};

    void SetUp() override
    {
        game.initialize();
    }
};

// Test the renderer initialization
TEST_F(SFMLRendererTest, Initialization)
{
    // This test will run in CI environments, so we can't assume a display is available.
    // We just check that the renderer object is created without errors.
    EXPECT_NO_THROW({ SFMLRenderer testRenderer(800, 600, "Test Window"); });
}

// Test resource loading
TEST_F(SFMLRendererTest, ResourceLoading)
{
    // We can verify that resource loading doesn't throw exceptions
    EXPECT_NO_THROW({ EXPECT_TRUE(renderer.loadResources()); });
}

// Test window properties
TEST_F(SFMLRendererTest, WindowProperties)
{
    renderer.loadResources(); // Must load resources first

    // Check window title and size
    EXPECT_EQ(renderer.getWindowTitle(), "Test Window");
    EXPECT_EQ(renderer.getWindowWidth(), 800);
    EXPECT_EQ(renderer.getWindowHeight(), 600);
}

// Test game object to screen coordinate mapping
TEST_F(SFMLRendererTest, CoordinateMapping)
{
    renderer.loadResources(); // Must load resources first

    // Get cell size used for rendering
    float cellSize = renderer.getCellSize();
    EXPECT_GT(cellSize, 0);

    // Since our gameToScreenPosition includes offsets to center the board,
    // we can't test the exact mapping, but we can test that the returned
    // position is within reasonable bounds
    sf::Vector2f screenPos = renderer.gameToScreenPosition(Position(5, 5));
    EXPECT_GT(screenPos.x, 0);
    EXPECT_GT(screenPos.y, 0);
    EXPECT_LT(screenPos.x, renderer.getWindowWidth());
    EXPECT_LT(screenPos.y, renderer.getWindowHeight());
}