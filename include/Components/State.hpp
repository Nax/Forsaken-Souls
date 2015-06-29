#ifndef STATE_COMPONENT_HPP
#define STATE_COMPONENT_HPP

#include <Lums>
#include "StateMachine.hpp"

namespace Component
{
    class State : public lm::Component
    {
        LUMS_COMPONENT
    public:
        State();
        void    init(lm::GameObject& go);
        void    setStateMachine(const lm::BValue& value);
        void    setMove(const lm::BValue& value);
        void    setAction(const lm::BValue& value);
        void    switchState(lm::GameObject& go, size_t message);
        ~State();

    private:
        size_t          _move;
        size_t          _action;
        StateMachine*   _stateMachine;
    };
}

#endif