#include <cmath>
#include "Systems/Physics.hpp"
#include "Physics.hpp"

#include <iostream>

void
System::Physics::update(const Map& map)
{
    for (auto go : lm::GameObjectSet::instance())
    {
        auto* physics = go->getComponent<Component::Physics>("physics");
        auto* collider = go->getComponent<Component::Collider>("collider");
        if (!(collider && physics))
            continue;
        lm::Rect2f boundingBox = collider->boundingBox;
        boundingBox.pos.x += go->position.x;
        boundingBox.pos.y += go->position.y;
        ::Physics::computeNextFrame(map, boundingBox, physics->speed, physics->grounded);
        go->position.x = boundingBox.pos.x - collider->boundingBox.pos.x;
        go->position.y = boundingBox.pos.y - collider->boundingBox.pos.y;
    }
}
