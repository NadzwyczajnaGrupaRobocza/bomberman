#pragma once

#include "window_size.hpp"

namespace graphics
{
class window
{
public:
    virtual ~window() noexcept = default;

    virtual bool is_open() const = 0;
    virtual void display() = 0;
    virtual void update() = 0;
    virtual window_size get_window_size() const = 0;
};
}
