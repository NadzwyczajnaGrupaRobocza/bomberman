#pragma once

#include "CollisionScript.hpp"

namespace bomberman
{
class Entity;
class GreenAllert : public physics::CollisionScript
{
public:
    GreenAllert(bomberman::Entity&);
    void onCollisionEnter(physics::Collider&) override;
    void onCollisionExit() override;

private:
    bomberman::Entity& _entity;
};
}
