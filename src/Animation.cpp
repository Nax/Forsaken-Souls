#include "Animation.hpp"

Animation::Animation()
{

}

void
Animation::loadBinary(const lm::BObject& object)
{
    for (auto moves : object["animations"].asObject())
    {
        size_t move = lm::sym(moves.first);
        for (auto actions : moves.second.asObject())
        {
            size_t action = lm::sym(actions.first);
            auto& anim = actions.second.asArray();
            auto& a = _animations[move][action];
            a.start = anim[0].asInt();
            a.length = anim[1].asInt();
            a.speed = anim[2].asInt();
            a.repeat = anim[3].asInt();
        }
    }
}

Animation::Data&
Animation::animation(size_t move, size_t action)
{
    return _animations[move][action];
}

Animation::~Animation()
{

}
