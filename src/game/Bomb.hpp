#include "Entity.hpp"

class Bomb : public Entity
{
public:
    [[nodiscard]] virtual auto hasExploded() const -> bool = 0;
};
