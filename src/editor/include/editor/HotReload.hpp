#pragma once

#include <memory>

namespace editor
{
class HotReload
{
public:
    virtual ~HotReload() = default;
    virtual void update() = 0;
};

std::unique_ptr<HotReload> create_hot_reload();
}
