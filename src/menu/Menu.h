#ifndef GREEDYSNAKE_MENU_H
#define GREEDYSNAKE_MENU_H

#include "menu/Input.h"
#include "menu/MenuItem.h"
#include "menu/SliderMenuItem.h"
#include "renderer/Renderer.h"
#include <memory>
#include <string>
#include <vector>

namespace GreedySnake
{

/**
 * @brief Class to manage a collection of menu items
 */
class Menu
{
  public:
    /**
     * @brief Constructor
     */
    Menu();

    /**
     * @brief Destructor
     */
    virtual ~Menu() = default;

    /**
     * @brief Add a menu item of the specified type
     * @tparam T Type of menu item to add
     * @tparam Args Parameter types for the constructor
     * @param args Constructor arguments for the menu item
     * @return Pointer to the created menu item
     */
    template <typename T, typename... Args> std::shared_ptr<T> addItem(Args&&... args)
    {
        auto item = std::make_shared<T>(std::forward<Args>(args)...);
        items.push_back(item);

        // If this is the first selectable item, select it
        if (items.size() == 1 && item->isSelectable())
        {
            item->select();
        }

        return item;
    }

    /**
     * @brief Clear all items from the menu
     */
    void clearItems();

    /**
     * @brief Handle user input
     * @param input The input enum value
     * @return True if the input was handled
     */
    bool handleInput(Input input);

    /**
     * @brief Render the menu
     * @param renderer The renderer to use
     * @param title The title to display
     */
    void render(Renderer& renderer, const std::string& title) const;

    /**
     * @brief Select the next item in the menu
     */
    void selectNext();

    /**
     * @brief Select the previous item in the menu
     */
    void selectPrevious();

    /**
     * @brief Execute the currently selected item
     */
    void executeSelected() const;

    /**
     * @brief Get the currently selected item
     * @return Shared pointer to the selected item
     */
    [[nodiscard]] std::shared_ptr<MenuItem> getSelectedItem() const;

    /**
     * @brief Get the number of items in the menu
     * @return Number of items
     */
    [[nodiscard]] size_t getItemCount() const;

    /**
     * @brief Get the index of the selected item
     * @return Selected index
     */
    [[nodiscard]] size_t getSelectedIndex() const;

    /**
     * @brief Get a list of menu item texts
     * @return Vector of strings containing menu item texts
     */
    [[nodiscard]] std::vector<std::string> getMenuItems() const;

    /**
     * @brief Set instructions for using the menu
     * @param instructionsText The instructions text
     */
    void setInstructions(const std::string& instructionsText);

    /**
     * @brief Get the instructions for using the menu
     * @return Instructions text
     */
    const std::string& getInstructions() const;

  private:
    std::vector<std::shared_ptr<MenuItem>> items;
    size_t selectedIndex;
    std::string instructions;
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_MENU_H