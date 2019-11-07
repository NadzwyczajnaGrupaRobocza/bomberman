#include "SfmlKeyStates.hpp"

static KeyboardKey toKeyboardKey(const sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Key::W: return KeyboardKey::W;
    case sf::Keyboard::Key::S: return KeyboardKey::S;
    case sf::Keyboard::Key::A: return KeyboardKey::A;
    case sf::Keyboard::Key::D: return KeyboardKey::D;
    case sf::Keyboard::Key::Space: return KeyboardKey::SPC;

    default: return KeyboardKey::Unknown;
    }
}

static KeyState toKeyState(const sf::Event::EventType& event)
{
    switch (event)
    {
    case ::sf::Event::KeyPressed: return KeyState::Pressed;

    case ::sf::Event::KeyReleased: return KeyState::Released;

    default: return KeyState::Unknown;
    }
}

void SfmlKeyStates::update()
{
    last_frame_key_states.clear();
}

void SfmlKeyStates::on_event(sf::Event event)
{
    const auto keyState = toKeyState(event.type);
    const auto key = toKeyboardKey(event.key.code);

    if (keyState != KeyState::Unknown and key != KeyboardKey::Unknown)
    {
        current_key_states[key] = keyState;
        last_frame_key_states[key] = keyState;
    }
}

bool SfmlKeyStates::is_pressed(KeyboardKey key)
{
    return current_key_states[key] == KeyState::Pressed;
}

bool SfmlKeyStates::is_released(KeyboardKey key)
{
    return current_key_states[key] == KeyState::Released;
}

bool SfmlKeyStates::was_pressed(KeyboardKey key)
{
    return last_frame_key_states[key] == KeyState::Pressed;
}

bool SfmlKeyStates::was_released(KeyboardKey key)
{
    return last_frame_key_states[key] == KeyState::Released;
}
