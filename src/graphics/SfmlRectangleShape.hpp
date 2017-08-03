#pragma once

#include "SFML/Graphics/RectangleShape.hpp"

namespace graphics
{
class SfmlRectangleShape : public sf::RectangleShape
{
public:
    using sf::RectangleShape::RectangleShape;
};
}
