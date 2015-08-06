#include "Scripts/Bot.hpp"
#include "Components/Physics.hpp"
#include "Components/Skeleton.hpp"

#include <cmath>

LUMS_REGISTER_COMPONENT(Script::Bot, "script_bot");

using namespace Script;

void
Bot::update(lm::GameObject& object)
{
    auto* physics = object.getComponent<::Component::Physics>("physics");
    auto* skeleton = object.getComponent<::Component::Skeleton>("skeleton");

    physics->speed.x = 1.0f;
    skeleton->skeleton().setAnimation("Run", true);
    skeleton->skeleton().setFlip(true);
}

