#include "math/Size2f.hpp"
#include "math/Size2i.hpp"

constexpr auto field_width = 11;
constexpr auto field_height = 21;

constexpr auto field_size = math::Size2i{field_width, field_height};
constexpr auto field_size_f = math::Size2f{field_width, field_height};

template <typename Type>
Type scale_to_field_size(Type val)
{
    return {val.first * field_width, val.second * field_height};
}
