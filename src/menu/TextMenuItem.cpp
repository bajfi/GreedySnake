#include "menu/TextMenuItem.h"

namespace GreedySnake
{

TextMenuItem::TextMenuItem(const std::string& labelText, std::function<void()> callback)
{
    // Set the label in the base class
    this->label = labelText;
    this->callback = callback;
}

void TextMenuItem::execute()
{
    if (callback)
    {
        callback();
    }
}

void TextMenuItem::render(Renderer& renderer)
{
    // Rendering logic - this is handled by the renderer
}

} // namespace GreedySnake
