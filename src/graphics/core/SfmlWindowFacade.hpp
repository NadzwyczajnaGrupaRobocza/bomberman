#include "SfmlWindow.hpp"

#include <SFML/Window/Window.hpp>

#include "WindowSize.hpp"

namespace graphics
{
class SfmlWindowFacade : public SfmlWindow
{
public:
    SfmlWindowFacade(const WindowSize&, const std::string& title);
    bool is_open() const override;
    void display() override;
    bool poll_event(sf::Event&) override;
    void close() override;
    void create(sf::VideoMode, const sf::String& title) override;

private:
    sf::Window window;
};
}
