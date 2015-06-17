#include "Components/Movable.hpp"

MovableComponent::MovableComponent()
{
    bind("speed", &MovableComponent::speed);
    bind("setSpeed", &MovableComponent::setSpeed);
}

void
MovableComponent::update(Entity& e)
{
    lm::Vector2f* position = e.recv<lm::Vector2f>("position");
    *position += _speed;
}

lm::Vector2f*
MovableComponent::speed()
{
    return &_speed;
}

void
MovableComponent::setSpeed(lm::Vector2f speed)
{
    _speed = speed;
}

MovableComponent::~MovableComponent()
{

}
