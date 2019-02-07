#include "BombermanGameWorld.hpp"
#include "BoundaryWallsPositionsGenerator.hpp"
#include "HumanPlayerSfml.hpp"
#include "LimitedBombLauncher.hpp"
#include "Bomberman.hpp"
#include "DefaultBombFactory.hpp"
#include <boost/core/null_deleter.hpp>

BombermanGameWorld::BombermanGameWorld(std::unique_ptr<physics::PhysicsEngine> a, std::unique_ptr<graphics::renderer_pool> b)
 : gen(std::make_unique<BoundaryWallsPositionsGenerator>()),
   simpleMap{*a, *gen, *b},
   ppool{std::move(a)},
   rpool{std::move(b)}

{
   std::shared_ptr<GameWorld> world(this, boost::null_deleter());

   auto hp = std::make_unique<HumanPlayerSfml>();
   auto bf = std::make_shared<DefautlBombFactory>(*ppool, *rpool);
   auto bl = std::make_unique<LimitedBombLauncher>(world, std::move(bf), 10);

   physics::PhysicsId pid{};
  
   auto rid = rpool->acquire(math::Size2f{30, 40}, math::Position2f{70, 70});
   entity.emplace_back(std::make_unique<Bomberman>(pid, rid, std::move(hp), ppool, rpool, std::move(bl)));
}

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
    rpool->render_all();
}
