#ifndef COMPONENTS_SPRITE_HPP
#define COMPONENTS_SPRITE_HPP

#include <Lums>
#include "Animation.hpp"

namespace Component
{
    class Sprite : public lm::Component
    {
        LUMS_COMPONENT

    public:
        Sprite();
        lm::Sprite&     sprite();
        void            setTexture(const lm::BValue& value);
        void            setAnimation(const lm::BValue& value);
        void            onStateChange(lm::GameObject& go, size_t move, size_t action);
        ~Sprite();

    private:
        lm::Sprite      _sprite;
        Animation*      _animation;
    };
}

#endif























