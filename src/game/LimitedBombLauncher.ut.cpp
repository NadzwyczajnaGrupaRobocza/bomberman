#include "gmock/gmock.h"

#include "fakeit.hpp"

#include "BombFactory.hpp"
#include "GameWorld.hpp"
#include "LimitedBombLauncher.hpp"

using namespace ::fakeit;

struct LimitedBombLauncherTest : public ::testing::Test
{
    LimitedBombLauncherTest()
    {
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
        std::shared_ptr<GameWorld>(&game_world.get(), [](...) {});
    std::shared_ptr<BombFactory> bf =
        std::shared_ptr<BombFactory>(&bomb_factory.get(), [](...) {});
    LimitedBombLauncher launcher = LimitedBombLauncher{gw, bf, max_bombs};
};

struct LimitedBombLauncherWithoutBombsLaunched : public LimitedBombLauncherTest
{
};

TEST_F(LimitedBombLauncherWithoutBombsLaunched, ShouldLaunchBomb)
{
    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));
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
