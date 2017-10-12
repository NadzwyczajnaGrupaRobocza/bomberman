#include "RendererPoolSfml.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <boost/uuid/uuid_io.hpp>

#include <iostream>

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
    return id;
}

void RendererPoolSfml::give_back(const RendererId& id)
{
    trash.emplace(id);
}

void RendererPoolSfml::cleanup_unused()
{
    for(const auto& id : trash)
    {
        std::cerr << "id: \n";
        shapes.erase(id);
    }
    trash.clear();
}

void RendererPoolSfml::render_all()
{
    std::cerr << "size before: " << shapes.size() << '\n';
    cleanup_unused();
    std::cerr << "size after: " << shapes.size() << '\n';
    context_renderer->clear(sf::Color::Black);

    boost::for_each(shapes, [&](const auto& shape) {
        context_renderer->draw(shape.second);
    });
}

void RendererPoolSfml::set_position(const RendererId&, const Position&)
{
}

Position RendererPoolSfml::get_position(const RendererId&)
{
    return Position{};
}
}
