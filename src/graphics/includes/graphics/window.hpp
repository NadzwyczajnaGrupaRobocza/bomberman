#pragma once

#include <functional>

#include "graphics/window_size.hpp"
#include "graphics/window_event.hpp"

namespace graphics
{
class window
{
public:
    virtual ~window() noexcept = default;

    virtual bool is_open() const = 0;
    virtual void display() = 0;
    virtual void update() = 0;
    virtual void subscribe(window_event_callback) = 0;
};
}
