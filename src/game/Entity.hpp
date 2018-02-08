#pragma once

#include "DeltaTime.hpp"

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void update(DeltaTime) = 0;
    virtual bool areYouDead() const = 0;
};
