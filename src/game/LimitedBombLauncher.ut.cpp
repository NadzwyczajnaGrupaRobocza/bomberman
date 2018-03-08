#include "gmock/gmock.h"

#include "fakeit.hpp"

#include "Bomb.hpp"
#include "BombFactory.hpp"
#include "GameWorld.hpp"
#include "LimitedBombLauncher.hpp"

using namespace ::fakeit;

struct LimitedBombLauncherTest : public ::testing::Test
{
    LimitedBombLauncherTest()
    {
        Fake(Dtor(game_world));
        Fake(Dtor(bomb_factory));
        When(Method(game_world, is_bomb_at_pos)).AlwaysReturn(no_bom_at_pos);
    }

    const math::Position2f default_position{0.2f, 0.2f};
    const BombPosition default_bomb_position{default_position};
    const bool bomb_has_been_spawned = true;
    const bool bomb_cannot_be_spawned = false;
    const bool bomb_at_pos = true;
    const bool no_bom_at_pos = false;
    const int max_bombs = 2;

    Mock<GameWorld> game_world;
    Mock<BombFactory> bomb_factory;
    std::shared_ptr<GameWorld> gw =
        std::shared_ptr<GameWorld>(&game_world.get());
    std::shared_ptr<BombFactory> bf =
        std::shared_ptr<BombFactory>(&bomb_factory.get());
    std::unique_ptr<Mock<Bomb>> unique_bomb = std::make_unique<Mock<Bomb>>();
    Mock<Bomb>& bomb = *unique_bomb.get();
    LimitedBombLauncher launcher = LimitedBombLauncher{gw, bf, max_bombs};
};

struct LimitedBombLauncherWithoutBombsLaunched : public LimitedBombLauncherTest
{
};

TEST_F(LimitedBombLauncherWithoutBombsLaunched, ShouldLaunchBomb)
{
    Fake(Dtor(bomb));
    When(Method(bomb_factory, create_time_bomb)).Do([&]() { return std::unique_ptr<Bomb>{&unique_bomb->get()}; });
    When(Method(game_world, register_bomb).Using(default_bomb_position, unique_bomb->get()));

    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));

    Verify(Method(bomb_factory, create_time_bomb));
}

TEST_F(LimitedBombLauncherWithoutBombsLaunched,
       WhenThereIsBombAtPostition_ShouldNotSpawnBomb)
{
    When(Method(game_world, is_bomb_at_pos).Using(default_bomb_position))
        .Return(bomb_at_pos);

    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_cannot_be_spawned));
}

struct LimitedBombLauncherWithAllBombsLaunched : public LimitedBombLauncherTest
{
    LimitedBombLauncherWithAllBombsLaunched()
    {
        When(Method(bomb_factory, create_time_bomb)).AlwaysDo([&]() {
            return nullptr;
        });
        launcher.try_spawn_bomb(default_position);
        launcher.try_spawn_bomb(default_position);
    }
};

TEST_F(LimitedBombLauncherWithAllBombsLaunched, ShouldNotLaunchBomb)
{
    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_cannot_be_spawned));
}

TEST_F(LimitedBombLauncherWithAllBombsLaunched,
       AfterNotfiedExploded_ShouldLaunchBomb)
{
    launcher.notify_exploded();

    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));
}

TEST_F(LimitedBombLauncherWithAllBombsLaunched,
       AfterNotfiedExplodedMoreTimesThenBombs_ShouldLaunchMaxNumberOfBombs)
{
    launcher.notify_exploded();
    launcher.notify_exploded();
    launcher.notify_exploded();

    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));
    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));
    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_cannot_be_spawned));
}
