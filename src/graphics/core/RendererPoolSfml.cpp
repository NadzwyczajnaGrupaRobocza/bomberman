#include "RendererPoolSfml.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <range/v3/algorithm/for_each.hpp>

#include <boost/uuid/uuid_io.hpp>

namespace graphics
{

RendererPoolSfml::RendererPoolSfml(
    std::unique_ptr<ContextRenderer> renderer,
    std::unique_ptr<RendererIdGenerator> generator)
    : context_renderer{std::move(renderer)}, renderer_id_generator{
                                                 std::move(generator)}
{
    context_renderer->initialize();
}

RendererId RendererPoolSfml::acquire(const math::Size2f& size,
                                     const math::Position2f& position)
{
    auto id = renderer_id_generator->generate();
    shapes.emplace(std::piecewise_construct, std::forward_as_tuple(id),
                   std::forward_as_tuple(size, position));
    return id;
}

void RendererPoolSfml::release(const RendererId& id)
{
    trash.emplace(id);
}

void RendererPoolSfml::cleanup_unused()
{
    ranges::for_each(trash, [this](const auto& id) { shapes.erase(id); });
    trash.clear();
}

void RendererPoolSfml::render_all()
{
    cleanup_unused();
    context_renderer->clear(sf::Color::Black);

    ranges::for_each(shapes, [&](const auto& shape) {
        context_renderer->draw(shape.second);
    });
}

void RendererPoolSfml::set_position(const RendererId& id,
                                    const math::Position2f& position)
{
    shapes.at(id).setPosition({position.x, position.y});
}

math::Position2f RendererPoolSfml::get_position(const RendererId& id)
{
    return shapes.at(id).getPosition();
}
}
