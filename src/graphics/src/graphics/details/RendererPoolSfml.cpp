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

RendererId RendererPoolSfml::take(const Size& size, const Position& position)
{
    auto id = renderer_id_generator->generate();
    auto shape = shapes.emplace(id, sf::Vector2f{size.width, size.height});
    shape.first->second.setPosition(position.x, position.y);
    std::clog << "x: " << position.x << ", y: " << position.y << '\n';
    return id;
}

void RendererPoolSfml::give_back(const RendererId& id)
{
    trash.emplace(id);
    std::clog << "give_back \n";
}

void RendererPoolSfml::cleanup_unused()
{
    for (const auto& id : trash)
    {
        shapes.erase(id);
        std::clog << "left: " << shapes.size() << '\n';
    }
    trash.clear();
}

void RendererPoolSfml::render_all()
{
    cleanup_unused();
    context_renderer->clear(sf::Color::Black);

    boost::for_each(shapes, [&](const auto& shape) {
        context_renderer->draw(shape.second);
    });
}

void RendererPoolSfml::set_position(const RendererId& id,
                                    const Position& position)
{
    shapes.at(id).setPosition({position.x, position.y});
}

Position RendererPoolSfml::get_position(const RendererId& id)
{
    return {shapes.at(id).getPosition().x, shapes.at(id).getPosition().y};
}
}
