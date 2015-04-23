#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "IEntity.hpp"
#include "Map.hpp"

namespace Phys
{
    void    updateEntity(IEntity& e, const Map& map);
    void    applyGravity(IEntity& e);
    void    checkCollisionX(IEntity& e, const Map& map);
    void    checkCollisionY(IEntity& e, const Map& map);
    void	checkDamages(IEntity& attacker, IEntity& target);
}

#endif