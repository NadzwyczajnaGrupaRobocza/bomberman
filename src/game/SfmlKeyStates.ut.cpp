#include <gtest/gtest.h>

#include "SfmlKeyStates.hpp"

using namespace ::testing;

class SfmlKeyStatesTest : public Test
{
public:
    SfmlKeyStates states{};
    SfmlWindowEventObserver& event_observer = states;
    KeyStates& key_states = states;
};

TEST_F(SfmlKeyStatesTest, byDefaultAllKeyShouldNotBePressed)
{
    for (const auto& key : supported_keys)
    {
        EXPECT_FALSE(key_states.was_pressed(key));
        EXPECT_FALSE(key_states.is_pressed(key));
    }
}

TEST_F(SfmlKeyStatesTest, byDefaultAllKeyShouldNotBeReleased)
{
    for (const auto& key : supported_keys)
    {
        EXPECT_FALSE(key_states.was_released(key));
    }
}

TEST_F(SfmlKeyStatesTest, afterPressedButtonItShouldBePressed)
{
    sf::Event event{};
    event.type = sf::Event::KeyPressed;
    event.key = sf::Event::KeyEvent{sf::Keyboard::Key::A};

    event_observer.update(event);

    EXPECT_TRUE(key_states.was_pressed(KeyboardKey::A));
    EXPECT_TRUE(key_states.is_pressed(KeyboardKey::A));

    // for (const auto& key : supported_keys)
    // {
    //     // event_observer.update(event);

    //     EXPECT_TRUE(key_states.was_pressed(key));
    //     EXPECT_TRUE(key_states.is_pressed(key));
    // }
}
