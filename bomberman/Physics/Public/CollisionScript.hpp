#pragma once

namespace physics
{
class Collider;
class CollisionScript
{
public:
    virtual ~CollisionScript() = default;

    virtual void onCollisionEnter(Collider&) = 0;
    virtual void onCollisionExit() = 0; // TODO: should take Collider as argument
};
}
