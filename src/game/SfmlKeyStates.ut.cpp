#include <gtest/gtest.h>

#include "SfmlKeyStates.hpp"

using namespace ::testing;

class SfmlKeyStatesTest : public Test
{
public:
    const bool altKeyUnpressed{false};
    const bool controlKeyUnpressed{false};
    const bool shiftKeyUnpressed{false};
    const bool systemKeyUnpressed{false};

    sf::Event createEvent(sf::Event::EventType type, sf::Keyboard::Key key)
    {
        sf::Event event{};
        event.type = type;
        event.key =
            sf::Event::KeyEvent{key, altKeyUnpressed, controlKeyUnpressed,
                                shiftKeyUnpressed, systemKeyUnpressed};

        return event;
    }

    SfmlKeyStates states{};
    SfmlWindowEventTarget& event_observer = states;
    KeyStates& key_states = states;
};

TEST_F(SfmlKeyStatesTest, byDefault_allKeyShouldNotBePressed)
{
    for (const auto& key : supported_keys)
    {
        EXPECT_FALSE(key_states.was_pressed(key));
        EXPECT_FALSE(key_states.is_pressed(key));
    }
}

TEST_F(SfmlKeyStatesTest, byDefault_allKeyShouldNotBeReleased)
{
    for (const auto& key : supported_keys)
    {
        EXPECT_FALSE(key_states.was_released(key));
    }
}

TEST_F(SfmlKeyStatesTest, afterPressedButton_itShouldBePressed)
{
    event_observer.on_event(
        createEvent(sf::Event::KeyPressed, sf::Keyboard::Key::A));

    EXPECT_TRUE(key_states.was_pressed(KeyboardKey::A));
    EXPECT_FALSE(key_states.was_released(KeyboardKey::A));
    EXPECT_TRUE(key_states.is_pressed(KeyboardKey::A));
    EXPECT_FALSE(key_states.is_released(KeyboardKey::A));
}

TEST_F(SfmlKeyStatesTest, afterReleasedButton_itShouldBeReleased)
{
    event_observer.on_event(
        createEvent(sf::Event::KeyPressed, sf::Keyboard::Key::A));
    event_observer.on_event(
        createEvent(sf::Event::KeyReleased, sf::Keyboard::Key::A));

    EXPECT_FALSE(key_states.was_pressed(KeyboardKey::A));
    EXPECT_TRUE(key_states.was_released(KeyboardKey::A));
    EXPECT_FALSE(key_states.is_pressed(KeyboardKey::A));
    EXPECT_TRUE(key_states.is_released(KeyboardKey::A));
}

TEST_F(SfmlKeyStatesTest, keyInformationFor_WasCommand_inTheNextFrame_isCleared)
{
    event_observer.on_event(
        createEvent(sf::Event::KeyPressed, sf::Keyboard::Key::A));

    event_observer.on_event(
        createEvent(sf::Event::KeyReleased, sf::Keyboard::Key::W));

    states.update();

    EXPECT_FALSE(key_states.was_pressed(KeyboardKey::A));
    EXPECT_FALSE(key_states.was_released(KeyboardKey::W));
}

TEST_F(SfmlKeyStatesTest, keyInformationFor_IsCommand_inTheNextFrame_isKeept)
{
    event_observer.on_event(
        createEvent(sf::Event::KeyPressed, sf::Keyboard::Key::A));

    event_observer.on_event(
        createEvent(sf::Event::KeyReleased, sf::Keyboard::Key::W));

    states.update();

    EXPECT_TRUE(key_states.is_pressed(KeyboardKey::A));
    EXPECT_TRUE(key_states.is_released(KeyboardKey::W));
}
