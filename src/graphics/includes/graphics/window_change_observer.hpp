#pragma once

#include "graphics/window_size.hpp"

namespace graphics
{
class window_change_observer
{
public:
    virtual ~window_change_observer() noexcept = default;

    virtual void window_size_changed(const window_size& size) = 0;
};

}
