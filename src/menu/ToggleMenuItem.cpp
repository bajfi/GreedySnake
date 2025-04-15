#include "menu/ToggleMenuItem.h"

namespace GreedySnake
{

ToggleMenuItem::ToggleMenuItem(const std::string& label,
                               bool initialState,
                               std::function<void(bool)> stateCallback)
    : state(initialState), stateCallback(std::move(stateCallback))
{
    this->label = label;
}

void ToggleMenuItem::execute()
{
    // Executing a toggle item toggles its state
    toggle();
}

void ToggleMenuItem::render(Renderer& renderer)
{
    // Rendering logic - this is handled by the renderer
}

void ToggleMenuItem::toggle()
{
    state = !state;
    if (stateCallback)
    {
        stateCallback(state);
    }
}

} // namespace GreedySnake