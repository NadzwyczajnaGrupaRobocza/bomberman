#pragma once

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

#include "WindowSize.hpp"
#include "ContextRenderer.hpp"

namespace graphics
{
template <typename BaseRenderTarget>
class RenderTarget : public ContextRenderer, public BaseRenderTarget
{
public:
    RenderTarget(const WindowSize& size) : window_size{size}
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
    bool setActive([[maybe_unused]] bool active) override
    {
        return true;
    }

protected:
    WindowSize window_size;
};

using SfmlRenderTarget = RenderTarget<sf::RenderTarget>;
}
