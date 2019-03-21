#include "renderer_pool_sfml.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <range/v3/algorithm/for_each.hpp>

#include <boost/uuid/uuid_io.hpp>

namespace graphics
{

renderer_pool_sfml::renderer_pool_sfml(std::unique_ptr<context_renderer> r,
                                       std::unique_ptr<renderer_id_generator> g)
    : renderer{std::move(r)}, id_generator{std::move(g)}
{
    renderer->initialize();
}

renderer_id renderer_pool_sfml::acquire(const math::Size2f& size,
                                        const math::Position2f& position,
                                        const color& shape_color)
{
    auto id = id_generator->generate();
    shapes.emplace(std::piecewise_construct, std::forward_as_tuple(id),
                   std::forward_as_tuple(size, position, shape_color));
    return id;
}

void renderer_pool_sfml::release(const renderer_id& id)
{
    trash.emplace(id);
}

void renderer_pool_sfml::cleanup_unused()
{
    ranges::for_each(trash, [this](const auto& id) { shapes.erase(id); });
    trash.clear();
}

void renderer_pool_sfml::render_all()
{
    cleanup_unused();
    renderer->clear(sf::Color::Black);

    ranges::for_each(shapes,
                     [&](const auto& shape) { renderer->draw(shape.second); });
}

void renderer_pool_sfml::set_position(const renderer_id& id,
                                      const math::Position2f& position)
{
    shapes.at(id).setPosition({position.x, position.y});
}

math::Position2f renderer_pool_sfml::get_position(const renderer_id& id)
{
    return shapes.at(id).getPosition();
}
void renderer_pool_sfml::set_color(const renderer_id& id,
                                   const color& new_color)
{
    shapes.at(id).set_color(new_color);
}

color renderer_pool_sfml::get_color(const renderer_id& id) const
{
    return shapes.at(id).get_color();
}
}
