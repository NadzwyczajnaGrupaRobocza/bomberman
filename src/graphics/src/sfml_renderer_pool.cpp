#include "sfml_renderer_pool.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <range/v3/algorithm/for_each.hpp>

#include "boost/range/algorithm_ext/erase.hpp"

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

sfml_renderer_pool::sfml_renderer_pool(std::unique_ptr<context_renderer> r,
                                       std::unique_ptr<texture_loader> loader)
    : renderer{std::move(r)}, textures{std::move(loader)}
{
    renderer->initialize();
    renderer->set_view();
}

renderer_id sfml_renderer_pool::acquire(const math::Size2f& size,
                                        const math::Position2f& position,
                                        const color& shape_color)
{
    auto id = renderer_id_generator::generate();
    shapes.emplace_back(id, size, position, shape_color);
    return id;
}

renderer_id sfml_renderer_pool::acquire(const math::Size2f& size,
                                        const math::Position2f& position,
                                        const std::string& texture_path)
{
    const auto id = acquire(size, position, graphics::colors::white);
    set_texture(id, texture_path);
    return id;
}

void sfml_renderer_pool::set_texture(const renderer_id& id,
                                     const texture_path& path)
{
    const auto& texture = textures->load(path);
    get_shape(id).setTexture(&texture);
}

void sfml_renderer_pool::release(const renderer_id& id)
{
    trash.emplace(id);
}

void sfml_renderer_pool::cleanup_unused()
{
    boost::remove_erase_if(
        shapes, [this](auto& shape) { return trash.count(shape.get_id()); });
    trash.clear();
}

void sfml_renderer_pool::render_all()
{
    cleanup_unused();
    renderer->clear(sf::Color::White);

    renderer->set_view();

    ranges::for_each(shapes, [&](const auto& shape) { renderer->draw(shape); });
}

void sfml_renderer_pool::set_position(const renderer_id& id,
                                      const math::Position2f& position)
{
    get_shape(id).setPosition({position.x, position.y});
}

math::Position2f sfml_renderer_pool::get_position(const renderer_id& id)
{
    return get_shape(id).getPosition();
}

void sfml_renderer_pool::set_color(const renderer_id& id,
                                   const color& new_color)
{
    get_shape(id).set_color(new_color);
}

color sfml_renderer_pool::get_color(const renderer_id& id) const
{
    return get_shape(id).get_color();
}

sfml_rectangle_shape& sfml_renderer_pool::get_shape(const renderer_id& shape_id)
{
    return const_cast<sfml_rectangle_shape&>(
        const_cast<const sfml_renderer_pool*>(this)->get_shape(shape_id));
}

const sfml_rectangle_shape&
sfml_renderer_pool::get_shape(const renderer_id& shape_id) const
{
    auto shape_it =
        std::find_if(shapes.begin(), shapes.end(), is_shape_id_equal{shape_id});

    assert(shape_it != shapes.end() && "invalid rendered_id");

    return *shape_it;
}
}
