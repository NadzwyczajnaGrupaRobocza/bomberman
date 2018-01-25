#include "gmock/gmock.h"

#include "LimitedBombLauncher.hpp"

using namespace ::testing;

struct LimitedBombLauncherTest : public Test
{
    const math::Position2 defaultPosition{0.2f, 0.2f};
    const bool bombHasBeenSpawned = true;
    const bool bombCannotBeSpawned = false;
    const int maxBombs = 2;

    LimitedBombLauncher launcher{maxBombs};
};

struct LimitedBombLauncherWithoutBombsLaunched : public LimitedBombLauncherTest
{
};

TEST_F(LimitedBombLauncherWithoutBombsLaunched, ShouldLaunchBomb)
{
    ASSERT_THAT(launcher.try_spawn_bomb(defaultPosition),
                Eq(bombHasBeenSpawned));
}

struct LimitedBombLauncherWithAllBombsLunched : public LimitedBombLauncherTest
{
    LimitedBombLauncherWithAllBombsLunched()
    {
        launcher.try_spawn_bomb(defaultPosition);
        launcher.try_spawn_bomb(defaultPosition);
    }
};

TEST_F(LimitedBombLauncherWithAllBombsLunched, ShouldNotLaunchBomb)
{
    ASSERT_THAT(launcher.try_spawn_bomb(defaultPosition),
                Eq(bombCannotBeSpawned));
}

TEST_F(LimitedBombLauncherWithAllBombsLunched,
       AfterNotfiedExploded_ShouldLaunchBomb)
{
    launcher.notifyExploded();

    ASSERT_THAT(launcher.try_spawn_bomb(defaultPosition),
                Eq(bombHasBeenSpawned));
}

TEST_F(LimitedBombLauncherWithAllBombsLunched,
       AfterNotfiedExplodedMoreTimesThenBombs_ShouldLaunchMaxNumberOfBombs)
{
    launcher.notifyExploded();
    launcher.notifyExploded();
    launcher.notifyExploded();

    ASSERT_THAT(launcher.try_spawn_bomb(defaultPosition),
                Eq(bombHasBeenSpawned));
    ASSERT_THAT(launcher.try_spawn_bomb(defaultPosition),
                Eq(bombHasBeenSpawned));
    ASSERT_THAT(launcher.try_spawn_bomb(defaultPosition),
                Eq(bombCannotBeSpawned));
}
