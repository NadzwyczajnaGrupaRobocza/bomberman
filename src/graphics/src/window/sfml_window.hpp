#pragma once

#include <memory>

#include "sfml/window_proxy.hpp"

#include "boost/optional.hpp"
#include "graphics/window.hpp"
#include "graphics/window_change_observer.hpp"
#include "graphics/window_size.hpp"

namespace graphics
{
class sfml_window : public window
{
public:
    sfml_window(const window_size&, const std::string&,
                std::unique_ptr<window_proxy>, window_change_observer&);
    sfml_window(const window_size&, const std::string&,
                std::unique_ptr<window_proxy>);

    bool is_open() const override;
    void display() override;
    void update() override;
    void subscribe(window_event_callback) override;

private:
    sfml_window(const window_size&, const std::string&,
                std::unique_ptr<window_proxy>,
                boost::optional<window_change_observer&>);

    window_size get_window_size() const;

    std::unique_ptr<window_proxy> m_window;
    boost::optional<window_change_observer&> change_observer;

    boost::optional<window_event_callback> callback;
};
}
