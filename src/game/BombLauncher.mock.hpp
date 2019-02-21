#pragma once

#include "gmock/gmock.h"

#include "game/BombLauncher.hpp"

class MockBombLauncher : public BombLauncher
{
public:
    MOCK_METHOD1(try_spawn_bomb, bool(math::Position2f));
    MOCK_METHOD0(notify_exploded, void());
};
