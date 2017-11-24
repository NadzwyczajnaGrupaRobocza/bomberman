#pragma once

#include <boost/operators.hpp>

namespace math
{
template <typename T>
struct Size2 : boost::additive<Size2<T>>, boost::totally_ordered<Size2<T>>
{
    constexpr Size2(const T width_, const T height_)
        : width{width_}, height{height_}
    {
    }

    T& operator+=(const Size2<T>& size)
    {
        width += size.width;
        height += size.height;
        return *this;
    }

    bool operator==(const Size2<T>& size)
    {
        return std::tie(width, height) == std::tie(size.width, size.height);
    }

    bool operator<(const Size2<T>& size)
    {
        return std::tie(width, height) < std::tie(size.width, size.height);
    }

    T width;
    T height;
};
}
