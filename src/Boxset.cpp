#include "Boxset.hpp"

void
BoxSet::loadBinary(const lm::BObject& object)
{
    for (auto& moves : object["bounding"].asObject())
    {
        for (auto& actions : moves.second.asObject())
        {
            auto& bb = actions.second.asArray();
            lm::Rect2f rect = {{bb[0].asFloat(), bb[1].asFloat()}, {bb[2].asFloat(), bb[3].asFloat()}};
            _boxes[lm::sym(moves.first)][lm::sym(actions.first)] = rect;
        }
    }
}

const lm::Rect2f&
BoxSet::boxes(size_t move, size_t action)
{
    return _boxes[move][action];
}