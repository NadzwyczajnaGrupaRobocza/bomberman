#include "DefaultBombFactory.hpp"

#include "TimeBomb.hpp"

std::unique_ptr<Bomb> DefautlBombFactory::create_time_bomb() const
{
    return nullptr;
}
