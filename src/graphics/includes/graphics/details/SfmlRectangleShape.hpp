#pragma once

#include "SFML/Graphics/RectangleShape.hpp"

#include <iostream>

namespace graphics
{
class SfmlRectangleShape : public sf::RectangleShape
{
public:
    using sf::RectangleShape::RectangleShape;

    friend bool operator==(const SfmlRectangleShape& lhs,
                           const SfmlRectangleShape& rhs);

    friend bool operator!=(const SfmlRectangleShape& lhs,
                           const SfmlRectangleShape& rhs);
    friend bool operator<(const SfmlRectangleShape& lhs,
                          const SfmlRectangleShape& rhs);
};
}
