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
        Physics();
        void    update(std::vector<lm::GameObject*>& gameObjects, const Map& map); 
        ~Physics();

    private:
        void    move(lm::GameObject& go, Component::Physics& physics);
        void    collide(lm::GameObject& go, Component::Collider& collider, const Map& map);
    };
}

#endif