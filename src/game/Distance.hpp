#pragma once

#include "Direction.hpp"

template <typename T, Direction diretction>
struct Distance
{
    Distance() = default;
    constexpr explicit Distance(int d) : distance{d}
    {
    }

    operator int() const
    {
        return distance;
    }

    Distance operator+=(Distance other)
    {
        distance += other.distance;
        return *this;
    }

    Distance operator+(Distance other)
    {
        auto dist = *this;
        return dist += other;
    }

private:
    int distance;
};

using LeftDistance = Distance<int, Direction::left>;
using RightDistance = Distance<int, Direction::right>;
using UpDistance = Distance<int, Direction::up>;
using DownDistance = Distance<int, Direction::down>;

constexpr LeftDistance operator"" _left(unsigned long long int d)
{
    return LeftDistance{static_cast<int>(d)};
}
constexpr RightDistance operator"" _right(unsigned long long int d)
{
    return RightDistance{static_cast<int>(d)};
}
constexpr UpDistance operator"" _up(unsigned long long int d)
{
    return UpDistance{static_cast<int>(d)};
}
constexpr DownDistance operator"" _down(unsigned long long int d)
{
    return DownDistance{static_cast<int>(d)};
}
