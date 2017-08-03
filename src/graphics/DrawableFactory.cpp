#include "DrawableFactory.hpp"

namespace graphics
{
std::unique_ptr<SfmlRectangleShape>
DrawableFactory::create_rectangle(const sf::Vector2f size) const
{
    return std::make_unique<SfmlRectangleShape>(size);
}
}
