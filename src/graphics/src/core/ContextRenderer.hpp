#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "SfmlRectangleShape.hpp"

namespace graphics
{
class ContextRenderer
{
public:
    virtual ~ContextRenderer() noexcept = default;

    virtual void initialize() = 0;
    virtual void clear(const sf::Color& color) = 0;
    virtual void draw(const SfmlRectangleShape&) = 0;
};
}
