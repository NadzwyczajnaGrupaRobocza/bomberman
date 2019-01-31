#include <gtest/gtest.h>

#include "sfml_rectangle_shape.hpp"

namespace graphics
{

namespace
{
const position2f pos{0.7f, 73.0f};
const size2f size{200, 100};
} // namespace

TEST(sfml_rectangle_shape_test, getPosition)
{
    const sfml_rectangle_shape rect(size, pos);

    EXPECT_EQ(pos, rect.getPosition());
}

TEST(sfml_rectangle_shape_test, getSize)
{
    const sfml_rectangle_shape rect(size, pos);

    EXPECT_EQ(size, rect.getSize());
}

TEST(sfml_rectangle_shape_test, equality)
{
    const sfml_rectangle_shape rect_1(size2f{200, 100}, pos);
    const sfml_rectangle_shape rect_2(size2f{200, 100}, pos);
    const sfml_rectangle_shape rect_3(rect_2);

    EXPECT_EQ(rect_1, rect_2);
    EXPECT_EQ(rect_1, rect_3);
}

TEST(sfml_rectangle_shape_test, inequality)
{
    const sfml_rectangle_shape rect_1(size2f{200, 10}, pos);
    const sfml_rectangle_shape rect_2(size2f{20, 100}, pos);

    EXPECT_NE(rect_1, rect_2);
}
} // namespace graphics
