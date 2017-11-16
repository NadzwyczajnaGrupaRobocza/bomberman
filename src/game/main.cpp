#include "BombermanGameWorld.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <chrono>

int main()
{
    const std::pair<int, int> window_size{800, 600};
    sf::Window window(sf::VideoMode(window_size.first, window_size.second), "Bomberman Remake");

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

        std::chrono::milliseconds ms{clock.restart().asMilliseconds()};
        world.update(ElapsedTime{ms});

        window.display();
    }
}

