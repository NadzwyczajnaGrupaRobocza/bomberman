#pragma once

#include "KeyStates.hpp"
#include "SfmlWindowEventObserver.hpp"

class SfmlKeyStates : public KeyStates, public SfmlWindowEventObserver
{
public:
    void next_frame() override;
    void update(sf::Event) override;

    bool is_pressed(KeyboardKey) override;
    bool was_pressed(KeyboardKey) override;
    bool was_released(KeyboardKey) override;
};
