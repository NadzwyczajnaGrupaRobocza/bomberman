#include "SfmlRectangleShape.hpp"

#include <tuple>

namespace graphics
{

bool operator==(const SfmlRectangleShape& lhs, const SfmlRectangleShape& rhs)
{
    return std::tie(lhs.getPosition().x, lhs.getPosition().y, lhs.getSize().x,
                    lhs.getSize().y) ==
           std::tie(rhs.getPosition().x, rhs.getPosition().y, rhs.getSize().x,
                    rhs.getSize().y);
}

bool operator!=(const SfmlRectangleShape& lhs, const SfmlRectangleShape& rhs)
{
    return not(lhs == rhs);
}

bool operator<(const SfmlRectangleShape& lhs, const SfmlRectangleShape& rhs)
{
    return std::tie(lhs.getPosition().x, lhs.getPosition().y, lhs.getSize().x,
                    lhs.getSize().y) <
           std::tie(rhs.getPosition().x, rhs.getPosition().y, rhs.getSize().x,
                    rhs.getSize().y);
}
}
