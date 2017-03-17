#pragma once

#include "CollisionScript.hpp"

namespace bomberman
{
class Entity;
class RedAllert : public physics::CollisionScript
{
public:
    RedAllert(bomberman::Entity&);
    void onCollisionEnter(physics::Collider&) override;
    void onCollisionExit() override;

private:
    bomberman::Entity& _entity;
};
}
