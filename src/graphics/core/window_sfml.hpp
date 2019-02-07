#pragma once

#include "graphics/window.hpp"

#include <memory>

#include "window_size.hpp"
#include "sfml_window.hpp"

namespace graphics
{
class window_sfml : public window
{
public:
    window_sfml(const window_size&, const std::string&,
                std::unique_ptr<sfml_window>);

    bool is_open() const override;
    void display() override;
    void update() override;

private:
    std::unique_ptr<sfml_window> window;
};
}
