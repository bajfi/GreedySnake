# Greedy Snake

A modern C++ implementation of the classic Snake game using SFML for graphical rendering.

## Features

- Modern C++ 17 implementation
- SFML graphics for rendering
- Multiple game states and menus
- Configurable settings
- Unit testing with Google Test

## Build Requirements

- CMake 3.14 or higher
- SFML 2.5 or higher
- C++17 compatible compiler

## Building the Project

```bash
# Clone the repository
git clone https://github.com/bajfi/GreedySnake.git

cd GreedySnake

# Create a build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run the game
./GreedySnake

# Run tests
./run_tests
```

## Controls

- Arrow keys or WASD to move
- P to pause/resume
- Escape to go back or exit

## Project Structure

- `src/game`: Core game logic
- `src/menu`: Menu system and game states
- `src/renderer`: Rendering interface and implementations
- `src/settings`: Game settings management
- `src/tests`: Unit tests

## License

This project is licensed under the MIT License - see the LICENSE file for details.
