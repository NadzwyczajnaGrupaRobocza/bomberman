#include "BombermanGameWorld.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"
#include <memory>
#include <chrono>
#include "math/Size2u.hpp"

int main()
{
    const math::Size2u window_size{800, 600};
    sf::Window window(sf::VideoMode(window_size.width, window_size.height), "Bomberman Remake");

    BombermanGameWorld world;
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
        world.update(ElapsedTime{ms});

        window.display();
    }
}

