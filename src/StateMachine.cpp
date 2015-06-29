#include "StateMachine.hpp"

StateMachine::StateMachine()
{

}

void
StateMachine::loadBinary(const lm::BObject& object)
{
    for (auto move : object["moves"].asObject())
    {
        size_t moveKey = lm::sym(move.first);
        for (auto message : move.second.asObject())
        {
            size_t messageKey = lm::sym(message.first);
            for (auto action : message.second.asObject())
            {
                size_t actionKey = lm::sym(action.first);
                size_t value = lm::sym(action.second.asString());
                _moves[moveKey][actionKey][messageKey] = value;
            }
        }
    }

    for (auto action : object["actions"].asObject())
    {
        size_t actionKey = lm::sym(action.first);
        for (auto message : action.second.asObject())
        {
            size_t messageKey = lm::sym(message.first);
            size_t value = lm::sym(message.second.asString());
            _actions[actionKey][messageKey] = value;
        }
    }
}

size_t
StateMachine::switchMove(size_t move, size_t action, size_t message)
{
    auto& moveMap = _moves[move][action];
    auto newMove = moveMap.find(message);
    if (newMove == moveMap.end())
        return move;
    return newMove->second;
}

size_t
StateMachine::switchAction(size_t action, size_t message)
{
    auto& actionMap = _actions[action];
    auto newAction = actionMap.find(message);
    if (newAction == actionMap.end())
        return action;
    return newAction->second;
}

StateMachine::~StateMachine()
{

}