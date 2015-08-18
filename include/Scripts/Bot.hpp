#ifndef BOT_SCRIPT_HPP
#define BOT_SCRIPT_HPP

#include <Lums>

namespace Script
{
    class Bot : public lm::Component
    {
        LUMS_COMPONENT

    public:
        static const int moveSpeed = 6.f;
        static const int jumpSpeed = 20.f;

        void    init(lm::GameObject& object);
        void    update(lm::GameObject& object);
        void    move(lm::GameObject& object);
        void    findPath(lm::GameObject& object);
        void    setAnimation(lm::GameObject& object);

    private:
        lm::Vector2f    _target;
        int             _targetType;
        bool            _targeting;
    };
}

#endif
