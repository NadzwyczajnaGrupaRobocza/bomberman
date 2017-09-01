#include "RenderTarget.hpp"

namespace graphics
{
RenderTarget::RenderTarget(const sf::Vector2u size) : window_size{size}
{
}

void RenderTarget::initialize()
{
    sf::RenderTarget::initialize();
}

void RenderTarget::clear(const sf::Color color)
{
    sf::RenderTarget::clear(color);
}

void RenderTarget::draw(const SfmlRectangleShape& drawable)
{
    sf::RenderTarget::draw(drawable);
}

void RenderTarget::setSize(const sf::Vector2u new_size)
{
    window_size = new_size;
}

sf::Vector2u RenderTarget::getSize() const
{
    return window_size;
}

bool RenderTarget::activate(const bool)
{
    return true;
}
}
