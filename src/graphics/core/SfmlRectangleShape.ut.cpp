#include <gtest/gtest.h>

#include "SfmlRectangleShape.hpp"

namespace graphics
{

namespace
{
const Position2f pos{0.7f, 73.0f};
const Size2f size{200, 100};
}

TEST(SfmlRectangleShapeTest, getPosition)
{
    const SfmlRectangleShape rect(size, pos);

    EXPECT_EQ(pos, rect.getPosition());
}

TEST(SfmlRectangleShapeTest, getSize)
{
    const SfmlRectangleShape rect(size, pos);

    EXPECT_EQ(size, rect.getSize());
}

TEST(SfmlRectangleShapeTest, equality)
{
    const SfmlRectangleShape rect_1(Size2f{200, 100}, pos);
    const SfmlRectangleShape rect_2(Size2f{200, 100}, pos);
    const SfmlRectangleShape rect_3(rect_2);

    EXPECT_EQ(rect_1, rect_2);
    EXPECT_EQ(rect_1, rect_3);
}

TEST(SfmlRectangleShapeTest, inequality)
{
    const SfmlRectangleShape rect_1(Size2f{200, 10}, pos);
    const SfmlRectangleShape rect_2(Size2f{20, 100}, pos);

    EXPECT_NE(rect_1, rect_2);
}
}
