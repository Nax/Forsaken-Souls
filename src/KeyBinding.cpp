#include "KeyBinding.hpp"
#include "Assets.hpp"
#include "Screen.hpp"

#include <iostream>

KeyBinding::KeyBinding()
: _leftAlpha(1.f),
 _rightAlpha(0.3f),
 _jumpAlpha(0.3f),
 _crouchAlpha(0.3f),
 _attackAlpha(0.3f),
 _keyLeftAlpha(1.f),
 _keyRightAlpha(0.3f),
 _keyJumpAlpha(0.3f),
 _keyCrouchAlpha(0.3f),
 _keyAttackAlpha(0.3f),
 _saveAlpha(0.3f),
 _cursor(0),
 _switch(false)
{
    _keys[static_cast<int>(Input::Left)] = lm::Key::Left;
    _keys[static_cast<int>(Input::Right)] = lm::Key::Right;
    _keys[static_cast<int>(Input::Jump)] = lm::Key::Space;
    _keys[static_cast<int>(Input::Crouch)] = lm::Key::Down;
    _keys[static_cast<int>(Input::Attack)] = lm::Key::A;
}

void
KeyBinding::load()
{
    _leftBatch.draw(lm::FontProvider::instance().get("roboto80"), "Left",
                    {100.f, SCREEN_HEIGHT / 2 - 900.f / 2}, {1.f, 0.f, 1.f, _leftAlpha});
    _leftBatch.send();
    _keyLeftBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Left)])).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 900.f / 2}, {1.f, 0.f, 1.f, _keyLeftAlpha});
    _keyLeftBatch.send();

    _rightBatch.draw(lm::FontProvider::instance().get("roboto80"), "Right",
                    {100.f, SCREEN_HEIGHT / 2 - 700.f / 2}, {1.f, 0.f, 1.f, _rightAlpha});
    _rightBatch.send();
    _keyRightBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Right)])).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 700.f / 2}, {1.f, 0.f, 1.f, _keyRightAlpha});
    _keyRightBatch.send();

    _jumpBatch.draw(lm::FontProvider::instance().get("roboto80"), "Jump",
                    {100.f, SCREEN_HEIGHT / 2 - 500.f / 2}, {1.f, 0.f, 1.f, _jumpAlpha});
    _jumpBatch.send();
    _keyJumpBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Jump)])).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 500.f / 2}, {1.f, 0.f, 1.f, _keyJumpAlpha});
    _keyJumpBatch.send();

    _crouchBatch.draw(lm::FontProvider::instance().get("roboto80"), "Crouch",
                    {100.f, SCREEN_HEIGHT / 2 - 300.f / 2}, {1.f, 0.f, 1.f, _crouchAlpha});
    _crouchBatch.send();
    _keyCrouchBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Crouch)])).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 300.f / 2}, {1.f, 0.f, 1.f, _keyCrouchAlpha});
    _keyCrouchBatch.send();

    _attackBatch.draw(lm::FontProvider::instance().get("roboto80"), "Attack",
                    {100.f, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _attackAlpha});
    _attackBatch.send();
    _keyAttackBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Attack)])).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _keyAttackAlpha});
    _keyAttackBatch.send();

    _saveBatch.draw(lm::FontProvider::instance().get("roboto80"), "Save",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT - 200.f}, {1.f, 0.f, 1.f, _saveAlpha});
    _saveBatch.send();

    _proj.projection = lm::ortho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void
