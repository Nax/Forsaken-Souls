#include "SettingsMenu.hpp"
#include "Settings.hpp"
#include "KeyBinding.hpp"
#include "Screen.hpp"

SettingsMenu::SettingsMenu()
: _cursor(0),
 _resCursor(0),
 _fullscreen(false)
{

}

void
SettingsMenu::load()
{
    lm::Window& win = lm::Core::instance().window();
    _resolutions = {
        {640, 480},
        {800, 600},
        {1024, 768},
        {1280, 720},
        {1280, 800},
        {1280, 960},
        {1440, 900},
        {1440, 1080},
        {1600, 900},
        {1600, 1200},
        {1920, 1080},
        {1920, 1200},
        {1920, 1440},
        {2560, 1600}
    };
    std::remove_if(_resolutions.begin(), _resolutions.end(), [&win](lm::Vector2i res)
    {
        return (res.x > win.maxSize().x || res.y > win.maxSize().y);
    });

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
        switch (event.key)
        {
            case lm::Key::Escape:
                remove();
                break;
            case lm::Key::Down:
                _cursor = (_cursor + 1) % 4;
                break;
            case lm::Key::Up:
                _cursor = (_cursor == 0) ? 3 : _cursor - 1;
                break;
            case lm::Key::Left:
                if (_cursor == 2)
                    _resCursor = (_resCursor > 0) ? _resCursor - 1 : 0;
                break;
            case lm::Key::Right:
                if (_cursor == 2)
                    _resCursor = (_resCursor < _resolutions.size() - 1) ? _resCursor + 1 : _resCursor;
                break;
            case lm::Key::Return:
                if (_cursor == 0)
                    remove();
                else if (_cursor == 1)
                    lm::Core::instance().push<KeyBinding>();
                else if (_cursor == 3)
                    switchRes();
                break;
            default:
                break;
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
    lm::Vector4f color = (_cursor == 0) ? select : none;
    _batch.draw(font, "Resume", {500.f, 3 * SCREEN_HEIGHT / 4.f, 0.f}, color);
    color = (_cursor == 1) ? select : none;
    _batch.draw(font, "Bind Keys", {500.f, 2.5f * SCREEN_HEIGHT / 4.f, 0.f}, color);
    color = (_cursor == 2) ? select : none;
    _batch.draw(font, "Resolution", {500.f, 2.f * SCREEN_HEIGHT / 4.f, 0.f}, color);
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%dx%d", _resolutions[_resCursor].x, _resolutions[_resCursor].y);
    _batch.draw(font, buffer, {1000.f, 2.f * SCREEN_HEIGHT / 4.f, 0.f}, color);
    color = (_cursor == 3) ? select : none;
    _batch.draw(font, "Apply", {500.f, 1.5f * SCREEN_HEIGHT / 4.f, 0.f}, color);
    _batch.end();
}

void
SettingsMenu::switchRes()
{
    lm::Vector2i res = _resolutions[_resCursor];
    lm::Core::instance().window().resize(res.x, res.y);
    float scale = float(res.x) / SCREEN_WIDTH;
    lm::setGlobalScale(scale);
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
