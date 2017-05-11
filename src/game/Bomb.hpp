#include "Entity.hpp"

class Bomb : public Entity
{
public:
    void update(std::chrono::milliseconds) override;
    bool areYouDead() const override;
    bool hasExploded() const;
private:
    bool exploded{false};
    const std::chrono::seconds bombTimer{3};
};


