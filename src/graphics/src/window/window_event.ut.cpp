#include <gtest/gtest.h>

#include "graphics/window_event.hpp"

using namespace ::testing;

namespace graphics
{

class window_event_test : public Test
{
public:
};

TEST_F(window_event_test, dummy)
{
    window_event event;

    event.dispatch([](const screen_event){});

    EXPECT_FALSE(true);

}

}
