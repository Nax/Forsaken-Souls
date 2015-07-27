#ifndef SYSTEMS_PHYSICS_HPP
#define SYSTEMS_PHYSICS_HPP

#include <vector>
#include <Lums>
#include "Components/Movable.hpp"
#include "Components/Collidable.hpp"
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
        void    move(lm::GameObject& go, Component::Movable& movable);
        void    collide(lm::GameObject& go, Component::Collidable& collidable, const Map& map);
    };
}

#endif