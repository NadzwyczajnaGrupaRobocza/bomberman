#include "ExplosionRange.hpp"

#include <tuple>

bool ExplosionRange::operator==(const ExplosionRange& other) const
{
    return std::tie(leftDist, rightDist, upDist, downDist) ==
           std::tie(other.leftDist, other.rightDist, other.upDist,
                    other.downDist);
}

std::ostream& operator<<(std::ostream& out, const ExplosionRange& range)
{
    out << "{";
    out << "Left: " << range.left() << " ,";
    out << "Right: " << range.right() << " ,";
    out << "Up: " << range.up() << " ,";
    out << "Down: " << range.down();
    out << "}";
    return out;
}
