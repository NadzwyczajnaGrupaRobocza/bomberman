#include "SfmlWindow.hpp"

#include <SFML/Window/Window.hpp>

namespace graphics
{
class SfmlWindowFacade : public SfmlWindow
{
public:
    bool is_open() const override;
    void display() override;
    bool poll_event(sf::Event&) override;
    void close() override;
    void create(sf::VideoMode, const sf::String& title) override;

private:
    sf::Window window;
};
}
