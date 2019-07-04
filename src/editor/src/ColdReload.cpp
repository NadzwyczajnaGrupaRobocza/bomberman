#include "HotReload.hpp"

namespace editor
{
class ColdReload : public HotReload
{
public:
    void update() override
    {
    }
};

std::unique_ptr<HotReload> create_hot_reload()
{
    return std::make_unique<ColdReload>();
}
}
