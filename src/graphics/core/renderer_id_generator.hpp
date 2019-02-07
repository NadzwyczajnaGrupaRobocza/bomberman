#pragma once

#include "graphics/renderer_id.hpp"

namespace graphics
{
class renderer_id_generator
{
public:
    virtual ~renderer_id_generator() noexcept = default;
    virtual renderer_id generate() const;
};
}
