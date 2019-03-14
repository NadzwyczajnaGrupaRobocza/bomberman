#include "sfml_renderer_pool.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <range/v3/algorithm/for_each.hpp>

#include <boost/uuid/uuid_io.hpp>

namespace graphics
{

sfml_renderer_pool::sfml_renderer_pool(std::unique_ptr<context_renderer> r)
    : renderer{std::move(r)}
{
    renderer->initialize();
}

renderer_id sfml_renderer_pool::acquire(const math::Size2f& size,
                                        const math::Position2f& position,
                                        const color& shape_color)
{
    auto id = renderer_id_generator::generate();
    shapes.emplace(std::piecewise_construct, std::forward_as_tuple(id),
                   std::forward_as_tuple(size, position, shape_color));
    return id;
}

void sfml_renderer_pool::release(const renderer_id& id)
{
    trash.emplace(id);
}

void sfml_renderer_pool::cleanup_unused()
{
    ranges::for_each(trash, [this](const auto& id) { shapes.erase(id); });
    trash.clear();
}

void sfml_renderer_pool::render_all()
{
    cleanup_unused();
    renderer->clear(sf::Color::Black);

    ranges::for_each(shapes,
                     [&](const auto& shape) { renderer->draw(shape.second); });
}

void sfml_renderer_pool::set_position(const renderer_id& id,
                                      const math::Position2f& position)
{
    shapes.at(id).setPosition({position.x, position.y});
}

math::Position2f sfml_renderer_pool::get_position(const renderer_id& id)
{
    return shapes.at(id).getPosition();
}

void sfml_renderer_pool::set_color(const renderer_id& id,
                                   const color& new_color)
{
    shapes.at(id).set_color(new_color);
}

color sfml_renderer_pool::get_color(const renderer_id& id) const
{
    return shapes.at(id).get_color();
}
}
