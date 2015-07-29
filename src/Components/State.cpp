#include <iostream>

#include "Components/State.hpp"

LUMS_REGISTER_COMPONENT(Component::State, "state");

LUMS_BIND_SETTER("state", "state_machine", &Component::State::setStateMachine);
LUMS_BIND_SETTER("state", "move", &Component::State::setMove);
LUMS_BIND_SETTER("state", "action", &Component::State::setAction);

LUMS_BIND_MESSAGE("state", "switch_state", &Component::State::switchState);

using namespace Component;

State::State()
: _stateMachine(nullptr)
{

}

void
State::init(lm::GameObject& go)
{
    go.send("state_change", _move, _action);
}

void
State::setStateMachine(const lm::BValue& value)
{
    _stateMachine = &(StateMachineProvider::instance().get(value.asString()));
}

void
State::setMove(const lm::BValue& value)
{
    _move = lm::sym(value.asString());
}

void
State::setAction(const lm::BValue& value)
{
    _action = lm::sym(value.asString());
}

void
State::switchState(lm::GameObject& go, size_t message)
{
    if (_action == lm::sym("none") && (message == lm::sym("left") || message == lm::sym("right") || message == lm::sym("no_move")))
    {
        int direction = (message == lm::sym("left")) ? -1 : (message == lm::sym("right")) ? 1 : 0;
        go.send("direction", direction);
    }
    size_t newAction = _stateMachine->switchAction(_action, message);
    size_t newMove = _stateMachine->switchMove(_move, newAction, message);
    if (newMove != _move || newAction != _action)
    {
        go.send("state_change", newMove, newAction);
        _move = newMove;
        _action = newAction;
    }
}

State::~State()
{

}