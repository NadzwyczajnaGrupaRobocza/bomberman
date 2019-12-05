#include <gtest/gtest.h>

#include "graphics/window_event.hpp"

using namespace ::testing;

namespace graphics
{

TEST(keyboard_event_compare_test,
     default_initialized_events_are_equal_unknown_event)
{
    keyboard_event uninitialized_event1{};
    keyboard_event unknown_event{key_state::Unknown, keyboard_key::Unknown};

    EXPECT_TRUE(uninitialized_event1 == unknown_event);
}

TEST(keyboard_event_compare_test, default_initialized_events_are_equal)
{
    keyboard_event uninitialized_event1{};
    keyboard_event uninitialized_event2{};

    EXPECT_TRUE(uninitialized_event1 == uninitialized_event2);
    EXPECT_FALSE(uninitialized_event1 != uninitialized_event2);
}

TEST(keyboard_event_compare_test,
     two_event_with_different_key_state_only_are_not_equal)
{
    keyboard_event released_spc_event{key_state::Released, keyboard_key::SPC};
    keyboard_event pressed_spc_event{key_state::Pressed, keyboard_key::SPC};

    EXPECT_FALSE(released_spc_event == pressed_spc_event);
    EXPECT_TRUE(released_spc_event != pressed_spc_event);
}

TEST(keyboard_event_compare_test,
     two_event_with_different_keyboard_key_only_are_not_equal)
{
    keyboard_event pressed_d_event{key_state::Pressed, keyboard_key::D};
    keyboard_event pressed_spc_event{key_state::Pressed, keyboard_key::SPC};

    EXPECT_FALSE(pressed_d_event == pressed_spc_event);
    EXPECT_TRUE(pressed_d_event != pressed_spc_event);
}

TEST(keyboard_event_compare_test, two_different_events_are_not_equal)
{
    keyboard_event uninitialized_event{};
    keyboard_event released_d_event{key_state::Released, keyboard_key::D};
    keyboard_event pressed_spc_event{key_state::Pressed, keyboard_key::SPC};

    EXPECT_FALSE(uninitialized_event == released_d_event);
    EXPECT_FALSE(uninitialized_event == pressed_spc_event);
    EXPECT_FALSE(released_d_event == pressed_spc_event);
}

TEST(keyboard_event_compare_test, two_equal_events_are_equal)
{
    keyboard_event released_w_event1{key_state::Released, keyboard_key::W};
    keyboard_event released_w_event2{key_state::Released, keyboard_key::W};

    EXPECT_TRUE(released_w_event1 == released_w_event2);
}

struct window_event_test : Test
{
};

struct window_event_test_dispatch_emtpy_event : window_event_test
{
};

TEST_F(window_event_test_dispatch_emtpy_event, do_nothing)
{
    bool screen_event_triggered{false};
    bool keyboard_event_triggered{false};

    window_event event{};
    event.dispatch(
        [&](const screen_event&) { screen_event_triggered = true; },
        [&](const keyboard_event&) { keyboard_event_triggered = true; });

    EXPECT_FALSE(screen_event_triggered);
    EXPECT_FALSE(keyboard_event_triggered);
}

struct window_event_test_dispatch_non_emtpy_event : window_event_test
{
};

TEST_F(window_event_test_dispatch_non_emtpy_event, call_proper_callback)
{
    bool screen_event_triggered{false};
    bool keyboard_event_triggered{false};

    window_event event{screen_event::Resize};
    event.dispatch(
        [&](const screen_event&) { screen_event_triggered = true; },
        [&](const keyboard_event&) { keyboard_event_triggered = true; });

    EXPECT_TRUE(screen_event_triggered);
    EXPECT_FALSE(keyboard_event_triggered);
}

TEST_F(window_event_test_dispatch_non_emtpy_event,
       resize_event_properly_catched)
{
    auto catched_event = screen_event::Unknown;
    auto expected_event = screen_event::Resize;

    window_event{expected_event}.dispatch(
        [&](const screen_event& event) { catched_event = event; });

    EXPECT_EQ(expected_event, catched_event);
}

TEST_F(window_event_test_dispatch_non_emtpy_event,
       unknown_event_properly_catched)
{
    auto catched_event = screen_event::Resize;
    auto expected_event = screen_event::Unknown;

    window_event{expected_event}.dispatch(
        [&](const screen_event& event) { catched_event = event; });

    EXPECT_EQ(expected_event, catched_event);
}

TEST_F(window_event_test_dispatch_non_emtpy_event,
       keyboard_event_properly_catched)
{
    auto catched_event = keyboard_event{};
    auto expected_event = keyboard_event{key_state::Pressed, keyboard_key::A};

    window_event{expected_event}.dispatch(
        [&](const keyboard_event& event) { catched_event = event; });

    EXPECT_EQ(expected_event, catched_event);
}

}
