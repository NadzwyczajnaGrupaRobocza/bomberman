#include <gtest/gtest.h>

#include "sfml_rectangle_shape.hpp"
#include "renderer_id_generator.hpp"

namespace graphics
{
namespace
{
const position2f pos{0.7f, 73.0f};
const size2f size{200, 100};
const color default_color{80, 75, 26};
const auto shape_id = renderer_id_generator{}.generate();

} // namespace

TEST(sfml_rectangle_shape_test, getRendererId)
{
    const sfml_rectangle_shape rect(shape_id, size, pos, default_color);

    EXPECT_EQ(shape_id, rect.get_id());
}

TEST(sfml_rectangle_shape_test, getPosition)
{
    const sfml_rectangle_shape rect(shape_id, size, pos, default_color);

    EXPECT_EQ(pos, rect.getPosition());
}

TEST(sfml_rectangle_shape_test, getSize)
{
    const sfml_rectangle_shape rect(shape_id, size, pos, default_color);

    EXPECT_EQ(size, rect.getSize());
}

TEST(sfml_rectangle_shape_test, getColorDefinedInConstructor)
{
    const sfml_rectangle_shape rect(shape_id, size, pos, default_color);

    EXPECT_EQ(default_color, rect.get_color());
}

TEST(sfml_rectangle_shape_test, colorShouldBeChangeable)
{
    sfml_rectangle_shape rect(shape_id, size, pos, default_color);

    const color new_color{255, 56, 1};
    ASSERT_NE(new_color, default_color);

    rect.set_color(new_color);
    EXPECT_EQ(new_color, rect.get_color());
}

TEST(sfml_rectangle_shape_test, equality)
{
    const sfml_rectangle_shape rect_1(shape_id, size2f{200, 100}, pos,
                                      default_color);
    const sfml_rectangle_shape rect_2(shape_id, size2f{200, 100}, pos,
                                      default_color);
    const sfml_rectangle_shape rect_3(rect_2);

    EXPECT_EQ(rect_1, rect_2);
    EXPECT_EQ(rect_1, rect_3);
}

TEST(sfml_rectangle_shape_test, sizeInequality)
{
    const sfml_rectangle_shape rect_1(shape_id, size2f{200, 10}, pos,
                                      default_color);
    const sfml_rectangle_shape rect_2(shape_id, size2f{20, 100}, pos,
                                      default_color);

    EXPECT_NE(rect_1, rect_2);
}

TEST(sfml_rectangle_shape_test, positionInequality)
{
    const sfml_rectangle_shape rect_1(shape_id, size, position2f{10.f, 20.f},
                                      default_color);
    const sfml_rectangle_shape rect_2(shape_id, size, position2f{0.f, 20.f},
                                      default_color);

    EXPECT_NE(rect_1, rect_2);
}

TEST(sfml_rectangle_shape_test, colorInequality)
{
    const sfml_rectangle_shape rect_1(shape_id, size, pos, color{0, 0, 0});
    const sfml_rectangle_shape rect_2(shape_id, size, pos,
                                      color{255, 255, 255});

    EXPECT_NE(rect_1, rect_2);
}
} // namespace graphics
