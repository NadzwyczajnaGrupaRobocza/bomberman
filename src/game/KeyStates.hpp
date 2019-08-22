#pragma once

#include <array>

enum class KeyboardKey
{
    W,
    S,
    A,
    D,
    SPC
};

constexpr std::array supported_keys{KeyboardKey::W, KeyboardKey::S,
                                    KeyboardKey::A, KeyboardKey::D,
                                    KeyboardKey::SPC};

class KeyStates
{
public:
    virtual ~KeyStates() = default;
    virtual bool is_pressed(KeyboardKey) = 0;
    virtual bool was_pressed(KeyboardKey) = 0;
    virtual bool was_released(KeyboardKey) = 0;
};
