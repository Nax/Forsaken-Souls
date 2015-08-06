#ifndef BOT_SCRIPT_HPP
#define BOT_SCRIPT_HPP

#include <Lums>

namespace Script
{
    class Bot : public lm::Component
    {
        LUMS_COMPONENT

    public:
        void    update(lm::GameObject& object);
    };
}

#endif
