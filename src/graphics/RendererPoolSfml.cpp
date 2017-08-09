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
                                  const math::Position2&)
{
    auto id = renderer_id_generator->generate();
    std::clog << __FUNCTION__ << " " << shapes.size() << " : "
              << boost::uuids::to_string(id) << '\n';
    shapes.emplace(id, sf::Vector2f{size.width, size.height});
    std::clog << __FUNCTION__ << " " << shapes.size() << " : " << id << '\n';
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

    std::clog << "DUPA: " << shapes.size() << "\n";
    boost::for_each(shapes, [&](const auto& shape) {
        std::clog << __FUNCTION__ << " " << shape.second.getSize().x << ","
                  << shape.second.getSize().y << "\n";
        context_renderer->draw(shape.second);
    });
}

void RendererPoolSfml::set_position(const RendererId&, const math::Position2&)
{
}
}
