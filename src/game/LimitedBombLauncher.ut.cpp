#include "gmock/gmock.h"

#include "LimitedBombLauncher.hpp"

using namespace ::testing;

class LimitedBombLauncherTest : public Test
{
public:
    const math::Position2 defaultPosition{0.2f, 0.2f};
    const bool bombHasBeenSpawned = true;
    const bool bombCannotBeSpawned = false;

    LimitedBombLauncher launcher;
};

TEST_F(LimitedBombLauncherTest, ShouldLaunchBomb)
{
    ASSERT_THAT(launcher.try_spawn_bomb(defaultPosition),
                Eq(bombHasBeenSpawned));
}
