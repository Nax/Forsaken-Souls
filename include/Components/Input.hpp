#ifndef COMPONENTS_INPUT_HPP
#define COMPONENTS_INPUT_HPP

#include <Lums>

namespace Component
{
    class Input : public lm::Component
    {
        LUMS_COMPONENT

    public:
        Input();
        ~Input();

        bool    left:1;
        bool    right:1;
        bool    jump:1;
        bool    crouch:1;
        bool    meleeAttack:1;
        bool    rangeAttack:1;
    };
}

#endif
