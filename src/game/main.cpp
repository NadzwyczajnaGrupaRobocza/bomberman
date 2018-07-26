#include "BombermanGameWorld.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"
#include <memory>
#include <chrono>
#include "math/Size2u.hpp"
#include "graphics/factory.hpp"
#include "physics/PhysicsEngine.hpp"
#include "physics/ConcretePhysicsEngine.hpp"

int main()
{
  const math::Size2u window_size{800, 600};
  sf::Window window(sf::VideoMode(window_size.width, window_size.height), "Bomberman Remake");

  //auto window = graphics::create_window(window_size, "Bomberman remake");
  auto r = graphics::create_renderer_pool(window_size);
  auto p = std::make_unique<physics::ConcretePhysicsEngine>();

  auto world = std::make_shared<BombermanGameWorld>(std::move(p), std::move(r));
  sf::Clock clock;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
          window.close();
    }

    const std::chrono::milliseconds ms{clock.restart().asMilliseconds()};
    world->update(DeltaTime{ms});

    window.display();
  }
}

