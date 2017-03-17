#include "CollisionScript.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "Collider.hpp"
#include "Entity.hpp"

namespace physics
{
CollisionScript::CollisionScript(bomberman::Entity& entity) : _entity{entity}
{
}

void CollisionScript::onCollisionEnter(Collider&)
{
    _entity.get_shape().setFillColor(sf::Color::Red);
}

void CollisionScript::onCollisionExit()
{
    _entity.get_shape().setFillColor(sf::Color::Blue);
}
}
