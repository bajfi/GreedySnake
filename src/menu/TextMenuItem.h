#ifndef GREEDYSNAKE_TEXTMENUITEM_H
#define GREEDYSNAKE_TEXTMENUITEM_H

#include "menu/MenuItem.h"

namespace GreedySnake
{

// A simple text-based menu item with a callback
class TextMenuItem : public MenuItem
{
  public:
    // Constructor with label and optional callback
    TextMenuItem(const std::string& label, std::function<void()> callback = nullptr);
    virtual ~TextMenuItem() = default;

    // Execute the callback function when selected
    void execute() override;

    // Render the text menu item
    void render(Renderer& renderer) override;
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_TEXTMENUITEM_H