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
        void    handleEvent(std::vector<lm::GameObject*>& gameObjects, const lm::Event& event);
        void    update(std::vector<lm::GameObject*>& gameObjects);
        ~Input();

    private:
        void    sendInput(lm::GameObject& object, const char* str);
    };
}

#endif
