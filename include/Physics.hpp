#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "IEntity.hpp"
#include "Map.hpp"

namespace Phys
{
    void    updateEntity(IEntity& e, const Map& map);
    void    updatePosition(IEntity& e);
    void    updateStance(IEntity& e);
    void    updateSpeed(IEntity& e);
    void    applyGravity(IEntity& e);
    void    checkCollisionX(IEntity& e, const Map& map);
    void    checkCollisionY(IEntity& e, const Map& map);
}

#endif