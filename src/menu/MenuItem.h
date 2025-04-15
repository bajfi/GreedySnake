#ifndef GREEDYSNAKE_MENUITEM_H
#define GREEDYSNAKE_MENUITEM_H

#include "renderer/Renderer.h"
#include <functional>
#include <memory>
#include <string>

namespace GreedySnake
{

// Abstract base class for all menu items
class MenuItem
{
  public:
    MenuItem() : selected(false)
    {
    }
    virtual ~MenuItem() = default;

    // Get the label of the menu item
    [[nodiscard]] std::string getLabel() const
    {
        return label;
    }

    // Check if the menu item is currently selected
    [[nodiscard]] bool isSelected() const
    {
        return selected;
    }

    // Mark the item as selected
    void select()
    {
        selected = true;
    }

    // Mark the item as deselected
    void deselect()
    {
        selected = false;
    }

    // Check if the menu item can be selected
    [[nodiscard]] virtual bool isSelectable() const
    {
        return true;
    }

    // Execute the menu item's action (pure virtual)
    virtual void execute() = 0;

    // Render the menu item (pure virtual)
    virtual void render(Renderer& renderer) = 0;

  protected:
    std::string label;
    bool selected;
    std::function<void()> callback;
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_MENUITEM_H