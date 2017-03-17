#include "Entity.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include "Collider.hpp"

namespace bomberman
{
Entity::Entity(sf::RectangleShape& shape, physics::Collider& collider)
    : _shape{shape}, _collider{collider}
{
}

sf::RectangleShape& Entity::get_shape()
{
    return _shape;
}

physics::Collider& Entity::get_collider()
{
    return _collider;
}

void Entity::update()
{
    _collider.runScript();
}
}
