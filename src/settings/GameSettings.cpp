#include "settings/GameSettings.h"
#include <fstream>
#include <iostream>

namespace GreedySnake
{

GameSettings::GameSettings()
    : gameSpeed(5),      // Medium speed by default
      boardWidth(20),    // Default board width
      boardHeight(20),   // Default board height
      borders(true),     // Border collisions enabled by default
      soundEnabled(true) // Sound enabled by default
{
}

int GameSettings::getGameSpeed() const
{
    return gameSpeed;
}

void GameSettings::setGameSpeed(int speed)
{
    gameSpeed = clamp(speed, 1, 10); // Clamp to 1-10 range
}

int GameSettings::getBoardWidth() const
{
    return boardWidth;
}

void GameSettings::setBoardWidth(int width)
{
    boardWidth = clamp(width, 10, 100); // Minimum size 10, maximum reasonable size 100
}

int GameSettings::getBoardHeight() const
{
    return boardHeight;
}

void GameSettings::setBoardHeight(int height)
{
    boardHeight = clamp(height, 10, 100); // Minimum size 10, maximum reasonable size 100
}

bool GameSettings::hasBorders() const
{
    return borders;
}

void GameSettings::setBorders(bool enabled)
{
    borders = enabled;
}

bool GameSettings::isSoundEnabled() const
{
    return soundEnabled;
}

void GameSettings::setSoundEnabled(bool enabled)
{
    soundEnabled = enabled;
}

bool GameSettings::saveToFile(const std::string& filename)
{
    try
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            return false;
        }

        // Write settings to file in a simple key=value format
        file << "gameSpeed=" << gameSpeed << '\n';
        file << "boardWidth=" << boardWidth << '\n';
        file << "boardHeight=" << boardHeight << '\n';
        file << "borders=" << (borders ? "true" : "false") << '\n';
        file << "soundEnabled=" << (soundEnabled ? "true" : "false") << '\n';

        file.close();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error saving settings: " << e.what() << '\n';
        return false;
    }
}

bool GameSettings::loadFromFile(const std::string& filename)
{
    try
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            return false;
        }

        std::string line;
        while (std::getline(file, line))
        {
            // Parse each line as key=value
            auto pos = line.find('=');
            if (pos == std::string::npos)
            {
                continue; // Skip invalid lines
            }

            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // Apply the setting based on the key
            if (key == "gameSpeed")
            {
                try
                {
                    setGameSpeed(std::stoi(value));
                }
                catch (...)
                {
                    // Ignore conversion errors
                }
            }
            else if (key == "boardWidth")
            {
                try
                {
                    setBoardWidth(std::stoi(value));
                }
                catch (...)
                {
                    // Ignore conversion errors
                }
            }
            else if (key == "boardHeight")
            {
                try
                {
                    setBoardHeight(std::stoi(value));
                }
                catch (...)
                {
                    // Ignore conversion errors
                }
            }
            else if (key == "borders")
            {
                setBorders(value == "true");
            }
            else if (key == "soundEnabled")
            {
                setSoundEnabled(value == "true");
            }
        }

        file.close();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading settings: " << e.what() << '\n';
        return false;
    }
}

int GameSettings::clamp(int value, int min, int max) const
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    return value;
}

} // namespace GreedySnake