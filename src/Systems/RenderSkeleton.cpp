#include "Systems/RenderSkeleton.hpp"
#include "Components/Skeleton.hpp"
#include "Screen.hpp"

using namespace System;

RenderSkeleton::RenderSkeleton()
{

}

void
RenderSkeleton::render()
{
    auto& gameObjects = lm::GameObjectSet::instance();
    _batch.begin();
    for (auto it = gameObjects.rbegin(); it != gameObjects.rend(); ++it)
    {
        auto go = *it;
        auto component = go->getComponent<Component::Skeleton>("skeleton");
        if (!component)
            continue;
        lm::Skeleton& s = component->skeleton();
        const lm::Texture& t = component->texture();
        _batch.draw(s, t, {go->position.x * TILE_SIZE, go->position.y * TILE_SIZE, go->position.z});
    }
    _batch.end();
}

void
RenderSkeleton::update()
{
    for (auto& go : lm::GameObjectSet::instance())
    {
        auto component = go->getComponent<Component::Skeleton>("skeleton");
        if (!component)
            continue;
        lm::Skeleton& s = component->skeleton();
        s.update();
        if (s.finished())
            go->send("switch_state", lm::sym("animation_end"));
    }
}

RenderSkeleton::~RenderSkeleton()
{

}
