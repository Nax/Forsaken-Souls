#include "Components/Collider.hpp"

LUMS_REGISTER_COMPONENT(Component::Collider, "collider");

LUMS_BIND_SETTER("collider", "box", &Component::Collider::setBox);

// LUMS_BIND_MESSAGE("collidable", "state_change", &Component::Collidable::onStateChange);

// LUMS_BIND_MESSAGE("movable", "direction", &Component::Movable::onDirectionChange);

using namespace Component;

void
Collider::init(lm::GameObject& object)
{
    collidedObject = nullptr;
}

void
Collider::setBox(const lm::BValue& value)
{
    const auto& array = value.asArray(); 
    boundingBox = {{array[0].asFloat(), array[1].asFloat()}, {array[2].asFloat(), array[3].asFloat()}};
}
