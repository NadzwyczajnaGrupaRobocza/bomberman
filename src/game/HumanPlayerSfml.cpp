#include "HumanPlayerSfml.hpp"

#include <SFML/Graphics.hpp>
using kbd_access = sf::Keyboard;

VectorInt2D HumanPlayerSfml::get_direction() const
{
    VectorInt2D direction{0, 0};

    if (kbd_access::isKeyPressed(kbd_access::A))
    {
        direction += VectorInt2D{-1, 0};
    }
    if (kbd_access::isKeyPressed(kbd_access::D))
    {
        direction += VectorInt2D{1, 0};
    }
    if (kbd_access::isKeyPressed(kbd_access::W))
    {
        direction += VectorInt2D{0, -1};
    }
    if (kbd_access::isKeyPressed(kbd_access::S))
    {
        direction += VectorInt2D{0, 1};
    }
    return direction;
}

bool HumanPlayerSfml::wants_bomb() const
{
    return kbd_access::isKeyPressed(kbd_access::Space);
}
