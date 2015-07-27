#ifndef COMPONENTS_MOVABLE_HPP
#define COMPONENTS_MOVABLE_HPP

#include <Lums>
#include "Body.hpp"

namespace Component
{
    class Movable : public lm::Component
    {
        LUMS_COMPONENT

    public:
        Movable();
        void        setBody(const lm::BValue& value);
        void        onStateChange(lm::GameObject& go, size_t move, size_t action);
        void        onDirectionChange(lm::GameObject& go, int direction);

        ~Movable();

        lm::Vector2f    speed;
        Body*           body;
        Body::Data*     data;
        bool            direction;
        bool            moving;
    };
}

#endif