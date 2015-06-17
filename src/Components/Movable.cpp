#include "Components/Movable.hpp"

MovableComponent::MovableComponent()
{
    bind("speed", &MovableComponent::speed);
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

MovableComponent::~MovableComponent()
{

}