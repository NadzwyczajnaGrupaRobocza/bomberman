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
                           const SfmlRectangleShape& rhs)
    {
        std::clog << "test " << __FUNCTION__ << "lhs:" << lhs.getSize().x << ","
                  << lhs.getSize().y << " rhs:" << rhs.getSize().x << ","
                  << rhs.getSize().y << "\n";
        return lhs.getSize() == rhs.getSize();
    }

    friend bool operator!=(const SfmlRectangleShape& lhs,
                           const SfmlRectangleShape& rhs)
    {
        return not(lhs == rhs);
    }

    friend bool operator<(const SfmlRectangleShape& lhs,
                          const SfmlRectangleShape& rhs)
    {
        return lhs.getPosition().x < rhs.getPosition().x &&
               lhs.getPosition().y < rhs.getPosition().y &&
               lhs.getSize().x < rhs.getSize().x &&
               lhs.getSize().y < rhs.getSize().y;
    }
};
}
