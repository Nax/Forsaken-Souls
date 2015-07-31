#ifndef COMPONENT_ACTOR_HPP
#define COMPONENT_ACTOR_HPP

#include <Lums>

namespace Component
{
    class Actor : public lm::Component
    {
        LUMS_COMPONENT

    public:
        void    init(lm::GameObject& object);
        void    setHealth(const BValue& value);

        bool    direction:1;
        bool    dead:1;
        bool    knockBack:1;
        int     health;
        int     maxHealth;
    };
}

#endif