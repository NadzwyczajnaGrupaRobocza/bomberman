#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <boost/operators.hpp>

#include "graphics/color.hpp"
#include "graphics/renderer_id.hpp"
#include "position2f.hpp"
#include "size2f.hpp"

namespace graphics
{
class sfml_rectangle_shape
    : public sf::RectangleShape,
      public boost::equality_comparable<sfml_rectangle_shape>
{
public:
    sfml_rectangle_shape(renderer_id, const size2f&, const position2f&,
                         const color&);

    position2f getPosition() const;
    size2f getSize() const;

    void set_color(const color&);
    color get_color() const;

    renderer_id get_id() const;

private:
    renderer_id id;
};

inline bool operator==(const sfml_rectangle_shape& lhs,
                       const sfml_rectangle_shape& rhs)
{
    return lhs.getPosition() == rhs.getPosition() &&
           lhs.getSize() == rhs.getSize() && lhs.get_color() == rhs.get_color();
}
}
