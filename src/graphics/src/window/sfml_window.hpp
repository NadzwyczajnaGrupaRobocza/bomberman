#pragma once

#include <memory>

#include "boost/optional.hpp"
#include "graphics/window.hpp"
#include "graphics/window_change_observer.hpp"
#include "graphics/window_size.hpp"
#include "sfml/window_proxy.hpp"

namespace graphics
{
class sfml_window : public window
{
public:
    sfml_window(const window_size&, const std::string&,
                std::unique_ptr<window_proxy>, window_change_observer&);
    sfml_window(const window_size&, const std::string&,
                std::unique_ptr<window_proxy>);

    [[nodiscard]] auto is_open() const -> bool override;
    auto display() -> void override;
    auto update() -> void override;
    auto subscribe(window_event_callback) -> void override;
    auto close() -> void override;

    // TODO: add UT
    [[nodiscard]] auto get_window_size() const -> window_size override;

private:
    sfml_window(const window_size&, const std::string&,
                std::unique_ptr<window_proxy>,
                boost::optional<window_change_observer&>);

    std::unique_ptr<window_proxy> m_window;
    boost::optional<window_change_observer&> change_observer;

    boost::optional<window_event_callback> callback;
};
}
