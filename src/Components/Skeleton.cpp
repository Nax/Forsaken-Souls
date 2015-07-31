#include "Components/Skeleton.hpp"

LUMS_REGISTER_COMPONENT(Component::Skeleton, "skeleton");

LUMS_BIND_SETTER("skeleton", "texture", &Component::Skeleton::setTexture);
LUMS_BIND_SETTER("skeleton", "skeleton", &Component::Skeleton::setSkeleton);

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

Skeleton::~Skeleton()
{

}
