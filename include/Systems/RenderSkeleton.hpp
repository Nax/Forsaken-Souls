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
        void    render(std::vector<lm::GameObject*>& gameObjects);
        void    update(std::vector<lm::GameObject*>& gameObjects);
        ~RenderSkeleton();

    private:
        lm::SpriteBatch _batch;
    };
}

#endif
