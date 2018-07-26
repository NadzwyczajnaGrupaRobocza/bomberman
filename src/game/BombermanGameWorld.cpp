#include "BombermanGameWorld.hpp"
#include "BoundaryWallsPositionsGenerator.hpp"


BombermanGameWorld::BombermanGameWorld(std::unique_ptr<physics::PhysicsEngine> a, std::unique_ptr<graphics::RendererPool> b)
 : gen(std::make_unique<BoundaryWallsPositionsGenerator>()),
   simpleMap{*a, *gen, *b}
{}

bool BombermanGameWorld::is_bomb_at_pos(const BombPosition& p) const
{
    return bombs.count(p);
}

void BombermanGameWorld::register_bomb(BombPosition p, std::unique_ptr<Bomb> bomb)
{
    bombs[p] = std::move(bomb);
}

void BombermanGameWorld::register_explosion(ExplosionPosition p, std::unique_ptr<Explosion> explosion)
{
    explosions[p] = std::move(explosion);
}

void BombermanGameWorld::update(DeltaTime dt)
{
    for(const auto& b : bombs)
    {
        b.second->update(dt);
    }

    for(const auto& e : entity)
    {
        e->update(dt);
    }

    //TODO: Uncomment me when explision are present
   /*
    for(const auto& e : explosions)
    {
        e.second->update(dt);
    }
    */
}
