#include "Collision.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <cassert>

#include "Entity.hpp"

namespace physics
{
Collision::Collision(std::size_t triggers_count, std::size_t colliders_count)
{
    triggers.reserve(triggers_count);
    colliders.reserve(colliders_count);
}

void Collision::update()
{
    collidersVsTriggers();
    collidersVsColliders();
}

void Collision::collidersVsTriggers()
{
    boost::for_each(colliders, [this](auto& collider) {
        boost::for_each(triggers, [this, &collider](auto& trigger) {
            if (this->AABBvsAABB(collider.get_aabb(), trigger.get_aabb()))
            {
                trigger.addCollision(collider);
            }
        });
    });
}

void Collision::collidersVsColliders()
{
    // TODO:
}

Collider& Collision::addTrigger(sf::Vector2f position, float width,
                                float height)
{
    triggers.emplace_back(createCollider(position, width, height));
    return triggers.back();
}

Collider& Collision::addCollider(sf::Vector2f position, float width,
                                 float height)
{
    colliders.emplace_back(createCollider(position, width, height));
    return colliders.back();
}

Collider Collision::createCollider(sf::Vector2f position, float width,
                                   float height)
{
    AABB aabb{};
    aabb.x = position.x;
    aabb.y = position.y;
    aabb.width = width;
    aabb.height = height;

    return Collider{aabb};
}

bool Collision::AABBvsAABB(const AABB& a, const AABB& b) const
{
    if (a.x > (b.x + b.width) || (a.x + a.width) < b.x)
    {
        return false;
    }

    if (a.y > (b.y + b.height) || (a.y + a.height) < b.y)
    {
        return false;
    }

    return true;
}
}
