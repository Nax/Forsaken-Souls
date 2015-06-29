#include "Components/Sprite.hpp"

LUMS_REGISTER_COMPONENT(Component::Sprite, "sprite");

LUMS_BIND_SETTER("sprite", "texture", &Component::Sprite::setTexture);
LUMS_BIND_SETTER("sprite", "animation", &Component::Sprite::setAnimation);

LUMS_BIND_MESSAGE("sprite", "state_change", &Component::Sprite::onStateChange);

using namespace Component;

Sprite::Sprite()
{

}

lm::Sprite&
Sprite::sprite()
{
    return _sprite;
}

void
Sprite::setTexture(const lm::BValue& value)
{
    _sprite.setTexture(lm::TextureProvider::instance().get(value.asString()));
}

void
Sprite::setAnimation(const lm::BValue& value)
{
    _animation = &(AnimationProvider::instance().get(value.asString()));
}

void
Sprite::onStateChange(lm::GameObject& go, size_t move, size_t action)
{
    auto& data = _animation->animation(move, action);
    _sprite.setAnimation(data.start, data.length, data.speed, data.repeat);
}

Sprite::~Sprite()
{

}
