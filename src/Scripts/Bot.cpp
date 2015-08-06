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

    lm::GameObject* player = lm::GameObjectSet::instance().getObjectByTag("player");

    if (player)
    {
        if (player->position.x > object.position.x)
        {
            physics->speed.x = 6.0f;
            skeleton->skeleton().setFlip(true);
        }
        else
        {
            physics->speed.x = -6.0f;
            skeleton->skeleton().setFlip(false);
        }
        skeleton->skeleton().setAnimation("Run", true);
    }
}

