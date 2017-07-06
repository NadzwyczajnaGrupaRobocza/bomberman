#include "Entity.hpp"

class Bomb : public Entity
{
public:
    virtual bool hasExploded() const = 0;
};
