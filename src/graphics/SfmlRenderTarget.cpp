#include "SfmlRenderTarget.hpp"

namespace graphics
{
SfmlRenderTarget::SfmlRenderTarget(const sf::Vector2u size) : window_size{size}
{
    RenderTarget::initialize();
}

void SfmlRenderTarget::setSize(const sf::Vector2u new_size)
{
    window_size = new_size;
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
