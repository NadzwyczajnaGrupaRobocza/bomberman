#pragma once

#include <memory>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "sfml_rectangle_shape.hpp"

namespace graphics
{
class context_renderer
{
public:
    virtual ~context_renderer() noexcept = default;

    virtual void initialize() = 0;
    virtual void clear(const sf::Color&) = 0;
    virtual void draw(const sfml_rectangle_shape&) = 0;
};
}
