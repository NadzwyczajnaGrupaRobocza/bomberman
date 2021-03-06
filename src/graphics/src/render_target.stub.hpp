#pragma once

#include <gtest/gtest.h>

#include "renderer_id_generator.hpp"
#include "sfml_rectangle_shape.hpp"

namespace graphics
{
namespace
{
const position2f pos{0, 0};
const size2f size{0, 0};
const color default_color{0, 0, 0};
const auto shape_id = renderer_id_generator{}.generate();
}

class render_target_stub
{
public:
    virtual ~render_target_stub()
    {
        EXPECT_EQ(shouldInitialize, initialized);
        EXPECT_EQ(shouldClear, cleared);
        if (shouldClear)
        {
            EXPECT_EQ(expectedColor, clearedColor);
        }
        EXPECT_EQ(shouldDraw, drawn);
        if (shouldDraw)
        {
            EXPECT_EQ(expectedShape, drawnShape);
        }
    }
    void initialize()
    {
        initialized = true;
    }

    void clear(const sf::Color& color)
    {
        cleared = true;
        clearedColor = color;
    }

    void draw(const sfml_rectangle_shape& shape)
    {
        drawn = true;
        drawnShape = shape;
    }

    void setView(const sf::View&)
    {
    }

    void set_view_size(const window_size&)
    {
    }

    sf::View getDefaultView()
    {
        return sf::View{};
    }

    virtual sf::Vector2u getSize() const = 0;
    virtual bool setActive(bool) = 0;

    void expectClear(const sf::Color& color)
    {
        shouldClear = true;
        expectedColor = color;
    }

    void expectDraw(const sfml_rectangle_shape& shape)
    {
        shouldDraw = true;
        expectedShape = shape;
    }

    bool initialized{false};
    bool cleared{false};
    sf::Color clearedColor{sf::Color::Transparent};
    bool drawn{false};
    sfml_rectangle_shape drawnShape{shape_id, size, pos, default_color};

    bool shouldInitialize{false};
    bool shouldClear{false};
    bool shouldDraw{false};

    sf::Color expectedColor{sf::Color::Transparent};

    sfml_rectangle_shape expectedShape{shape_id, size, pos, default_color};
};
}
