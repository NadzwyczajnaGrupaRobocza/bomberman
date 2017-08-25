#include "RendererPoolSfml.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <boost/range/algorithm/for_each.hpp>

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

RendererId RendererPoolSfml::take(const math::Size& size,
                                  const math::Position2& position)
{
    auto id = renderer_id_generator->generate();
    auto shape = shapes.emplace(id, sf::Vector2f{size.width, size.height});
    shape.first->second.setPosition(sf::Vector2f(position.x, position.y));
    return id;
}

void RendererPoolSfml::give_back(const RendererId&)
{
}

void RendererPoolSfml::cleanup_unused()
{
}

void RendererPoolSfml::render_all()
{
    context_renderer->clear(sf::Color::Black);

    boost::for_each(shapes, [&](const auto& shape) {
        context_renderer->draw(shape.second);
    });
}

void RendererPoolSfml::set_position(const RendererId&, const math::Position2&)
{
}

void RendererPoolSfml::get_position(const RendererId&)
{
}
}
