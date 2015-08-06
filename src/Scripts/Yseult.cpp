#include "Scripts/Yseult.hpp"
#include "Components/Input.hpp"
#include "Components/Physics.hpp"
#include "Components/Skeleton.hpp"
#include "Components/Actor.hpp"

#include <cmath>

LUMS_REGISTER_COMPONENT(Script::Yseult, "script_yseult");

using namespace Script;

void
Yseult::update(lm::GameObject& object)
{
    auto* input = object.getComponent<::Component::Input>("input");
    auto* physics = object.getComponent<::Component::Physics>("physics");
    auto* actor = object.getComponent<::Component::Actor>("actor");

    if (input->left && !input->right)
    {
        physics->speed.x = -10.f;
        actor->direction = false;
    }
    else if (!input->left && input->right)
    {
        physics->speed.x = 10.f;
        actor->direction = true;
    }
    else
        physics->speed.x = 0.f;
    if (input->jump && physics->grounded)
        physics->speed.y = 19.8f;
    updateAnimation(object);
}

void
Yseult::updateAnimation(lm::GameObject& object)
{
    auto* physics = object.getComponent<::Component::Physics>("physics");
    auto* skeleton = object.getComponent<::Component::Skeleton>("skeleton");
    auto* actor = object.getComponent<::Component::Actor>("actor");

    skeleton->skeleton().setFlip(actor->direction);
    if (!physics->grounded)
        skeleton->skeleton().setAnimation("Fall", false);
    else if (fabs(physics->speed.x) > 0.01f)
        skeleton->skeleton().setAnimation("Run", true);
    else
        skeleton->skeleton().setAnimation("Idle_Wait", true);
}

