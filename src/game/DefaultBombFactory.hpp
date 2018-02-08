#pragma once

#include "BombFactory.hpp"

class DefautlBombFactory : public BombFactory
{
public:
    virtual std::shared_ptr<Bomb> create_time_bomb() const = 0;
};
