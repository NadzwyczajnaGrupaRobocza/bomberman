#pragma once

#include "gmock/gmock.h"

#include "GameWorld.hpp"

class MockGameWorld : public GameWorld
{
public:
    MOCK_CONST_METHOD1(is_bomb_at_pos, bool(const BombPosition&));
    MOCK_METHOD2(register_bomb, void(BombPosition, std::unique_ptr<Bomb>));
    MOCK_METHOD1(deregister_bomb, void(const Bomb*));
    MOCK_METHOD2(register_explosion,
                 void(ExplosionPosition, std::unique_ptr<Explosion>));
    MOCK_METHOD1(deregister_explosion, void(const Explosion*));
    MOCK_METHOD1(update, void(DeltaTime));
};
