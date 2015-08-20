#ifndef KEY_BINDING_HPP
#define KEY_BINDING_HPP

#include <Lums>

enum class Input : int
{
    Left = 0,
    Right,
    Jump,
    Crouch,
    Attack
};

class KeyBinding : public lm::GameState
{
public:
    KeyBinding();
    void    load();
    void    update();
    void    handleEvent(const lm::Event& event);
    void    render();
    void    unload();
    ~KeyBinding();

private:
    lm::Projection          _proj;
    lm::SpriteBatch         _batch;

    int                     _cursor;
    bool                    _switch;
};

#endif
