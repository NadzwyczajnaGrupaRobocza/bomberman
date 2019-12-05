#pragma once

#include <functional>
#include <variant>

namespace graphics
{
enum class key_state
{
    Unknown,
    Released,
    Pressed
};

enum class keyboard_key
{
    Unknown,
    W,
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

constexpr bool operator==(const keyboard_event& lhs, const keyboard_event& rhs)
{
    constexpr auto tie = [](const auto& event) {
        return std::tie(event.state, event.key);
    };

    return tie(lhs) == tie(rhs);
}

constexpr bool operator!=(const keyboard_event& lhs, const keyboard_event& rhs)
{
    return not(lhs == rhs);
}

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

struct window_event
{
public:
    window_event() = default;

    template <typename Event>
    window_event(Event&& event) : concrete_event{std::forward<Event>(event)}
    {
    }

    template <typename... Lambda>
    void dispatch(Lambda... lambda)
    {
        std::visit(overloaded{[](auto) {}, std::move(lambda)...},
                   concrete_event);
    }

private:
    struct uninitialized_event
    {
    };
    std::variant<uninitialized_event, keyboard_event, screen_event>
        concrete_event;
};

using window_event_callback = std::function<void(const window_event&)>;
}
