#pragma once

#include <functional>
#include <variant>

namespace graphics
{
enum class key_state
{
    Released,
    Pressed,
    Unknown
};

enum class keyboard_key
{
    Unknown = -1,
    W = 0,
    S,
    A,
    D,
    SPC
};

struct keyboard_event
{
    key_state state;
    keyboard_key key;
};

enum class screen_event
{
    Unknown = -1,
    Resize = 0
};

template <class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...)->overloaded<Ts...>;

class window_event
{
public:
    template <typename Lambda>
    void dispatch(Lambda lambda)
    {
        std::visit(overloaded{[](auto) {}, lambda}, concrete_event);
    }

private:
    std::variant<keyboard_event, screen_event> concrete_event;
};

using window_event_callback = std::function<void(window_event)>;
}
