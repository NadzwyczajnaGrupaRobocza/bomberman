#include "SfmlRectangleShape.hpp"

#include <tuple>

namespace graphics
{

SfmlRectangleShape::SfmlRectangleShape(const Size2f& size,
                                       const Position2f& position)
{
    setSize(size);
    setPosition(position);
}

Position2f SfmlRectangleShape::getPosition() const
{
    return sf::RectangleShape::getPosition();
}

Size2f SfmlRectangleShape::getSize() const
{
    return sf::RectangleShape::getSize();
}
}
