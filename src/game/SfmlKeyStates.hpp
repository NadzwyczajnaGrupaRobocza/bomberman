#pragma once

#include <map>
#include <optional>

#include "KeyStates.hpp"
#include "SfmlWindowEventTarget.hpp"

enum class KeyState
{
    Released,
    Pressed,
    Unknown
};

class SfmlKeyStates : public KeyStates, public SfmlWindowEventTarget
{
public:
    void update();

    bool is_pressed(KeyboardKey) override;
    bool is_released(KeyboardKey) override;
    bool was_pressed(KeyboardKey) override;
    bool was_released(KeyboardKey) override;

    void on_event(sf::Event) override;

private:
    std::map<KeyboardKey, KeyState> current_key_states{};
    std::map<KeyboardKey, std::optional<KeyState>> last_frame_key_states{};
};
