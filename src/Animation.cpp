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
            size_t anim = lm::sym(actions.second.asArray()[0].asString());
            bool loop = actions.second.asArray()[1].asInt();
            _animations[move][action] = Data{anim, loop};
        }
    }
}

const Animation::Data&
Animation::animation(size_t move, size_t action)
{
    return _animations[move][action];
}

Animation::~Animation()
{

}
