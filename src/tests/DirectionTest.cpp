#include "utils/Direction.h"
#include <gtest/gtest.h>

using namespace GreedySnake;

TEST(DirectionTest, OppositeDirection)
{
    // Test that each direction maps to its opposite
    EXPECT_EQ(getOppositeDirection(Direction::UP), Direction::DOWN);
    EXPECT_EQ(getOppositeDirection(Direction::DOWN), Direction::UP);
    EXPECT_EQ(getOppositeDirection(Direction::LEFT), Direction::RIGHT);
    EXPECT_EQ(getOppositeDirection(Direction::RIGHT), Direction::LEFT);

    // Test that applying getOppositeDirection twice returns the original direction
    EXPECT_EQ(getOppositeDirection(getOppositeDirection(Direction::UP)), Direction::UP);
    EXPECT_EQ(getOppositeDirection(getOppositeDirection(Direction::DOWN)), Direction::DOWN);
    EXPECT_EQ(getOppositeDirection(getOppositeDirection(Direction::LEFT)), Direction::LEFT);
    EXPECT_EQ(getOppositeDirection(getOppositeDirection(Direction::RIGHT)), Direction::RIGHT);
}