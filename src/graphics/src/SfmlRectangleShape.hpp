#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <boost/operators.hpp>

#include "math/sfml/Position2f.hpp"
#include "math/sfml/Size2f.hpp"

namespace graphics
{
class SfmlRectangleShape : public sf::RectangleShape
{
public:
    SfmlRectangleShape(math::sf::Size2f, math::sf::Position2f);

    const math::sf::Position2f getPosition() const;
    const math::sf::Size2f getSize() const;

    friend bool operator==(const SfmlRectangleShape& lhs,
                           const SfmlRectangleShape& rhs);

    friend bool operator!=(const SfmlRectangleShape& lhs,
                           const SfmlRectangleShape& rhs);
};
}
