#include <gtest/gtest.h>

#include "SfmlRectangleShape.hpp"

namespace graphics
{
const Position2f pos{0.0f, 0.0f};

TEST(SfmlRectangleShapeTest, equality)
{
    SfmlRectangleShape rect_1(Size2f{200, 100}, pos);
    SfmlRectangleShape rect_2(Size2f{200, 100}, pos);
    SfmlRectangleShape rect_3(rect_2);

    EXPECT_EQ(rect_1, rect_2);
    EXPECT_EQ(rect_1, rect_3);
}

TEST(SfmlRectangleShapeTest, inequality)
{
    SfmlRectangleShape rect_1(Size2f{200, 10}, pos);
    SfmlRectangleShape rect_2(Size2f{20, 100}, pos);

    EXPECT_NE(rect_1, rect_2);
}
}
