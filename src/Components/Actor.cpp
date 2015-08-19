#include "Components/Actor.hpp"

LUMS_REGISTER_COMPONENT(Component::Actor, "actor");

LUMS_BIND_SETTER("actor", "health", &Component::Actor::setHealth);

using namespace Component;

void
Actor::init(lm::GameObject& object)
{
    direction = false;
    dead = false;
    knockBack = false;
}

void
Actor::setHealth(const lm::BValue& value)
{
    health = maxHealth = value.asInt();
}
