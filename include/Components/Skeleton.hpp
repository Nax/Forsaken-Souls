#ifndef COMPONENTS_SKELETON_HPP
#define COMPONENTS_SKELETON_HPP

#include <Lums>

namespace Component
{
    class Skeleton : public lm::Component
    {
        LUMS_COMPONENT

    public:
        Skeleton();
        lm::Skeleton&       skeleton();
        const lm::Texture&  texture();
        void                setTexture(const lm::BValue& value);
        void                setSkeleton(const lm::BValue& value);
        ~Skeleton();

    private:
        lm::Skeleton        _skeleton;
        const lm::Texture*  _texture;
    };
}

#endif























