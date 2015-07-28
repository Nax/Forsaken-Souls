#include "Body.hpp"

void
Body::loadBinary(const lm::BObject& object)
{
    for (auto& moves : object["bodies"].asObject())
    {
        size_t move = lm::sym(moves.first);
        for (auto& actions : moves.second.asObject())
        {
            size_t action = lm::sym(actions.first);
            auto& obj = actions.second.asObject();
            auto& speed = obj["speed"].asArray();
            auto& impulse = obj["impulse"].asArray();
            _bodies[move][action] = {{speed[0].asFloat(), speed[1].asFloat()}, {impulse[0].asFloat(), impulse[1].asFloat()}};
        }
    }
}

Body::Data&
Body::body(size_t move, size_t action)
{
    return _bodies[move][action];
}
