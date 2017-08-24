#pragma once

#include "math/Size.hpp"
#include "SFML/System/Vector2.hpp"

namespace graphics
{
namespace utils
{
math::Size to_math(const sf::Vector2f& size);
sf::Vector2u to_sfml_u(const math::Size& size);
}
}
