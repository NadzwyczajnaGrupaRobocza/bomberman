#pragma once

#include <iostream>

#include "Distance.hpp"

class ExplosionRange
{
public:
    ExplosionRange(LeftDistance left, RightDistance right, UpDistance up,
                   DownDistance down)
        : leftDist{left}, rightDist{right}, upDist{up}, downDist{down}
    {
    }

    LeftDistance left() const
    {
        return leftDist;
    }

    RightDistance right() const
    {
        return rightDist;
    }

    UpDistance up() const
    {
        return upDist;
    }

    DownDistance down() const
    {
        return downDist;
    }

    bool operator==(const ExplosionRange&) const;

private:
    LeftDistance leftDist;
    RightDistance rightDist;
    UpDistance upDist;
    DownDistance downDist;
};

std::ostream& operator<<(std::ostream& out, const ExplosionRange& range);