KeyBinding::update()
{
    _leftAlpha = (_cursor == 0) ? fmin(_leftAlpha + 0.03f, 1.f) : fmax(0.3f, _leftAlpha - 0.03f);
    _rightAlpha = (_cursor == 1) ? fmin(_rightAlpha + 0.03f, 1.f) : fmax(0.3f, _rightAlpha - 0.03f);
    _jumpAlpha = (_cursor == 2) ? fmin(_jumpAlpha + 0.03f, 1.f) : fmax(0.3f, _jumpAlpha - 0.03f);
    _crouchAlpha = (_cursor == 3) ? fmin(_crouchAlpha + 0.03f, 1.f) : fmax(0.3f, _crouchAlpha - 0.03f);
    _attackAlpha = (_cursor == 4) ? fmin(_attackAlpha + 0.03f, 1.f) : fmax(0.3f, _attackAlpha - 0.03f);
    _keyLeftAlpha = _leftAlpha;
    _keyRightAlpha = _rightAlpha;
    _keyJumpAlpha = _jumpAlpha;
    _keyCrouchAlpha = _crouchAlpha;
    _keyAttackAlpha = _attackAlpha;
    _saveAlpha = (_cursor == 5) ? fmin(_saveAlpha + 0.03f, 1.f) : fmax(0.3f, _saveAlpha - 0.03f);

    _leftBatch.flush();
    _leftBatch.draw(lm::FontProvider::instance().get("roboto80"), "Left",
                    {100.f, SCREEN_HEIGHT / 2 - 900.f / 2}, {1.f, 0.f, 1.f, _leftAlpha});
    _leftBatch.send();
    _keyLeftBatch.flush();
    if (_switch && _cursor == 0)
        _keyLeftBatch.draw(lm::FontProvider::instance().get("roboto80"), "Press Key",
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 900.f / 2}, {1.f, 0.f, 1.f, _keyLeftAlpha});
    else
        _keyLeftBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Left)])).c_str(),
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 900.f / 2}, {1.f, 0.f, 1.f, _keyLeftAlpha});
    _keyLeftBatch.send();

    _rightBatch.flush();
    _rightBatch.draw(lm::FontProvider::instance().get("roboto80"), "Right",
                    {100.f, SCREEN_HEIGHT / 2 - 700.f / 2}, {1.f, 0.f, 1.f, _rightAlpha});
    _rightBatch.send();
    _keyRightBatch.flush();
    if (_switch && _cursor == 1)
        _keyRightBatch.draw(lm::FontProvider::instance().get("roboto80"), "Press Key",
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 700.f / 2}, {1.f, 0.f, 1.f, _keyRightAlpha});
    else
        _keyRightBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Right)])).c_str(),
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 700.f / 2}, {1.f, 0.f, 1.f, _keyRightAlpha});
    _keyRightBatch.send();

    _jumpBatch.flush();
    _jumpBatch.draw(lm::FontProvider::instance().get("roboto80"), "Jump",
                    {100.f, SCREEN_HEIGHT / 2 - 500.f / 2}, {1.f, 0.f, 1.f, _jumpAlpha});
    _jumpBatch.send();
    _keyJumpBatch.flush();
    if (_switch && _cursor == 2)
        _keyJumpBatch.draw(lm::FontProvider::instance().get("roboto80"), "Press Key",
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 500.f / 2}, {1.f, 0.f, 1.f, _keyJumpAlpha});
    else
        _keyJumpBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Jump)])).c_str(),
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 500.f / 2}, {1.f, 0.f, 1.f, _keyJumpAlpha});
    _keyJumpBatch.send();

    _crouchBatch.flush();
    _crouchBatch.draw(lm::FontProvider::instance().get("roboto80"), "Crouch",
                    {100.f, SCREEN_HEIGHT / 2 - 300.f / 2}, {1.f, 0.f, 1.f, _crouchAlpha});
    _crouchBatch.send();
    _keyCrouchBatch.flush();
    if (_switch && _cursor == 3)
        _keyCrouchBatch.draw(lm::FontProvider::instance().get("roboto80"), "Press Key",
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 300.f / 2}, {1.f, 0.f, 1.f, _keyCrouchAlpha});
    else
        _keyCrouchBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Crouch)])).c_str(),
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 300.f / 2}, {1.f, 0.f, 1.f, _keyCrouchAlpha});
    _keyCrouchBatch.send();

    _attackBatch.flush();
    _attackBatch.draw(lm::FontProvider::instance().get("roboto80"), "Attack",
                    {100.f, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _attackAlpha});
    _attackBatch.send();
    _keyAttackBatch.flush();
    if (_switch && _cursor == 4)
        _keyAttackBatch.draw(lm::FontProvider::instance().get("roboto80"), "Press Key",
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _keyAttackAlpha});
    else
        _keyAttackBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(_keys[static_cast<int>(Input::Attack)])).c_str(),
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _keyAttackAlpha});
    _keyAttackBatch.send();

    _saveBatch.flush();
    _saveBatch.draw(lm::FontProvider::instance().get("roboto80"), "Save",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT - 200.f}, {1.f, 0.f, 1.f, _saveAlpha});
    _saveBatch.send();
}

void
KeyBinding::handleEvent(const lm::Event& event)
{
    if (event.type == lm::Event::Type::KeyDown)
    {
        if (!_switch)
        {
            switch (event.key)
            {
                case lm::Key::Escape:
                    remove();
                    break;
                case lm::Key::Down:
                    _cursor = (_cursor + 1) % 6;
                    break;
                case lm::Key::Up:
                    _cursor = (_cursor == 0) ? 5 : _cursor - 1;
                    break;
                case lm::Key::Return:
                    if (_cursor == 5)
                        remove();
                    else
                        _switch = true;
                    break;
                default:
                    break;
            }
        }
        else
        {
            _keys[_cursor] = event.key;
            _switch = false;
        }
    }
}

void
KeyBinding::render()
{
    auto& shader = lm::ShaderProvider::instance().get("basic2d");
    shader.use();
    _proj.view = lm::Matrix4f::identity();
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);

    _leftBatch.render();
    _rightBatch.render();
    _jumpBatch.render();
    _crouchBatch.render();
    _attackBatch.render();
    _keyLeftBatch.render();
    _keyRightBatch.render();
    _keyJumpBatch.render();
    _keyCrouchBatch.render();
    _keyAttackBatch.render();
    _saveBatch.render();
}

KeyBinding::~KeyBinding()
{

}
