#ifndef BOT_SCRIPT_HPP
#define BOT_SCRIPT_HPP

#include <Lums>

namespace Script
{
    class Bot : public lm::Component
    {
        LUMS_COMPONENT

    public:
        enum class TargetType
        {
            None,
            Walk,
            Jump,
            Fall
        };

        void    init(lm::GameObject& object);
        void    update(lm::GameObject& object);
        void    findPath(lm::GameObject& object);

    private:
        lm::Vector2f    _target;
        bool            _targeting;
        TargetType      _targetType;
        float           _lastTargetDist;
    };
}

#endif
