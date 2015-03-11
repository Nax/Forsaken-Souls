#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Player.hpp"
#include "Map.hpp"

namespace Phys
{
    void    updatePlayer(Player& p, const Map& map);
    void    checkGrounded(Player &p, const Map& map);
    void    updatePlayerStence(Player &p);
    void    setPlayerTransition(Player &p);
    void    setPlayerAnimation(Player &p);
    void    updatePlayerSpeed(Player &p, bool moving);
    void    updatePlayerPosition(Player &p, const Map& map);
}

#endif