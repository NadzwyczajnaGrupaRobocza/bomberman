#pragma once

#include "gmock/gmock.h"
#include "graphics/window_change_observer.hpp"

namespace graphics
{
class window_change_observer_mock : public window_change_observer
{
public:
    MOCK_METHOD1(window_size_changed, void(const window_size& size));
};

}
