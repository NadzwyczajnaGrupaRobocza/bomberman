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

bool operator==(const SfmlRectangleShape& lhs, const SfmlRectangleShape& rhs)
{
    return lhs.getPosition() == rhs.getPosition() &&
           lhs.getSize() == rhs.getSize();
}

bool operator!=(const SfmlRectangleShape& lhs, const SfmlRectangleShape& rhs)
{
    return not(lhs == rhs);
}
}
