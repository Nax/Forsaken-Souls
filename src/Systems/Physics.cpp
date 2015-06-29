#include "Systems/Physics.hpp"

using namespace System;

Physics::Physics()
{

}

void
Physics::update(std::vector<lm::GameObject*>& gameObjects)
{
    for (auto go : gameObjects)
    {
        auto* movable = static_cast<Component::Movable*>(go->getComponent("movable"));
        if (!movable)
            continue;
        move(*go, *movable);
    }
}

Physics::~Physics()
{
    
}

/* Private */

void
Physics::move(lm::GameObject& go, Component::Movable& movable)
{
    go.position.x += movable.speed.x * 0.04f;
    go.position.y += movable.speed.y * 0.04f;
    movable.speed = movable.speed * 0.95f + movable.data->speed * 0.05f;
}
