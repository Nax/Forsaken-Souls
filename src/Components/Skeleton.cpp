#include "Components/Skeleton.hpp"

LUMS_REGISTER_COMPONENT(Component::Skeleton, "skeleton");

LUMS_BIND_SETTER("skeleton", "texture", &Component::Skeleton::setTexture);
LUMS_BIND_SETTER("skeleton", "skeleton", &Component::Skeleton::setSkeleton);
LUMS_BIND_SETTER("skeleton", "animation", &Component::Skeleton::setAnimation);

LUMS_BIND_MESSAGE("skeleton", "state_change", &Component::Skeleton::onStateChange);
LUMS_BIND_MESSAGE("skeleton", "direction", &Component::Skeleton::onDirectionChange);

using namespace Component;

Skeleton::Skeleton()
{

}

lm::Skeleton&
Skeleton::skeleton()
{
    return _skeleton;
}

const lm::Texture&
Skeleton::texture()
{
    return *_texture;
}

void
Skeleton::setTexture(const lm::BValue& value)
{
    _texture = &lm::TextureProvider::instance().get(value.asString());
}

void
Skeleton::setSkeleton(const lm::BValue& value)
{
    _skeleton = lm::SkeletonProvider::instance().get(value.asString()).create();
}

void
Skeleton::setAnimation(const lm::BValue& value)
{
    _animation = &(AnimationProvider::instance().get(value.asString()));
}

void
Skeleton::onStateChange(lm::GameObject& go, size_t move, size_t action)
{
    const Animation::Data& data = _animation->animation(move, action);
    _skeleton.setAnimation(data.name, data.loop);
}

void
Skeleton::onDirectionChange(lm::GameObject& go, bool direction)
{
    _skeleton.setFlip(direction);
}

Skeleton::~Skeleton()
{

}
