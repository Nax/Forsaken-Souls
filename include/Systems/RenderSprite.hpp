#ifndef RENDER_SPRITE_HPP
#define RENDER_SPRITE_HPP

#include <vector>
#include <Lums>

namespace System
{
    class RenderSprite
    {
    public:
        RenderSprite();
        void    operator()(std::vector<lm::GameObject*>& gameObjects);
        ~RenderSprite();

    private:
        lm::SpriteBatch _batch;
    };
}

#endif
