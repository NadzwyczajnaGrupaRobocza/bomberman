#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "graphics/window_size.hpp"
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
    virtual void set_view() = 0;
    virtual void set_view_size(const window_size&) = 0;
};
}
