#include "Conversion.hpp"

namespace graphics
{
namespace utils
{
math::Size to_math(const sf::Vector2f& size)
{
    return math::Size{size.x, size.y};
}

sf::Vector2u to_sfml_u(const math::Size& size)
{
    return sf::Vector2u{static_cast<unsigned>(size.width),
                        static_cast<unsigned>(size.height)};
}
}
}
