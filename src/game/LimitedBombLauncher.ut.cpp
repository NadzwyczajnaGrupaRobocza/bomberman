#include <gmock/gmock.h>

#include <iostream>
#include <fakeit.hpp>

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
    std::unique_ptr<Mock<Bomb>> unique_bomb = std::make_unique<Mock<Bomb>>();
    Mock<Bomb>& bomb = *unique_bomb.get();
    std::shared_ptr<LimitedBombLauncher> launcher =
        std::make_shared<LimitedBombLauncher>(
            std::shared_ptr<GameWorld>(&game_world.get()),
            std::shared_ptr<BombFactory>(&bomb_factory.get(), [](auto) {}),
            max_bombs);
};

std::ostream& operator<<(std::ostream& o, BombPosition pos);
std::ostream& operator<<(std::ostream& o, BombPosition bp)
{
    math::Position2f pos(bp);
    return o << pos.x << ", " << pos.y;
}

struct LimitedBombLauncherWithoutBombsLaunched : public LimitedBombLauncherTest
{
};

TEST_F(LimitedBombLauncherWithoutBombsLaunched, ShouldLaunchBomb)
{
    Fake(Dtor(bomb));
    When(Method(bomb_factory, create_time_bomb)
             .Matching([&](auto& bomb_position, auto& givenLauncher) {
                 return bomb_position == default_bomb_position &&
                        givenLauncher == launcher;
             }))
        .Do([&](auto, auto) {
            return std::unique_ptr<Bomb>{&unique_bomb->get()};
        });
    When(Method(game_world, register_bomb)
             .Matching([&](BombPosition& bombPosition,
                           std::unique_ptr<Bomb>& uniq_bomb) {
                 const auto uniq_bom_address = uniq_bomb.get();
                 uniq_bomb.release();
                 return bombPosition == default_bomb_position &&
                        uniq_bom_address == &unique_bomb->get();
             }))
        .Return();

    ASSERT_THAT(launcher->try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));

    Verify(Method(bomb_factory, create_time_bomb));
    Verify(Method(game_world, register_bomb));
}

TEST_F(LimitedBombLauncherWithoutBombsLaunched,
       WhenThereIsBombAtPostition_ShouldNotSpawnBomb)
{
    When(Method(game_world, is_bomb_at_pos).Using(default_bomb_position))
        .Return(bomb_at_pos);

    ASSERT_THAT(launcher->try_spawn_bomb(default_position),
                ::testing::Eq(bomb_cannot_be_spawned));
}

struct LimitedBombLauncherWithAllBombsLaunched : public LimitedBombLauncherTest
{
    LimitedBombLauncherWithAllBombsLaunched()
    {
        When(Method(bomb_factory, create_time_bomb)).AlwaysDo([&](auto, auto) {
            auto mock_bomb = std::make_unique<Mock<Bomb>>();
            Mock<Bomb>& bomb_ref = *mock_bomb.get();
            Fake(Dtor(bomb_ref));
            return std::unique_ptr<Bomb>{&mock_bomb->get()};
        });
        When(Method(game_world, register_bomb))
            .AlwaysDo([&](auto&, auto& bomb_to_release) {
                bomb_to_release.release();
            });
        launcher->try_spawn_bomb(default_position);
        launcher->try_spawn_bomb(default_position);
    }
};

TEST_F(LimitedBombLauncherWithAllBombsLaunched, ShouldNotLaunchBomb)
{
    ASSERT_THAT(launcher->try_spawn_bomb(default_position),
                ::testing::Eq(bomb_cannot_be_spawned));
}

TEST_F(LimitedBombLauncherWithAllBombsLaunched,
       AfterNotfiedExploded_ShouldLaunchBomb)
{
    launcher->notify_exploded();

    ASSERT_THAT(launcher->try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));
}

TEST_F(LimitedBombLauncherWithAllBombsLaunched,
       AfterNotfiedExplodedMoreTimesThenBombs_ShouldLaunchMaxNumberOfBombs)
{
    launcher->notify_exploded();
    launcher->notify_exploded();
    launcher->notify_exploded();

    ASSERT_THAT(launcher->try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));
    ASSERT_THAT(launcher->try_spawn_bomb(default_position),
                ::testing::Eq(bomb_has_been_spawned));
    ASSERT_THAT(launcher->try_spawn_bomb(default_position),
                ::testing::Eq(bomb_cannot_be_spawned));
}
