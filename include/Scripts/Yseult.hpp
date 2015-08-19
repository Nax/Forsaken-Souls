#ifndef YSEULT_SCRIPT_HPP
#define YSEULT_SCRIPT_HPP

#include <Lums>

namespace Script
{
    class Yseult : public lm::Component
    {
        enum
        {
            NoAttack,
            MeleeAttack,
            RangedAttack
        };

        LUMS_COMPONENT

    public:
        void    update(lm::GameObject& object);
        void    updateAnimation(lm::GameObject& object);

    private:
        int     attackAcc = 0;
        int     attackType = NoAttack;
    };
}

#endif
