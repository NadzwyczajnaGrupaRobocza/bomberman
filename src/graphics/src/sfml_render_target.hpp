#pragma once

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

#include "window_size.hpp"
#include "context_renderer.hpp"

namespace graphics
{
template <typename BaseRenderTarget>
class render_target : public context_renderer, public BaseRenderTarget
{
public:
    render_target(const window_size& s) : size{s}
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

    void draw(const sfml_rectangle_shape& drawable) override
    {
        BaseRenderTarget::draw(drawable);
    }

    sf::Vector2u getSize() const override
    {
        return size;
    }

    bool setActive([[maybe_unused]] bool active) override
    {
        return true;
    }

protected:
    window_size size;
};

using sfml_render_target = render_target<sf::RenderTarget>;
} // namespace graphics
