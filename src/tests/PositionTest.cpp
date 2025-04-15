#include "utils/Position.h"
#include <gtest/gtest.h>

using namespace GreedySnake;

// Test fixture for Position tests
class PositionTest : public ::testing::Test
{
  protected:
    // Test positions
    Position origin{0, 0};
    Position pos1{5, 10};
    Position pos2{-3, 7};
};

// Test constructor and member access
TEST_F(PositionTest, Constructor)
{
    Position pos(3, 4);
    EXPECT_EQ(pos.x, 3);
    EXPECT_EQ(pos.y, 4);

    // Default constructor
    Position defaultPos;
    EXPECT_EQ(defaultPos.x, 0);
    EXPECT_EQ(defaultPos.y, 0);
}

// Test equality operator
TEST_F(PositionTest, EqualityOperator)
{
    Position pos1(5, 10);
    Position pos2(5, 10);
    Position pos3(6, 10);

    EXPECT_TRUE(pos1 == pos2);
    EXPECT_FALSE(pos1 == pos3);
    EXPECT_FALSE(pos2 == pos3);
}

// Test inequality operator
TEST_F(PositionTest, InequalityOperator)
{
    Position pos1(5, 10);
    Position pos2(5, 10);
    Position pos3(6, 10);

    EXPECT_FALSE(pos1 != pos2);
    EXPECT_TRUE(pos1 != pos3);
    EXPECT_TRUE(pos2 != pos3);
}

// Test addition operator
TEST_F(PositionTest, AdditionOperator)
{
    Position pos1(5, 10);
    Position pos2(3, -4);

    Position result = pos1 + pos2;
    EXPECT_EQ(result.x, 8);
    EXPECT_EQ(result.y, 6);
}