#ifndef COMPONENTS_COLLIDABLE_HPP
#define COMPONENTS_COLLIDABLE_HPP

#include <Lums>
#include "BoxSet.hpp"

namespace Component
{
    class Collidable : public lm::Component
    {
        LUMS_COMPONENT

    public:
        void    setBox(const lm::BValue& value);
        void    onStateChange(lm::GameObject& go, size_t move, size_t action);

        BoxSet*              box;
        const lm::Rect2f*    currentBox;
    };
}

#endif