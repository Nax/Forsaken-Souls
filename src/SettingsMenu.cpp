#include "SettingsMenu.hpp"
#include "Settings.hpp"
#include "KeyBinding.hpp"
#include "Screen.hpp"

SettingsMenu::SettingsMenu()
: _cursor(0),
 _resCursor(0),
 _selectReso(false),
 _fullscreen(false)
{

}

void
SettingsMenu::load()
{
    // {
    //     lm::Vector2i    savedRes;

        // Settings::instance().get<SettingsEntry::GraphResolution>(savedRes);
        // lm::Core::instance().window().resize(savedRes.x, savedRes.y);
    // }
    _proj.projection = lm::ortho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
}

void
SettingsMenu::update()
{

}

void
SettingsMenu::handleEvent(const lm::Event& event)
{
    if (event.type == lm::Event::Type::KeyDown)
    {
        if (!_selectReso)
        {
            switch (event.key)
            {
                case lm::Key::Escape:
                    remove();
                    break;
                case lm::Key::Down:
                    _cursor = (_cursor + 1) % 3;
                    break;
                case lm::Key::Up:
                    _cursor = (_cursor == 0) ? 2 : _cursor - 1;
                    break;
                case lm::Key::Return:
                    if (_cursor == 0)
                        remove();
                    else if (_cursor == 1)
                        lm::Core::instance().push<KeyBinding>();
                    else
                        _selectReso = true;
                    break;
                default:
                    break;
            }
        }
        else
        {
            switch (event.key)
            {
                case lm::Key::Escape:
                    _resCursor = 0;
                    _selectReso = false;
                    break;
                case lm::Key::Return:
                    switchRes();
                    break;
                case lm::Key::Down:
                    _resCursor = (_resCursor + 1) % 4;
                    break;
                case lm::Key::Up:
                    _resCursor = (_resCursor == 0) ? 3 : --_resCursor;
                    break;
                default:
                    break;
            }
        }
    }
}

void
SettingsMenu::render()
{
    auto& shader = lm::ShaderProvider::instance().get("basic2d");
    auto& font = lm::FontProvider::instance().get("roboto80");

    shader.use();
    _proj.view = lm::Matrix4f::identity();
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);
 
    _batch.begin();
    lm::Vector4f select = {0.2f, 0.6f, 0.2f, 1.0f};
    lm::Vector4f none = {1.0f, 1.0f, 1.0f, 1.0f};
    if (_selectReso)
    {   
        lm::Vector4f color = (_resCursor == 0) ? select : none;
        _batch.draw(font, "1280x800", {1000.f, 3.f * SCREEN_HEIGHT / 4.f, 0.f}, color);
        color = (_resCursor == 1) ? select : none;
        _batch.draw(font, "1920x1080", {1000.f, 2.75f * SCREEN_HEIGHT / 4.f, 0.f}, color);
        color = (_resCursor == 2) ? select : none;
        _batch.draw(font, "2560x1440", {1000.f, 2.5f * SCREEN_HEIGHT / 4.f, 0.f}, color);
        color = (_resCursor == 3) ? select : none;
        _batch.draw(font, "Fullscreen", {1000.f, 2.25f * SCREEN_HEIGHT / 4.f, 0.f}, color);
    }
    lm::Vector4f color = (_cursor == 0) ? select : none;
    _batch.draw(font, "Resume", {500.f, 3 * SCREEN_HEIGHT / 4.f, 0.f}, color);
    color = (_cursor == 1) ? select : none;
    _batch.draw(font, "Bind Keys", {500.f, 2.5f * SCREEN_HEIGHT / 4.f, 0.f}, color);
    color = (_cursor == 2) ? select : none;
    _batch.draw(font, "Resolution", {500.f, 2.f * SCREEN_HEIGHT / 4.f, 0.f}, color);
    _batch.end();
}

void
SettingsMenu::switchRes()
{
    switch (_resCursor)
    {
        case 0:
            lm::Core::instance().window().resize(1280, 800);
            break;
        case 1:
            lm::Core::instance().window().resize(1920, 1080);
            break;
        case 2:
            lm::Core::instance().window().resize(2560, 1440);
            break;
        case 3:
            _fullscreen = !_fullscreen;
            Settings::instance().set<SettingsEntry::GraphFullScreen>(_fullscreen);
            break;
        default:
            break;
    }
    // Settings::instance().set<SettingsEntry::GraphResolution>(res);
}

void
SettingsMenu::unload()
{
    Settings::instance().store();
}

SettingsMenu::~SettingsMenu()
{

}
