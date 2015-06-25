#include "Systems/RenderSprite.hpp"
#include "Components/Sprite.hpp"
#include "Screen.hpp"

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
        lm::Sprite& s = component->sprite();
        s.pos.x = go->position.x * TILE_SIZE;
        s.pos.y = SCREEN_HEIGHT - go->position.y * TILE_SIZE - s.height();
        s.pos.z = go->position.z;
        _batch.draw(s);
    }
    _batch.end();
}

RenderSprite::~RenderSprite()
{

}
