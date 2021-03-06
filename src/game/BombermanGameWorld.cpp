#include <boost/core/null_deleter.hpp>
#include <experimental/map>

#include "Bomberman.hpp"
#include "BombermanGameWorld.hpp"
#include "BoundaryWallsPositionsGenerator.hpp"
#include "DefaultBombFactory.hpp"
#include "FieldSize.hpp"
#include "HumanPlayerSfml.hpp"
#include "LimitedBombLauncher.hpp"

BombermanGameWorld::BombermanGameWorld(
    std::unique_ptr<physics::PhysicsEngine> a,
    std::unique_ptr<graphics::renderer_pool> b, const math::Size2u& map_size)
    : gen(std::make_unique<BoundaryWallsPositionsGenerator>()),
      simpleMap{*a, *gen, *b, map_size}, ppool{std::move(a)}, rpool{
                                                                  std::move(b)}

{
    std::shared_ptr<GameWorld> world(this, boost::null_deleter());

    auto hp = std::make_unique<HumanPlayerSfml>();
    auto bf = std::make_shared<DefautlBombFactory>(ppool, rpool);
    auto bl = std::make_unique<LimitedBombLauncher>(world, std::move(bf), 10);

    physics::PhysicsId pid{};
    auto rid = rpool->acquire(field_size_f, math::Position2f{10, 10},
                              "resources/bomberman.png");

    entity.emplace_back(std::make_unique<Bomberman>(
        pid, rid, std::move(hp), ppool, rpool, std::move(bl)));
}

bool BombermanGameWorld::is_bomb_at_pos(const BombPosition& p) const
{
    return bombs.count(p);
}

void BombermanGameWorld::register_bomb(BombPosition p,
                                       std::unique_ptr<Bomb> bomb)
{
    bombs[p] = std::move(bomb);
}

void BombermanGameWorld::register_explosion(
    ExplosionPosition p, std::unique_ptr<Explosion> explosion)
{
    explosions[p] = std::move(explosion);
}

void BombermanGameWorld::update(DeltaTime dt)
{
    for (const auto& b : bombs)
    {
        b.second->update(dt);
    }

    for (const auto& e : entity)
    {
        e->update(dt);
    }

    // TODO: Uncomment me when explision are present
    /*
     for(const auto& e : explosions)
     {
         e.second->update(dt);
     }
     */
    rpool->render_all();
    cleanBombs();
}

void BombermanGameWorld::cleanBombs()
{
    std::experimental::erase_if(bombs, [](const auto& element) {
        return element.second->hasExploded();
    });
}

void BombermanGameWorld::window_size_changed(const graphics::window_size& size)
{
    rpool->set_rendering_size(size);
}
