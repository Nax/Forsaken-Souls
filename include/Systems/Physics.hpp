#ifndef SYSTEMS_PHYSICS_HPP
#define SYSTEMS_PHYSICS_HPP

#include <vector>
#include <Lums>
#include "Components/Physics.hpp"
#include "Components/Collider.hpp"
#include "Map.hpp"

namespace System
{
    class Physics
    {
    public:
        void    update(const Map& map);
    };
}

#endif