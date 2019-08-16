#pragma once

#include <boost/operators.hpp>
#include <ostream>
#include <tuple>
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

namespace
{
template <typename>
struct to_int_type
{
    using type = int;
};
}

template <typename T, typename CompareType,
          typename to_int_type<decltype(CompareType::x)>::type = 0>
bool operator==(const Size2<T>& lhs, const CompareType& rhs)
{
    const auto tie = [](const Size2<T>& size) {
        return std::tie(size.width, size.height);
    };
    const auto tieCompare = [](const CompareType& size) {
        return std::tie(size.x, size.y);
    };
    return tie(lhs) == tieCompare(rhs);
}
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const math::Size2<T>& size)
{
    return out << "Size2<" << typeid(T).name() << ">{width:" << size.width
               << ", "
               << "height:" << size.height << "}\n";
}
