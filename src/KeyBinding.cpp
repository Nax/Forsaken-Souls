#include "KeyBinding.hpp"
#include "Screen.hpp"
#include "Settings.hpp"

#include <iostream>

KeyBinding::KeyBinding()
: _cursor(0),
 _switch(false)
{

}

void
KeyBinding::load()
{
    _proj.projection = lm::ortho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
}

void
KeyBinding::update()
{
    // const MappedKeys&   keyMapping = Settings::instance().keyMapping();
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
    auto& font = lm::FontProvider::instance().get("roboto80");
    shader.use();
    _proj.view = lm::Matrix4f::identity();
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);

    lm::Key     keyrec;
    Settings&   rsettings = Settings::instance();

    lm::Vector4f color = {1.f, 0.f, 1.f, 1.f};
    _batch.begin();
    _batch.draw(font, "Left", {100.f, SCREEN_HEIGHT / 2 - 900.f / 2, 0.f}, color);

    rsettings.get<SettingsEntry::KeyLeft>(keyrec);
    _batch.draw(font, std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 900.f / 2, 0.f}, color);
    _batch.draw(font, "Right",
                    {100.f, SCREEN_HEIGHT / 2 - 700.f / 2, 0.f}, color);
    rsettings.get<SettingsEntry::KeyRight>(keyrec);
    _batch.draw(font, std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 700.f / 2, 0.f}, color);
    _batch.draw(font, "Jump",
                    {100.f, SCREEN_HEIGHT / 2 - 500.f / 2, 0.f}, color);

    rsettings.get<SettingsEntry::KeyJump>(keyrec);
    _batch.draw(font, std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 500.f / 2, 0.f}, color);
    _batch.draw(font, "Crouch",
                    {100.f, SCREEN_HEIGHT / 2 - 300.f / 2, 0.f}, color);
    rsettings.get<SettingsEntry::KeyCrouch>(keyrec);
    _batch.draw(font, std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 300.f / 2, 0.f}, color);
    _batch.draw(font, "Attack",
                    {100.f, SCREEN_HEIGHT / 2 - 100.f / 2, 0.f}, color);
    rsettings.get<SettingsEntry::KeyAttack>(keyrec);
    _batch.draw(font, std::to_string(static_cast<int>(keyrec)).c_str(),
                    {SCREEN_WIDTH - 400.f, SCREEN_HEIGHT / 2 - 100.f / 2, 0.f}, color);
    _batch.draw(font, "Back",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT - 300.f, 0.f}, color);
    _batch.end();
}

void
KeyBinding::unload()
{
    Settings::instance().store();
}

KeyBinding::~KeyBinding()
{

}
