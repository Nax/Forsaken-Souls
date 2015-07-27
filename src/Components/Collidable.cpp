#include "Components/Collidable.hpp"

LUMS_REGISTER_COMPONENT(Component::Collidable, "collidable");

LUMS_BIND_SETTER("collidable", "box", &Component::Collidable::setBox);

LUMS_BIND_MESSAGE("collidable", "state_change", &Component::Collidable::onStateChange);

// LUMS_BIND_MESSAGE("movable", "direction", &Component::Movable::onDirectionChange);

using namespace Component;

void
Collidable::setBox(const lm::BValue& value)
{
    box = &(BoxProvider::instance().get(value.asString()));
}

void
Collidable::onStateChange(lm::GameObject& go, size_t move, size_t action)
{
    currentBox = &box->boxes(move, action);
}
