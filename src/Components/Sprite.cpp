#include "Components/Sprite.hpp"

LUMS_REGISTER_COMPONENT(Component::Sprite, "sprite");

LUMS_BIND_SETTER("sprite", "texture", &Component::Sprite::setTexture);

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

Sprite::~Sprite()
{

}
