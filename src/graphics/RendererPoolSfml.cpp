#include "RendererPoolSfml.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <iostream>

namespace graphics
{
RendererPoolSfml::~RendererPoolSfml()
{
    std::cout << "dupa destr\n";
}
RendererPoolSfml::RendererPoolSfml(std::unique_ptr<SfmlRenderTarget> renderer,
                                   std::unique_ptr<DrawableFactory> factory)
    : window_renderer{std::move(renderer)}, drawable_factory{std::move(factory)}
{
    window_renderer->initialize();
}

RenderId RendererPoolSfml::take(const math::Size&, const math::Position2&)
{
    return RenderId{};
}

void RendererPoolSfml::give_back(const RenderId&)
{
}

void RendererPoolSfml::set_position(const RenderId&, const math::Position2&)
{
}

void RendererPoolSfml::render_all()
{
    window_renderer->clear(sf::Color::Black);

    //auto shape = drawable_factory->create_rectangle(sf::Vector2f{19, 100});
    auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f{19, 100});
    shape->setPosition(100, 100);
    std::cout << "dupa 2--" << (shape != nullptr) << "\n";
    window_renderer->draw(*shape);
    std::cout << "dupa 3--" << (shape != nullptr) << "\n";
}
}
