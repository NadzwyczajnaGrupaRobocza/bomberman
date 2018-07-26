#pragma once

#include <memory>

#include <SFML/Graphics/render_target.hpp>

#include "window_size.hpp"
#include "context_renderer.hpp"

namespace graphics
{
template <typename BaseRenderTarget>
class render_target : public context_renderer, public BaseRenderTarget
{
public:
    render_target(const window_size& size) : window_size{size}
    {
    }

    void initialize() override
    {
        BaseRenderTarget::initialize();
    }

    void clear(const sf::Color& color) override
    {
        BaseRenderTarget::clear(color);
    }

    void draw(const SfmlRectangleShape& drawable) override
    {
        BaseRenderTarget::draw(drawable);
    }

    sf::Vector2u getSize() const override
    {
        return window_size;
    }
    bool activate([[maybe_unused]] bool active) override
    {
        return true;
    }

protected:
    window_size window_size;
};

using sfml_render_target = render_target<sf::render_target>;
}
