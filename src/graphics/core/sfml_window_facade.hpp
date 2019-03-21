#include "sfml_window.hpp"

#include <SFML/Window/Window.hpp>

#include "window_size.hpp"

namespace graphics
{
class sfml_window_facade : public sfml_window
{
public:
    sfml_window_facade(const window_size&, const std::string& title);
    bool is_open() const override;
    void display() override;
    bool poll_event(sf::Event&) override;
    void close() override;
    void create(sf::VideoMode, const sf::String& title) override;

private:
    sf::Window window;
};
}
