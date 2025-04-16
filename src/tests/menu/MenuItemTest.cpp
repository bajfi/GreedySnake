#include "menu/MenuItem.h"
#include "menu/Menu.h"
#include "menu/SliderMenuItem.h"
#include "menu/ToggleMenuItem.h"
#include "renderer/Renderer.h"
#include <functional>
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
    void renderMenu(const std::string& title,
                    const std::vector<std::string>& items,
                    size_t selectedIndex,
                    const std::string& instructions = "") override
    {
        lastTitle = title;
        lastMenuItems = items;
        lastSelectedIndex = selectedIndex;
        lastInstructions = instructions;
    }
    bool isWindowOpen() const override
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

    std::string lastTitle;
    std::vector<std::string> lastMenuItems;
    size_t lastSelectedIndex = 0;
    std::string lastInstructions;
};

// Test fixture for Menu tests
class MenuItemTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }
};

// Concrete MenuItem implementation for testing
class TestMenuItem : public MenuItem
{
  public:
    explicit TestMenuItem(const std::string& labelText)
    {
        this->label = labelText;
    }

    void execute() override
    {
        executed = true;
        if (callback)
        {
            callback();
        }
    }

    void render(Renderer& renderer) override
    {
        rendered = true;
    }

    bool isExecuted() const
    {
        return executed;
    }

    bool isRendered() const
    {
        return rendered;
    }

    void reset()
    {
        executed = false;
        rendered = false;
    }

    // Add callback setter
    void setCallback(std::function<void()> cb)
    {
        this->callback = std::move(cb);
    }

    bool rendered = false;
    bool executed = false;
};

TEST_F(MenuItemTest, MenuItemBasics)
{
    TestMenuItem item("Test Item");

    // Test initial state
    EXPECT_EQ(item.getLabel(), "Test Item");
    EXPECT_FALSE(item.isSelected());
    EXPECT_TRUE(item.isSelectable());

    // Test selection state
    item.select();
    EXPECT_TRUE(item.isSelected());

    item.deselect();
    EXPECT_FALSE(item.isSelected());
}

TEST_F(MenuItemTest, MenuItemCallback)
{
    TestMenuItem item("Test Item");
    bool callbackExecuted = false;

    // Use the public setter method
    item.setCallback([&callbackExecuted]() { callbackExecuted = true; });

    item.execute();
    EXPECT_TRUE(callbackExecuted);
}

TEST_F(MenuItemTest, MenuNavigation)
{
    Menu menu;

    // Use the template method to create items
    auto item1 = menu.addItem<TestMenuItem>("Item 1");
    auto item2 = menu.addItem<TestMenuItem>("Item 2");
    auto item3 = menu.addItem<TestMenuItem>("Item 3");

    // Initially, the first item should be selected
    EXPECT_TRUE(item1->isSelected());
    EXPECT_FALSE(item2->isSelected());
    EXPECT_FALSE(item3->isSelected());

    // Navigate to the next item
    menu.selectNext();
    EXPECT_FALSE(item1->isSelected());
    EXPECT_TRUE(item2->isSelected());
    EXPECT_FALSE(item3->isSelected());

    // Navigate to the previous item
    menu.selectPrevious();
    EXPECT_TRUE(item1->isSelected());
    EXPECT_FALSE(item2->isSelected());
    EXPECT_FALSE(item3->isSelected());

    // Navigate past the end (should wrap around)
    menu.selectNext();
    menu.selectNext();
    menu.selectNext();
    EXPECT_TRUE(item1->isSelected());

    // Navigate past the beginning (should wrap around)
    menu.selectPrevious();
    EXPECT_TRUE(item3->isSelected());
}

TEST_F(MenuItemTest, MenuExecution)
{
    Menu menu;
    bool item1Executed = false;
    bool item2Executed = false;

    auto item1 = menu.addItem<TestMenuItem>("Item 1");
    static_cast<TestMenuItem*>(item1.get())
        ->setCallback([&item1Executed]() { item1Executed = true; });

    auto item2 = menu.addItem<TestMenuItem>("Item 2");
    static_cast<TestMenuItem*>(item2.get())
        ->setCallback([&item2Executed]() { item2Executed = true; });

    // Execute the selected item (should be the first item)
    menu.executeSelected();
    EXPECT_TRUE(item1Executed);
    EXPECT_FALSE(item2Executed);

    // Select and execute the second item
    menu.selectNext();
    menu.executeSelected();
    EXPECT_TRUE(item2Executed);
}

TEST_F(MenuItemTest, MenuRender)
{
    Menu menu;
    auto item1 = menu.addItem<TestMenuItem>("Item 1");
    auto item2 = menu.addItem<TestMenuItem>("Item 2");

    // Create a mock renderer
    MockRenderer renderer;

    // Render the menu
    menu.render(renderer, "Test Menu");

    // Verify the menu was rendered correctly
    EXPECT_EQ(menu.getItemCount(), 2);
    EXPECT_EQ(menu.getSelectedIndex(), 0);
}

// Test for direct menu input handling
TEST(MenuTest, InputHandlingForSettings)
{
    Menu menu;

    // Add slider item to the menu
    int sliderValue = 5;
    auto sliderItem = menu.addItem<SliderMenuItem>(
        "Speed", 1, 10, sliderValue, [&sliderValue](int value) { sliderValue = value; });

    // Add toggle item to the menu
    bool toggleValue = false;
    auto toggleItem = menu.addItem<ToggleMenuItem>(
        "Enabled", toggleValue, [&toggleValue](bool value) { toggleValue = value; });

    // Initial values
    EXPECT_EQ(5, sliderValue);
    EXPECT_FALSE(toggleValue);

    // Test RIGHT arrow increases slider value
    EXPECT_TRUE(menu.handleInput(Input::RIGHT));
    EXPECT_EQ(6, sliderValue);

    // Test LEFT arrow decreases slider value
    EXPECT_TRUE(menu.handleInput(Input::LEFT));
    EXPECT_EQ(5, sliderValue);

    // Test multiple RIGHT increases
    for (int i = 0; i < 3; i++)
    {
        menu.handleInput(Input::RIGHT);
    }
    EXPECT_EQ(8, sliderValue);

    // Test multiple LEFT decreases
    for (int i = 0; i < 2; i++)
    {
        menu.handleInput(Input::LEFT);
    }
    EXPECT_EQ(6, sliderValue);

    // Navigate to toggle item
    menu.handleInput(Input::DOWN);

    // Test SELECT toggles the value
    EXPECT_TRUE(menu.handleInput(Input::SELECT));
    EXPECT_TRUE(toggleValue);

    // Test toggle again
    EXPECT_TRUE(menu.handleInput(Input::SELECT));
    EXPECT_FALSE(toggleValue);
}