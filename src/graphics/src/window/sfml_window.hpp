#pragma once

#include <memory>

#include "sfml/window_proxy.hpp"

#include "graphics/window.hpp"
#include "graphics/window_size.hpp"

namespace graphics
{
class sfml_window : public window
{
public:
    sfml_window(const window_size&, const std::string&,
                std::unique_ptr<window_proxy>);

    bool is_open() const override;
    void display() override;
    void update() override;
    window_size get_window_size() const override;

private:
    std::unique_ptr<window_proxy> m_window;
};
}
