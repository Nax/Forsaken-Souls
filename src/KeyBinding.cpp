#include "KeyBinding.hpp"
#include "Assets.hpp"
#include "Screen.hpp"
#include "Settings.hpp"

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
 _backAlpha(0.3f),
 _cursor(0),
 _switch(false)
{

}

void
KeyBinding::load()
{
    Settings&   rsettings = Settings::instance();
    lm::Key     keyrec;

    _leftBatch.draw(lm::FontProvider::instance().get("roboto80"), "Left",
                    {100.f, SCREEN_HEIGHT / 2 - 900.f / 2}, {1.f, 0.f, 1.f, _leftAlpha});
    _leftBatch.send();
    rsettings.get<SettingsEntry::KeyLeft>(keyrec);
    _keyLeftBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 900.f / 2}, {1.f, 0.f, 1.f, _keyLeftAlpha});
    _keyLeftBatch.send();

    _rightBatch.draw(lm::FontProvider::instance().get("roboto80"), "Right",
                    {100.f, SCREEN_HEIGHT / 2 - 700.f / 2}, {1.f, 0.f, 1.f, _rightAlpha});
    _rightBatch.send();
    rsettings.get<SettingsEntry::KeyRight>(keyrec);
    _keyRightBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 700.f / 2}, {1.f, 0.f, 1.f, _keyRightAlpha});
    _keyRightBatch.send();

    _jumpBatch.draw(lm::FontProvider::instance().get("roboto80"), "Jump",
                    {100.f, SCREEN_HEIGHT / 2 - 500.f / 2}, {1.f, 0.f, 1.f, _jumpAlpha});
    _jumpBatch.send();
    rsettings.get<SettingsEntry::KeyJump>(keyrec);
    _keyJumpBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 500.f / 2}, {1.f, 0.f, 1.f, _keyJumpAlpha});
    _keyJumpBatch.send();

    _crouchBatch.draw(lm::FontProvider::instance().get("roboto80"), "Crouch",
                    {100.f, SCREEN_HEIGHT / 2 - 300.f / 2}, {1.f, 0.f, 1.f, _crouchAlpha});
    _crouchBatch.send();
    rsettings.get<SettingsEntry::KeyCrouch>(keyrec);
    _keyCrouchBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 300.f / 2}, {1.f, 0.f, 1.f, _keyCrouchAlpha});
    _keyCrouchBatch.send();

    _attackBatch.draw(lm::FontProvider::instance().get("roboto80"), "Attack",
                    {100.f, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _attackAlpha});
    _attackBatch.send();
    rsettings.get<SettingsEntry::KeyAttack>(keyrec);
    _keyAttackBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _keyAttackAlpha});
    _keyAttackBatch.send();

    _backBatch.draw(lm::FontProvider::instance().get("roboto80"), "Back",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT - 300.f}, {1.f, 0.f, 1.f, _backAlpha});
    _backBatch.send();

    _proj.projection = lm::ortho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void
KeyBinding::update()
{
    const MappedKeys&   keyMapping = Settings::instance().keyMapping();

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
    _backAlpha = (_cursor == 5) ? fmin(_backAlpha + 0.03f, 1.f) : fmax(0.3f, _backAlpha - 0.03f);

    _leftBatch.flush();
    _leftBatch.draw(lm::FontProvider::instance().get("roboto80"), "Left",
                    {100.f, SCREEN_HEIGHT / 2 - 900.f / 2}, {1.f, 0.f, 1.f, _leftAlpha});
    _leftBatch.send();
    _keyLeftBatch.flush();
    if (_switch && _cursor == 0)
        _keyLeftBatch.draw(lm::FontProvider::instance().get("roboto80"), "Press Key",
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 900.f / 2}, {1.f, 0.f, 1.f, _keyLeftAlpha});
    else
        _keyLeftBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyMapping.left)).c_str(),
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
        _keyRightBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyMapping.right)).c_str(),
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
        _keyJumpBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyMapping.jump)).c_str(),
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
        _keyCrouchBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyMapping.crouch)).c_str(),
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
        _keyAttackBatch.draw(lm::FontProvider::instance().get("roboto80"), std::to_string(static_cast<int>(keyMapping.attack)).c_str(),
                        {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _keyAttackAlpha});
    _keyAttackBatch.send();

    _backBatch.flush();
    _backBatch.draw(lm::FontProvider::instance().get("roboto80"), "Back",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT - 300.f}, {1.f, 0.f, 1.f, _backAlpha});
    _backBatch.send();
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
            switch (_cursor)
            {
                case 0:
                    Settings::instance().set<SettingsEntry::KeyLeft>(event.key);
                    break;
                case 1:
                    Settings::instance().set<SettingsEntry::KeyRight>(event.key);
                    break;
                case 2:
                    Settings::instance().set<SettingsEntry::KeyJump>(event.key);
                    break;
                case 3:
                    Settings::instance().set<SettingsEntry::KeyCrouch>(event.key);
                    break;
                case 4:
                    Settings::instance().set<SettingsEntry::KeyAttack>(event.key);
                    break;
                default:
                    break;
            }
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
    _backBatch.render();
}

void
KeyBinding::unload()
{
    Settings::instance().store();
}

KeyBinding::~KeyBinding()
{

}
