#include "Entity.hpp"
#include "Components/Transform.hpp"

Entity::Entity()
{
	attach<TransformComponent>();
}

lm::Vector2f
Entity::center()
{
    lm::Vector2f position = *(recv<lm::Vector2f>("position"));
    lm::Rect2f*  boundingBox = recv<lm::Rect2f>("boundingBox");
    if (boundingBox)
        return position + boundingBox->pos + boundingBox->size * 0.5f;
    return position;
}


Entity::~Entity()
{

}
