#ifndef COMPONENTS_COLLIDER_HPP
#define COMPONENTS_COLLIDER_HPP

#include <Lums>

namespace Component
{
    class Collider : public lm::Component
    {
        LUMS_COMPONENT

    public:
        void    init(lm::GameObject& object);
        void    setBox(const lm::BValue& value);

        lm::Rect2f           boundingBox;
        lm::GameObject*      collidedObject;
    };
}

#endif