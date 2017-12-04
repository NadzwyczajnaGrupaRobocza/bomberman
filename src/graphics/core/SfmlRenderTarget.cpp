#include "SfmlRenderTarget.hpp"

namespace graphics
{
SfmlRenderTarget::SfmlRenderTarget(const WindowSize& size) : window_size{size}
{
}

void SfmlRenderTarget::initialize()
{
    sf::RenderTarget::initialize();
}

void SfmlRenderTarget::clear(const sf::Color& color)
{
    sf::RenderTarget::clear(color);
}

void SfmlRenderTarget::draw(const SfmlRectangleShape& drawable)
{
    sf::RenderTarget::draw(drawable);
}

sf::Vector2u SfmlRenderTarget::getSize() const
{
    return window_size;
}

bool SfmlRenderTarget::activate(const bool)
{
    return true;
}
}
