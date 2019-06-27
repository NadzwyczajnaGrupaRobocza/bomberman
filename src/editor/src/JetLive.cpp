#include "HotReload.hpp"

#include <SFML/Window/Event.hpp>
#include <jet/live/Live.hpp>

#include <iostream>
#include <memory>

namespace editor
{
class Logger : public jet::ILiveListener
{
public:
    void onLog(const jet::LogSeverity severity, const std::string& log)
    {
        switch(severity)
        {
          case jet::LogSeverity::kInfo:
              std::clog << "[I]";
              break;

          case jet::LogSeverity::kWarning:
              std::clog << "[W]";
              break;

          case jet::LogSeverity::kError:
              std::clog << "[E]";
              break;

          // case jet::LogSeverity::kDebug:
          //     std::clog << "[D]";
          //     break;

          default:
              return;
        }
        std::clog << ": " << log << "\n";
    }
};
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
    jet::Live hot_reload{std::make_unique<Logger>()};
    bool reloading{false};
};

std::unique_ptr<HotReload> create_hot_reload()
{
    return std::make_unique<JetLive>();
}
}
