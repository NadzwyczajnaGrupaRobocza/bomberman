#include "renderer_pool_sfml.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cassert>
#include <range/v3/algorithm/for_each.hpp>

#include "boost/range/algorithm_ext/erase.hpp"
#include <boost/uuid/uuid_io.hpp>

namespace graphics
{
namespace
{
struct is_shape_id_equal
{
    bool operator()(const sfml_rectangle_shape& shape)
    {
        return shape.get_id() == id;
    }

    const renderer_id id;
};
}

renderer_pool_sfml::renderer_pool_sfml(std::unique_ptr<context_renderer> r,
                                       std::unique_ptr<renderer_id_generator> g)
    : renderer{std::move(r)}, id_generator{std::move(g)}
{
    renderer->initialize();
    renderer->set_view();
}

renderer_id renderer_pool_sfml::acquire(const math::Size2f& size,
                                        const math::Position2f& position,
                                        const color& shape_color)
{
    auto id = id_generator->generate();
    shapes.emplace_back(id, size, position, shape_color);
    return id;
}

void renderer_pool_sfml::release(const renderer_id& id)
{
    trash.emplace(id);
}

void renderer_pool_sfml::cleanup_unused()
{
    boost::remove_erase_if(
        shapes, [this](auto& shape) { return trash.count(shape.get_id()); });

    trash.clear();
}

void renderer_pool_sfml::render_all()
{
    cleanup_unused();
    renderer->clear(sf::Color::Black);

    renderer->set_view();

    ranges::for_each(shapes, [&](const auto& shape) { renderer->draw(shape); });
}

void renderer_pool_sfml::set_position(const renderer_id& id,
                                      const math::Position2f& position)
{
    get_shape(id).setPosition({position.x, position.y});
}

math::Position2f renderer_pool_sfml::get_position(const renderer_id& id)
{
    return get_shape(id).getPosition();
}
void renderer_pool_sfml::set_color(const renderer_id& id,
                                   const color& new_color)
{
    get_shape(id).set_color(new_color);
}

color renderer_pool_sfml::get_color(const renderer_id& id) const
{
    return get_shape(id).get_color();
}

sfml_rectangle_shape& renderer_pool_sfml::get_shape(const renderer_id& shape_id)
{
    return const_cast<sfml_rectangle_shape&>(
        const_cast<const renderer_pool_sfml*>(this)->get_shape(shape_id));
}

const sfml_rectangle_shape&
renderer_pool_sfml::get_shape(const renderer_id& shape_id) const
{
    auto shape_it =
        std::find_if(shapes.begin(), shapes.end(), is_shape_id_equal{shape_id});

    assert(shape_it != shapes.end() && "invalid rendered_id");

    return *shape_it;
}

}
