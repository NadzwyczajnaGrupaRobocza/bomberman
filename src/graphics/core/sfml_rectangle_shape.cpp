#include "sfml_rectangle_shape.hpp"

#include <tuple>

namespace graphics
{

sfml_rectangle_shape::sfml_rectangle_shape(renderer_id shape_id,
                                           const size2f& size,
                                           const position2f& position,
                                           const color& c)
    : id{std::move(shape_id)}
{
    setSize(size);
    setPosition(position);
    set_color(c);
}

position2f sfml_rectangle_shape::getPosition() const
{
    return sf::RectangleShape::getPosition();
}

size2f sfml_rectangle_shape::getSize() const
{
    return sf::RectangleShape::getSize();
}

void sfml_rectangle_shape::set_color(const color& new_color)
{
    sf::RectangleShape::setFillColor(
        sf::Color{new_color.r, new_color.g, new_color.b});
}

color sfml_rectangle_shape::get_color() const
{
    const auto& current_color{sf::RectangleShape::getFillColor()};
    return color{current_color.r, current_color.g, current_color.b};
}

renderer_id sfml_rectangle_shape::get_id() const
{
    return id;
}
} // namespace graphics
