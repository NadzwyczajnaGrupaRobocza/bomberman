#include "gmock/gmock.h"

#include "fakeit.hpp"

#include "GameWorld.hpp"
#include "LimitedBombLauncher.hpp"

using namespace ::fakeit;

struct LimitedBombLauncherTest : public ::testing::Test
{
    const math::Position2 default_position{0.2f, 0.2f};
    const bool bomb_has_been_spawned = true;
    const bool bomb_cannot_be_spawned = false;
    const int max_bombs = 2;

    fakeit::Mock<GameWorld> game_world;
    LimitedBombLauncher launcher{max_bombs};
};

struct LimitedBombLauncherWithoutBombsLaunched : public LimitedBombLauncherTest
{
};

TEST_F(LimitedBombLauncherWithoutBombsLaunched, ShouldLaunchBomb)
{
    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));
}

struct LimitedBombLauncherWithAllBombsLunched : public LimitedBombLauncherTest
{
    LimitedBombLauncherWithAllBombsLunched()
    {
        launcher.try_spawn_bomb(default_position);
        launcher.try_spawn_bomb(default_position);
    }
};

TEST_F(LimitedBombLauncherWithAllBombsLunched, ShouldNotLaunchBomb)
{
    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_cannot_be_spawned));
}

TEST_F(LimitedBombLauncherWithAllBombsLunched,
       AfterNotfiedExploded_ShouldLaunchBomb)
{
    launcher.notify_exploded();

    ASSERT_THAT(launcher.try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));
}

TEST_F(LimitedBombLauncherWithAllBombsLunched,
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
