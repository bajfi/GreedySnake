#ifndef GREEDYSNAKE_SLIDERMENUITEM_H
#define GREEDYSNAKE_SLIDERMENUITEM_H

#include "menu/MenuItem.h"
#include <functional>

namespace GreedySnake
{

// A menu item for adjustable numeric values
class SliderMenuItem : public MenuItem
{
  public:
    // Constructor with label, min/max values, initial value, and callback
    SliderMenuItem(const std::string& label,
                   int min,
                   int max,
                   int initialValue,
                   std::function<void(int)> valueCallback = nullptr);
    virtual ~SliderMenuItem() = default;

    // Execute the callback function
    void execute() override;

    // Render the slider menu item
    void render(Renderer& renderer) override;

    // Get the display string with the current value
    [[nodiscard]] std::string getDisplayString() const override;

    // Increment the value and call the callback
    void increment();

    // Decrement the value and call the callback
    void decrement();

    // Get the current value
    [[nodiscard]] int getValue() const
    {
        return currentValue;
    }

    // Get the minimum value
    [[nodiscard]] int getMinValue() const
    {
        return minValue;
    }

    // Get the maximum value
    [[nodiscard]] int getMaxValue() const
    {
        return maxValue;
    }

  private:
    int minValue;
    int maxValue;
    int currentValue;
    std::function<void(int)> valueCallback;
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_SLIDERMENUITEM_H