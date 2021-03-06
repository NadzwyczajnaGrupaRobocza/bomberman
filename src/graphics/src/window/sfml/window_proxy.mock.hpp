#pragma once

#include <gmock/gmock.h>

#include "window_proxy.hpp"

namespace graphics
{
class mock_window_proxy : public window_proxy
{
public:
    MOCK_CONST_METHOD0(is_open, bool());
    MOCK_METHOD0(display, void());
    MOCK_METHOD1(poll_event, bool(sf::Event&));
    MOCK_METHOD0(close, void());
    MOCK_METHOD2(create, void(sf::VideoMode, const sf::String&));
    MOCK_CONST_METHOD0(get_window_size, window_size());
};
}
