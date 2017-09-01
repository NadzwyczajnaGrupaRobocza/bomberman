#include <gtest/gtest.h>

#include "SfmlRectangleShape.hpp"

namespace graphics
{
TEST(SfmlRectangleShapeTest, equality)
{
    SfmlRectangleShape rect_1(sf::Vector2f{200, 100});
    SfmlRectangleShape rect_2(sf::Vector2f{200, 100});
    SfmlRectangleShape rect_3(rect_2);

    EXPECT_EQ(rect_1, rect_2);
    EXPECT_EQ(rect_1, rect_3);
}

TEST(SfmlRectangleShapeTest, inequality)
{
    SfmlRectangleShape rect_1(sf::Vector2f{200, 10});
    SfmlRectangleShape rect_2(sf::Vector2f{20, 100});

    EXPECT_NE(rect_1, rect_2);
}
}
