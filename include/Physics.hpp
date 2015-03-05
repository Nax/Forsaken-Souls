#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Player.hpp"

namespace Phys
{
    void    updatePlayer(Player& p);
    void    checkGrounded(Player &p);
    void    updatePlayerStence(Player &p);
    void    setPlayerTransition(Player &p);
    void    setPlayerAnimation(Player &p);
}

#endif