#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <Lums>

namespace Component
{
    class Sprite : public lm::Component
    {
        LUMS_COMPONENT

    public:
        Sprite();
        lm::Sprite&     sprite();
        void            setTexture(const lm::BValue& value);
        ~Sprite();

    private:
        lm::Sprite      _sprite;
    };
}

#endif























