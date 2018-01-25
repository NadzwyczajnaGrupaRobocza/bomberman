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
