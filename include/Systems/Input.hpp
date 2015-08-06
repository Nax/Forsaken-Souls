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
        void    handleEvent(const lm::Event& event);
        void    update();
        ~Input();

    private:
        void    sendInput(lm::GameObject& object, const char* str);
    };
}

#endif
