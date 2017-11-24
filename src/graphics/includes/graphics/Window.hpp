#pragma once

namespace graphics
{
class Window
{
public:
    virtual ~Window() noexcept = default;

    virtual bool is_open() const = 0;
    virtual void display() = 0;
    virtual void update() = 0;
};
}
