#include "Components/Actor.hpp"

using namespace Component;

void
Actor::init(lm::GameObject& object)
{
    direction = false;
    dead = false;
    knockBack = false;
}

void
Actor::setHealth(const BValue& value)
{
    maxHealth = value.asInt();
}