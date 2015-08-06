#ifndef SYSTEMS_RENDER_SKELETON_HPP
#define SYSTEMS_RENDER_SKELETON_HPP

#include <vector>
#include <Lums>

namespace System
{
    class RenderSkeleton
    {
    public:
        RenderSkeleton();
        void    render();
        void    update();
        ~RenderSkeleton();

    private:
        lm::SpriteBatch _batch;
    };
}

#endif
