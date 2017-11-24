#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <boost/operators.hpp>

#include "Position2f.hpp"
#include "Size2f.hpp"

namespace graphics
{
class SfmlRectangleShape : public sf::RectangleShape
{
public:
    SfmlRectangleShape(const Size2f&, const Position2f&);

    Position2f getPosition() const;
    Size2f getSize() const;

    friend bool operator==(const SfmlRectangleShape& lhs,
                           const SfmlRectangleShape& rhs);

    friend bool operator!=(const SfmlRectangleShape& lhs,
                           const SfmlRectangleShape& rhs);
};
}
