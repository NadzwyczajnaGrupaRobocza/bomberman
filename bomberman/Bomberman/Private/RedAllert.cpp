#include "RedAllert.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "Entity.hpp"

namespace bomberman
{
RedAllert::RedAllert(Entity& entity) : _entity{entity}
{
}

void RedAllert::onCollisionEnter(physics::Collider&)
{
    _entity.get_shape().setFillColor(sf::Color::Red);
}

void RedAllert::onCollisionExit()
{
    _entity.get_shape().setFillColor(sf::Color::Blue);
}
}
