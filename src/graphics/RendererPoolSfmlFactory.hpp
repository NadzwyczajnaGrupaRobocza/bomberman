#pragma once

#include "RendererPoolFactory.hpp"

namespace graphics
{
class RendererPoolSfmlFactory : public RendererPoolFactory
{
public:
    std::unique_ptr<RendererPool> create(const math::Size&) const override;
};
}
