#pragma once

#include <boost/operators.hpp>
#include <tuple>
#include <ostream>
#include <typeinfo>

namespace math
{
template <typename T>
struct Size2 : boost::additive<Size2<T>>, boost::equality_comparable<Size2<T>>
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

    T width;
    T height;
};

template <typename T>
bool operator==(const Size2<T>& lhs, const Size2<T>& rhs)
{
    const auto tie = [](const Size2<T>& size) {
        return std::tie(size.width, size.height);
    };
    return tie(lhs) == tie(rhs);
}
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const math::Size2<T>& size)
{
    return out << "Size2<" << typeid(T).name() << ">{width:" << size.width
               << ", "
               << "height:" << size.height << "}\n";
}
