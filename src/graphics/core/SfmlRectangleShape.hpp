#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <boost/operators.hpp>

#include "Position2f.hpp"
#include "Size2f.hpp"

namespace graphics
{
class SfmlRectangleShape : public sf::RectangleShape,
                           public boost::equality_comparable<SfmlRectangleShape>
{
public:
    SfmlRectangleShape(const Size2f&, const Position2f&);

    Position2f getPosition() const;
    Size2f getSize() const;
};

inline bool operator==(const SfmlRectangleShape& lhs,
                       const SfmlRectangleShape& rhs)
{
    return lhs.getPosition() == rhs.getPosition() &&
           lhs.getSize() == rhs.getSize();
}
}
