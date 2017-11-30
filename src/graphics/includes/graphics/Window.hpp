#pragma once

namespace graphics
{
class Window
{
public:
    Window() = default; // Q: Is it a good idea
                        // to add default constructors to Interface
    Window(const Window&) = default;
    Window(Window&&) = default;
    virtual ~Window() noexcept = default;

    virtual bool is_open() const = 0;
    virtual void display() = 0;
    virtual void update() = 0;
};
}
