#include "Components/Transform.hpp"

TransformComponent::TransformComponent()
{
    bind("position", &TransformComponent::pos);
    bind("scale", &TransformComponent::scale);
    bind("rotation", &TransformComponent::rot);
}

lm::Vector2f*   
TransformComponent::pos()
{
    return &_pos;
}

lm::Vector2f*   
TransformComponent::scale()
{
    return &_scale;
}

lm::Angle*      
TransformComponent::rot()
{
    return &_rot;
}

TransformComponent::~TransformComponent()
{

}