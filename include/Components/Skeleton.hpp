#ifndef COMPONENTS_SKELETON_HPP
#define COMPONENTS_SKELETON_HPP

#include <Lums>
#include "Animation.hpp"

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
        void                setAnimation(const lm::BValue& value);
        void                onStateChange(lm::GameObject& go, size_t move, size_t action);
        void                onDirectionChange(lm::GameObject& go, int direction);
        ~Skeleton();

    private:
        lm::Skeleton        _skeleton;
        const lm::Texture*  _texture;
        Animation*          _animation;
    };
}

#endif























