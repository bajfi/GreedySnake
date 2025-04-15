#ifndef GREEDYSNAKE_GAMESETTINGS_H
#define GREEDYSNAKE_GAMESETTINGS_H

#include <string>

namespace GreedySnake
{

/**
 * @brief Manages game settings and configuration
 *
 * This class handles all configurable settings for the game,
 * including game speed, board dimensions, and other options.
 * It also handles saving/loading these settings to/from a file.
 */
class GameSettings
{
  public:
    /**
     * @brief Constructor with default settings
     */
    GameSettings();

    /**
     * @brief Get the current game speed (1-10 scale)
     * @return The game speed value
     */
    int getGameSpeed() const;

    /**
     * @brief Set the game speed
     * @param speed The new speed value (1-10, will be clamped to this range)
     */
    void setGameSpeed(int speed);

    /**
     * @brief Get the width of the game board
     * @return The board width
     */
    int getBoardWidth() const;

    /**
     * @brief Set the width of the game board
     * @param width The new board width (min 10, will be clamped)
     */
    void setBoardWidth(int width);

    /**
     * @brief Get the height of the game board
     * @return The board height
     */
    int getBoardHeight() const;

    /**
     * @brief Set the height of the game board
     * @param height The new board height (min 10, will be clamped)
     */
    void setBoardHeight(int height);

    /**
     * @brief Check if border collisions are enabled
     * @return True if borders are enabled, false otherwise
     */
    bool hasBorders() const;

    /**
     * @brief Enable or disable border collisions
     * @param enabled True to enable borders, false to disable them
     */
    void setBorders(bool enabled);

    /**
     * @brief Check if sound is enabled
     * @return True if sound is enabled, false otherwise
     */
    bool isSoundEnabled() const;

    /**
     * @brief Enable or disable sound
     * @param enabled True to enable sound, false to disable it
     */
    void setSoundEnabled(bool enabled);

    /**
     * @brief Save settings to a file
     * @param filename The file to save settings to
     * @return True if successful, false otherwise
     */
    bool saveToFile(const std::string& filename = "settings.ini") const;

    /**
     * @brief Load settings from a file
     * @param filename The file to load settings from
     * @return True if successful, false otherwise
     */
    bool loadFromFile(const std::string& filename = "settings.ini");

  private:
    int gameSpeed;     // Game speed (1-10)
    int boardWidth;    // Board width
    int boardHeight;   // Board height
    bool borders;      // Border collisions enabled
    bool soundEnabled; // Sound enabled

    /**
     * @brief Clamp a value to a specified range
     * @param value The value to clamp
     * @param min The minimum allowed value
     * @param max The maximum allowed value
     * @return The clamped value
     */
    int clamp(int value, int min, int max) const;
};

} // namespace GreedySnake

#endif // GREEDYSNAKE_GAMESETTINGS_H