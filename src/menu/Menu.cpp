#include "menu/Menu.h"
#include "menu/SliderMenuItem.h"
#include "menu/ToggleMenuItem.h"
#include <algorithm>

namespace GreedySnake
{

Menu::Menu() : selectedIndex(0), instructions("")
{
}

bool Menu::handleInput(Input input)
{
    if (items.empty())
    {
        return false;
    }

    if (input == Input::UP)
    {
        selectPrevious();
        return true;
    }

    if (input == Input::DOWN)
    {
        selectNext();
        return true;
    }

    if (input == Input::SELECT)
    {
        auto selectedItem = getSelectedItem();

        // Check if it's a toggle item first
        auto toggleItem = std::dynamic_pointer_cast<ToggleMenuItem>(selectedItem);
        if (toggleItem)
        {
            toggleItem->toggle();
            return true;
        }

        // Otherwise execute the standard action
        executeSelected();
        return true;
    }

    if (input == Input::LEFT)
    {
        // For slider items, allow left/right navigation
        auto selectedItem = getSelectedItem();
        auto sliderItem = std::dynamic_pointer_cast<SliderMenuItem>(selectedItem);
        if (sliderItem)
        {
            sliderItem->decrement();
            return true;
        }
    }

    if (input == Input::RIGHT)
    {
        // For slider items, allow left/right navigation
        auto selectedItem = getSelectedItem();
        auto sliderItem = std::dynamic_pointer_cast<SliderMenuItem>(selectedItem);
        if (sliderItem)
        {
            sliderItem->increment();
            return true;
        }
    }

    return false;
}

void Menu::render(Renderer& renderer, const std::string& title) const
{
    renderer.renderMenu(title, getMenuItems(), getSelectedIndex(), instructions);
}

std::shared_ptr<MenuItem> Menu::getSelectedItem() const
{
    if (items.empty() || selectedIndex >= items.size())
    {
        return nullptr;
    }
    return items[selectedIndex];
}

void Menu::selectNext()
{
    if (items.empty())
    {
        return;
    }

    // Deselect current item
    if (selectedIndex < items.size())
    {
        items[selectedIndex]->deselect();
    }

    // Find next selectable item
    size_t nextIndex = selectedIndex;

    do
    {
        nextIndex = (nextIndex + 1) % items.size();
    } while (!items[nextIndex]->isSelectable() && nextIndex != selectedIndex);

    selectedIndex = nextIndex;

    // Select the new item
    items[selectedIndex]->select();
}

void Menu::selectPrevious()
{
    if (items.empty())
    {
        return;
    }

    // Deselect current item
    if (selectedIndex < items.size())
    {
        items[selectedIndex]->deselect();
    }

    // Find previous selectable item
    size_t prevIndex = selectedIndex;

    do
    {
        prevIndex = (prevIndex == 0) ? items.size() - 1 : prevIndex - 1;
    } while (!items[prevIndex]->isSelectable() && prevIndex != selectedIndex);

    selectedIndex = prevIndex;

    // Select the new item
    items[selectedIndex]->select();
}

void Menu::executeSelected() const
{
    auto selectedItem = getSelectedItem();
    if (selectedItem)
    {
        selectedItem->execute();
    }
}

void Menu::clearItems()
{
    items.clear();
    selectedIndex = 0;
}

size_t Menu::getItemCount() const
{
    return items.size();
}

size_t Menu::getSelectedIndex() const
{
    return selectedIndex;
}

std::vector<std::string> Menu::getMenuItems() const
{
    std::vector<std::string> result;
    for (const auto& item : items)
    {
        result.push_back(item->getDisplayString());
    }
    return result;
}

void Menu::setInstructions(const std::string& instructionsText)
{
    instructions = instructionsText;
}

const std::string& Menu::getInstructions() const
{
    return instructions;
}

} // namespace GreedySnake