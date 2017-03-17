#pragma once

#include <type_traits>

namespace physics
{
struct AABB
{
    float x;
    float y;
    float width;
    float height;
};
static_assert(std::is_pod<AABB>::value, "AABB must be a POD type.");
}
