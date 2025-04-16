#include "menu/Input.h"
#include "menu/Menu.h"
#include "menu/SliderMenuItem.h"
#include "menu/TextMenuItem.h"
#include "menu/ToggleMenuItem.h"
#include "renderer/Renderer.h"
#include <gtest/gtest.h>

using namespace GreedySnake;

// Mock renderer for testing
class MockRenderer : public Renderer
{
  public:
    bool initialize() override
    {
        return true;
    }
    void shutdown() override
    {
    }
    void render(const Game& game) override
    {
    }
    [[nodiscard]] bool isWindowOpen() const override
    {
        return true;
    }
    bool handleEvents(Game& game) override
    {
        return true;
    }
    bool handleEvents(Input& input) override
    {
        return true;
    }
    void renderMenu(const std::string& title,
                    const std::vector<std::string>& items,
                    size_t selectedIndex,
                    const std::string& instructions = "") override
    {
    }
};

class SpecializedMenuItemTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }

    // Mock renderer for testing
    MockRenderer renderer;
};

TEST_F(SpecializedMenuItemTest, TextMenuItemBasics)
{
    bool executed = false;
    TextMenuItem item("Text Item", [&executed]() { executed = true; });

    EXPECT_EQ("Text Item", item.getLabel());
    EXPECT_FALSE(item.isSelected());

    item.select();
    EXPECT_TRUE(item.isSelected());

    item.execute();
    EXPECT_TRUE(executed);

    // This just shouldn't crash
    item.render(renderer);
}

TEST_F(SpecializedMenuItemTest, SliderMenuItemBasics)
{
    int value = 5;
    SliderMenuItem item("Slider Item", 0, 10, 5, [&value](int newValue) { value = newValue; });

    EXPECT_EQ("Slider Item", item.getLabel());
    EXPECT_EQ(5, item.getValue());
    EXPECT_FALSE(item.isSelected());

    item.select();
    EXPECT_TRUE(item.isSelected());

    // Test increment
    item.increment();
    EXPECT_EQ(6, item.getValue());
    EXPECT_EQ(6, value); // Callback should have updated the value

    // Test decrement
    item.decrement();
    EXPECT_EQ(5, item.getValue());
    EXPECT_EQ(5, value);

    // Test boundaries
    for (int i = 0; i < 20; i++)
    {
        item.increment();
    }
    EXPECT_EQ(10, item.getValue()); // Should be capped at max

    for (int i = 0; i < 20; i++)
    {
        item.decrement();
    }
    EXPECT_EQ(0, item.getValue()); // Should be capped at min

    // This just shouldn't crash
    item.render(renderer);

    // Execute should do the same as increment when selected
    item.execute();
    EXPECT_EQ(1, item.getValue());
}

TEST_F(SpecializedMenuItemTest, ToggleMenuItemBasics)
{
    bool toggleState = false;
    ToggleMenuItem item(
        "Toggle Item", false, [&toggleState](bool newState) { toggleState = newState; });

    EXPECT_EQ("Toggle Item", item.getLabel());
    EXPECT_FALSE(item.isToggled());
    EXPECT_FALSE(item.isSelected());

    item.select();
    EXPECT_TRUE(item.isSelected());

    // Test toggle
    item.toggle();
    EXPECT_TRUE(item.isToggled());
    EXPECT_TRUE(toggleState); // Callback should have updated the state

    item.toggle();
    EXPECT_FALSE(item.isToggled());
    EXPECT_FALSE(toggleState);

    // This just shouldn't crash
    item.render(renderer);

    // Execute should toggle
    item.execute();
    EXPECT_TRUE(item.isToggled());
}

// Test slider menu item with menu input handling
TEST_F(SpecializedMenuItemTest, SliderMenuItemInputHandling)
{
    // Create a menu with a slider item
    Menu menu;
    int value = 5;
    menu.addItem<SliderMenuItem>("Speed", 1, 10, 5, [&value](int newValue) { value = newValue; });

    // Verify initial state
    EXPECT_EQ(5, value);

    // Test RIGHT arrow key increments value
    EXPECT_TRUE(menu.handleInput(Input::RIGHT));
    EXPECT_EQ(6, value);

    // Test LEFT arrow key decrements value
    EXPECT_TRUE(menu.handleInput(Input::LEFT));
    EXPECT_EQ(5, value);

    // Test multiple increments
    for (int i = 0; i < 3; i++)
    {
        menu.handleInput(Input::RIGHT);
    }
    EXPECT_EQ(8, value);

    // Test boundary (should not exceed max)
    for (int i = 0; i < 5; i++)
    {
        menu.handleInput(Input::RIGHT);
    }
    EXPECT_EQ(10, value); // Should be capped at max

    // Test boundary (should not go below min)
    for (int i = 0; i < 15; i++)
    {
        menu.handleInput(Input::LEFT);
    }
    EXPECT_EQ(1, value); // Should be capped at min
}

// Test toggle menu item with menu input handling
TEST_F(SpecializedMenuItemTest, ToggleMenuItemInputHandling)
{
    // Create a menu with a toggle item
    Menu menu;
    bool state = false;
    menu.addItem<ToggleMenuItem>("Walls", false, [&state](bool newState) { state = newState; });

    // Verify initial state
    EXPECT_FALSE(state);

    // Test SELECT toggles the state
    EXPECT_TRUE(menu.handleInput(Input::SELECT));
    EXPECT_TRUE(state);

    // Test toggle again
    EXPECT_TRUE(menu.handleInput(Input::SELECT));
    EXPECT_FALSE(state);

    // Test multiple toggles
    EXPECT_TRUE(menu.handleInput(Input::SELECT));
    EXPECT_TRUE(state);
    EXPECT_TRUE(menu.handleInput(Input::SELECT));
    EXPECT_FALSE(state);
}