#include "Components/Movable.hpp"

LUMS_REGISTER_COMPONENT(Component::Movable, "movable");

LUMS_BIND_SETTER("movable", "body", &Component::Movable::setBody);

LUMS_BIND_MESSAGE("movable", "state_change", &Component::Movable::onStateChange);

using namespace Component;

Movable::Movable()
: speed()
{

}

void
Movable::setBody(const lm::BValue& value)
{
    body = &(BodyProvider::instance().get(value.asString()));
}

void
Movable::onStateChange(lm::GameObject& go, size_t move, size_t action)
{
    data = &(body->body(move, action));
    speed += data->impulse;
}

Movable::~Movable()
{
    
}
