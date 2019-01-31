#include "sfml_rectangle_shape.hpp"

#include <tuple>

namespace graphics
{

sfml_rectangle_shape::sfml_rectangle_shape(const size2f& size,
                                           const position2f& position)
{
    setSize(size);
    setPosition(position);
}

position2f sfml_rectangle_shape::getPosition() const
{
    return sf::RectangleShape::getPosition();
}

size2f sfml_rectangle_shape::getSize() const
{
    return sf::RectangleShape::getSize();
}
} // namespace graphics
