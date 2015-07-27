#include "Components/Movable.hpp"

LUMS_REGISTER_COMPONENT(Component::Movable, "movable");

LUMS_BIND_SETTER("movable", "body", &Component::Movable::setBody);

LUMS_BIND_MESSAGE("movable", "state_change", &Component::Movable::onStateChange);

LUMS_BIND_MESSAGE("movable", "direction", &Component::Movable::onDirectionChange);

using namespace Component;

Movable::Movable()
: speed()
, moving()
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
    if (data->impulse.x)
        speed.x = data->impulse.x * ((direction) ? 1.f : -1.f);
    if (data->impulse.y)
        speed.y = data->impulse.y;
}

void
Movable::onDirectionChange(lm::GameObject& go, int newDirection)
{
    if (newDirection)
    {
        moving = true;
        direction = (newDirection == 1);
    }
    else
        moving = false;
}

Movable::~Movable()
{
    
}
