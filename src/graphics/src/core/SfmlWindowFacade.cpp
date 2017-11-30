#include "SfmlWindowFacade.hpp"

namespace graphics
{
SfmlWindowFacade::SfmlWindowFacade(const WindowSize& ,
                                   const std::string& )
    // : window{sf::VideoMode{size.width, size.height}, title}
{
    // window.create(sf::VideoMode{size.width, size.height}, title);
}
bool SfmlWindowFacade::is_open() const
{
    return window.isOpen();
}

void SfmlWindowFacade::display()
{
    window.display();
}

bool SfmlWindowFacade::poll_event(sf::Event& event)
{
    return window.pollEvent(event);
}

void SfmlWindowFacade::close()
{
    return window.close();
}

void SfmlWindowFacade::create(sf::VideoMode mode, const sf::String& title)
{
    return window.create(mode, title);
}
}
