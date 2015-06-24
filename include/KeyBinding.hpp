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
    ~KeyBinding();

private:
    lm::Projection          _proj;

    lm::SpriteBatch         _leftBatch;
    lm::SpriteBatch         _rightBatch;
    lm::SpriteBatch         _jumpBatch;
    lm::SpriteBatch         _crouchBatch;
    lm::SpriteBatch         _attackBatch;
    lm::SpriteBatch         _keyLeftBatch;
    lm::SpriteBatch         _keyRightBatch;
    lm::SpriteBatch         _keyJumpBatch;
    lm::SpriteBatch         _keyCrouchBatch;
    lm::SpriteBatch         _keyAttackBatch;
    lm::SpriteBatch         _saveBatch;


    float                   _leftAlpha;
    float                   _rightAlpha;
    float                   _jumpAlpha;
    float                   _crouchAlpha;
    float                   _attackAlpha;
    float                   _keyLeftAlpha;
    float                   _keyRightAlpha;
    float                   _keyJumpAlpha;
    float                   _keyCrouchAlpha;
    float                   _keyAttackAlpha;
    float                   _saveAlpha;

    int                     _cursor;
    bool                    _switch;
};

#endif
