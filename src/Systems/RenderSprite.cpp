#include "Systems/RenderSprite.hpp"
#include "Components/Sprite.hpp"

using namespace System;

RenderSprite::RenderSprite()
{

}

void
RenderSprite::operator()(std::vector<lm::GameObject*>& gameObjects)
{
    _batch.begin();
    for (auto go : gameObjects)
    {
        auto component = static_cast<Component::Sprite*>(go->getComponent("sprite"));
        if (!component)
            continue;
        _batch.draw(component->sprite());
    }
    _batch.end();
}

RenderSprite::~RenderSprite()
{

}
