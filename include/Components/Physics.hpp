#ifndef COMPONENTS_PHYSICS_HPP
#define COMPONENTS_PHYSICS_HPP

#include <Lums>

namespace Component
{
    class Physics : public lm::Component
    {
        LUMS_COMPONENT

    public:
        void    init(lm::GameObject& object);

        lm::Vector2f    speed;
        bool            grounded;
    };
}

#endif