#include "menu/SliderMenuItem.h"
#include <iomanip>
#include <sstream>

namespace GreedySnake
{

SliderMenuItem::SliderMenuItem(const std::string& labelText,
                               int min,
                               int max,
                               int initialValue,
                               std::function<void(int)> valueCallback)
    : minValue(min), maxValue(max), currentValue(initialValue), valueCallback(valueCallback)
{
    // Set the label in the base class
    this->label = labelText;
}

void SliderMenuItem::execute()
{
    // For sliders, executing them increments the value
    increment();
}

void SliderMenuItem::render(Renderer& renderer)
{
    // Rendering logic - this is handled by the renderer
}

void SliderMenuItem::increment()
{
    int newValue = currentValue + 1; // Use step of 1
    if (newValue <= maxValue)
    {
        currentValue = newValue;
        if (valueCallback)
        {
            valueCallback(currentValue);
        }
    }
}

void SliderMenuItem::decrement()
{
    int newValue = currentValue - 1; // Use step of 1
    if (newValue >= minValue)
    {
        currentValue = newValue;
        if (valueCallback)
        {
            valueCallback(currentValue);
        }
    }
}

} // namespace GreedySnake