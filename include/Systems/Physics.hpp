#ifndef SYSTEMS_PHYSICS_HPP
#define SYSTEMS_PHYSICS_HPP

#include <vector>
#include <Lums>

namespace System
{
    class Physics
    {
    public:
        Physics();
        void    operator()(std::vector<lm::GameObject*>& gameObjects); 
        ~Physics();
    };
}

#endif