#ifndef SYSTEMS_INPUT_HPP
#define SYSTEMS_INPUT_HPP

#include <vector>
#include <Lums>

namespace System
{
    class Input
    {
    public:
        Input();
        void    operator()(std::vector<lm::GameObject*>& gameObjects, const lm::Event& event);
        ~Input();
    };
}

#endif
