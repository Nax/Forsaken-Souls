#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Player.hpp"
#include "Map.hpp"

namespace Phys
{
    void    updatePlayer(Player& p, const Map& map);
    void    updatePosition(Player& p);
    void    updateStance(Player& p);
    void    updateSpeed(Player& p);
    void    applyGravity(Player& p);
    void    checkCollisionX(Player& p, const Map& map);
    void    checkCollisionY(Player& p, const Map& map);
}

#endif