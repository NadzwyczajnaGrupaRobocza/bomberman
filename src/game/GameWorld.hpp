#pragma once

class GameWorld
{
public:

    virtual bool is_bomb_at_pos(const BombPosition&) const = 0;

    virtual void register_bomb(BombPosition, std::unique_ptr<Bomb>) = 0;
    virtual void register_explosion(ExplosionPosition, std::unique_ptr<Explosion>) = 0;

    virtual void update(ElapsedTime) = 0;
    virtual ~GameWorld() = default;
};
