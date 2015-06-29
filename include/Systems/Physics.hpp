#ifndef SYSTEMS_PHYSICS_HPP
#define SYSTEMS_PHYSICS_HPP

#include <vector>
#include <Lums>
#include "Components/Movable.hpp"

namespace System
{
    class Physics
    {
    public:
        Physics();
        void    update(std::vector<lm::GameObject*>& gameObjects); 
        ~Physics();

    private:
        void    move(lm::GameObject& go, Component::Movable& movable);
    };
}

#endif