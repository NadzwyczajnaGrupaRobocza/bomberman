#include "BombermanGameWorld.hpp"


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

void BombermanGameWorld::update(ElapsedTime dt)
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
