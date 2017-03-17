#pragma once

#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Collision.hpp"
#include "Entity.hpp"

namespace bomberman
{
using Shapes = std::vector<sf::RectangleShape>;
using Entities = std::vector<Entity>;

class Bomberman
{
public:
    Bomberman();
    void run();

private:
    void updateEntities();
    void updateInput();
    void updatePlayerInput();
    void updateMovement(float deltaTime);
    void updateRender();
    void updatePhysics();

    void swapBuffer();
    void clearDisplay();

    void movePlayer(const sf::Vector2f& transl);
    void renderShapes();
    void generateRandomnlyArrangedStaticEntities(const std::size_t& count);
    void generateDynamicEntities(const std::size_t& count);

    sf::RenderWindow _window;
    lmg01::Board _board;
    const float _baseSpeed = 200.f;
    const std::size_t _static_entity_count = 260;
    const std::size_t _dynamic_entity_count = 1;
    float _bonusSpeed = 1.0f;
    sf::Vector2f _movementDirection{0, 0};
    Shapes _shapes;
    Entities _static_entities;
    Entities _dynamic_entities;
    physics::Collision _collision;
};
}
