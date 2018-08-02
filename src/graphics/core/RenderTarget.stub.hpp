#pragma once

#include <gtest/gtest.h>

#include "SfmlRectangleShape.hpp"

namespace graphics
{
namespace
{
const Position2f pos{0, 0};
const Size2f size{0, 0};
}

class RenderTargetStub
{
public:
    virtual ~RenderTargetStub()
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

    void draw(const SfmlRectangleShape& shape)
    {
        drawn = true;
        drawnShape = shape;
    }

    virtual sf::Vector2u getSize() const = 0;
    virtual bool setActive(bool) = 0;

    void expectClear(const sf::Color& color)
    {
        shouldClear = true;
        expectedColor = color;
    }

    void expectDraw(const SfmlRectangleShape& shape)
    {
        shouldDraw = true;
        expectedShape = shape;
    }

    bool initialized{false};
    bool cleared{false};
    sf::Color clearedColor{sf::Color::Transparent};
    bool drawn{false};
    SfmlRectangleShape drawnShape{size, pos};

    bool shouldInitialize{false};
    bool shouldClear{false};
    bool shouldDraw{false};

    sf::Color expectedColor{sf::Color::Transparent};
    SfmlRectangleShape expectedShape{size, pos};
};
}
