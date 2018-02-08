#pragma once

#include <memory>

class Bomb;

class BombFactory
{
public:
    virtual ~BombFactory() noexcept = default;

    virtual std::unique_ptr<Bomb> create_time_bomb() const = 0;
};
