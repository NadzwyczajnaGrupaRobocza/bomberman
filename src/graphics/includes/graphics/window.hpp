#pragma once

#include <functional>

#include "graphics/window_event.hpp"
#include "graphics/window_size.hpp"

namespace graphics
{
class window
{
public:
    virtual ~window() noexcept = default;

    [[nodiscard]] virtual auto is_open() const -> bool = 0;

    virtual auto display() -> void = 0;
    virtual auto update() -> void = 0;
    virtual auto subscribe(window_event_callback) -> void = 0;
    virtual auto close() -> void = 0;

    [[nodiscard]] virtual auto get_window_size() const -> window_size = 0;
};
}
