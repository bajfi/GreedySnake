#ifndef GREEDYSNAKE_TOGGLEMENUITEM_H
#define GREEDYSNAKE_TOGGLEMENUITEM_H

#include "menu/MenuItem.h"
#include <functional>

namespace GreedySnake
{

// A menu item for toggling boolean settings
class ToggleMenuItem : public MenuItem
{
  public:
    // Constructor with label, initial state, and callback
    ToggleMenuItem(const std::string& label,
                   bool initialState,
                   std::function<void(bool)> stateCallback = nullptr);
    virtual ~ToggleMenuItem() = default;

    // Execute the toggle action
    void execute() override;

    // Render the toggle menu item
    void render(Renderer& renderer) override;

    // Toggle the state and call the callback
    void toggle();

    // Get the current state
    [[nodiscard]] bool isToggled() const
    {
        return state;
    }

  private:
    bool state;
    std::function<void(bool)> stateCallback;
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_TOGGLEMENUITEM_H