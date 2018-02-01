#pragma once

#include <chrono>

using DeltaTime = std::chrono::milliseconds;

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void update(DeltaTime) = 0;
    virtual bool areYouDead() const = 0;
};
