#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Collider.hpp"

namespace physics
{
using Colliders = std::vector<Collider>;

class Collision
{
public:
    Collision(std::size_t triggers_count, std::size_t colliders_count);

    void update();
    Collider& addTrigger(sf::Vector2f position, float width, float height);
    Collider& addCollider(sf::Vector2f position, float width, float height);

private:
    void collidersVsTriggers();
    void collidersVsColliders();

    Collider createCollider(sf::Vector2f position, float width, float height);
    bool AABBvsAABB(const AABB&, const AABB&) const;

private:
    Colliders triggers;
    Colliders colliders;
};
}
