#pragma once

namespace sf
{
class RectangleShape;
}

namespace physics
{
class Collider;
}

namespace bomberman
{
class Entity
{
public:
    Entity(sf::RectangleShape&, physics::Collider&);
    sf::RectangleShape& get_shape();
    physics::Collider& get_collider();

    void update();

private:
    sf::RectangleShape& _shape;
    physics::Collider& _collider;
};
}
