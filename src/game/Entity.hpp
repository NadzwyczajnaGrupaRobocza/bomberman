#pragma once

#include <chrono>

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void update(std::chrono::milliseconds) = 0;
    virtual bool areYouDead() const = 0;
};
