#include <SFML/Window/Window.hpp>

#include "sfml/window_proxy.hpp"

#include "window_size.hpp"

namespace graphics
{
class sfml_window_proxy : public window_proxy
{
public:
    sfml_window_proxy(const window_size&, const std::string& title);
    bool is_open() const override;
    void display() override;
    bool poll_event(sf::Event&) override;
    void close() override;
    void create(sf::VideoMode, const sf::String& title) override;
    window_size get_size() const override;

private:
    sf::Window m_window;
};
}
