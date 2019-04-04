#pragma once

#include "graphics/window.hpp"

#include <memory>

#include "window_size.hpp"
#include "sfml/window_proxy.hpp"

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

private:
    std::unique_ptr<window_proxy> m_window;
};
}
