#ifndef COMPONENTS_MOVABLE_HPP
#define COMPONENTS_MOVABLE_HPP

#include <Lums>

namespace Component
{
    class Movable : public lm::Component
    {
        LUMS_COMPONENT

    public:
        Movable();
        ~Movable();

        lm::Vector2f    _speed;
    };
}

#endif