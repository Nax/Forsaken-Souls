#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Player.hpp"
#include "Map.hpp"

namespace Phys
{
    void    updatePlayer(Player& p, const Map& map);
    void    updatePosition(Player& p);
    void    applyGravity(Player& p);
    void    checkCollisionY(Player& p, const Map& map, float* dy);
    void    checkCollisionX(Player& p, const Map& map, float* dx);
}

#endif