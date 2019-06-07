#include "HotReload.hpp"

#include <SFML/Window/Event.hpp>
#include <jet/live/Live.hpp>

namespace editor
{
class JetLive : public HotReload
{
public:
    void update() override
    {
        hot_reload.update();
        if (not reloading && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            hot_reload.tryReload();
            reloading = true;
        }
        else if (not(sf::Keyboard::isKeyPressed(sf::Keyboard::R) &&
                     sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)))
        {
            reloading = false;
        }
    }

private:
    jet::Live hot_reload;
    bool reloading{false};
};

std::unique_ptr<HotReload> create_hot_reload()
{
    return std::make_unique<JetLive>();
}
}
