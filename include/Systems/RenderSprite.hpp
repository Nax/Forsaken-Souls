#ifndef SYSTEMS_RENDER_SPRITE_HPP
#define SYSTEMS_RENDER_SPRITE_HPP

#include <vector>
#include <Lums>

namespace System
{
    class RenderSprite
    {
    public:
        RenderSprite();
        void    render(std::vector<lm::GameObject*>& gameObjects);
        void    update(std::vector<lm::GameObject*>& gameObjects);
        ~RenderSprite();

    private:
        lm::SpriteBatch _batch;
    };
}

#endif
