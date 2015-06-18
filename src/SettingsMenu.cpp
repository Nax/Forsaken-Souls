#include "SettingsMenu.hpp"
#include "Assets.hpp"
#include "Screen.hpp"

#include "unistd.h"

SettingsMenu::SettingsMenu()
: _resumeAlpha(1.f),
 _resoAlpha(0.3f),
 _res1Alpha(0.f),
 _res2Alpha(0.f),
 _res3Alpha(0.f),
 _fullscreenAlpha(0.f),
 _cursor(0),
 _resCursor(0),
 _selectReso(false),
 _switchRes(false),
 _fullscreen(false)
{

}

void
SettingsMenu::load()
{
    _resumeBatch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "Resume",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT / 2 - 500.f / 2}, {1.f, 0.f, 1.f, _resumeAlpha});
    _resumeBatch.send();

    _resolutionBatch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "Resolution",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT / 2 - 300.f / 2}, {1.f, 0.f, 1.f, _resoAlpha});
    _resolutionBatch.send();

    _res1Batch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "800x600",
                    {SCREEN_WIDTH / 2 - 1200.f / 2, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _res1Alpha});
    _res1Batch.send();
    _res2Batch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "1024x768",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _res2Alpha});
    _res2Batch.send();
    _res3Batch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "2560x1440",
                    {SCREEN_WIDTH / 2 + 800.f / 2, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _res3Alpha});
    _res3Batch.send();
    _fullscreenBatch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "Fullscreen",
                    {SCREEN_WIDTH / 2 + 220.f / 2, SCREEN_HEIGHT / 2 + 100.f / 2}, {1.f, 0.f, 1.f, _fullscreenAlpha});
    _fullscreenBatch.send();

    _proj.projection = lm::ortho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void
SettingsMenu::update()
{
    if (_selectReso)
    {
        _res1Alpha = (_resCursor == 0) ? fmin(_res1Alpha + 0.03f, 1.f) : fmax(0.3f, _res1Alpha - 0.03f);
        _res2Alpha = (_resCursor == 1) ? fmin(_res2Alpha + 0.03f, 1.f) : fmax(0.3f, _res2Alpha - 0.03f);
        _res3Alpha = (_resCursor == 2) ? fmin(_res3Alpha + 0.03f, 1.f) : fmax(0.3f, _res3Alpha - 0.03f);
        _fullscreenAlpha = (_resCursor == 3) ? fmin(_fullscreenAlpha + 0.03f, 1.f) : fmax(0.3f, _fullscreenAlpha - 0.03f);
    }
    else
    {
        _res1Alpha = fmax(0.f, _res1Alpha - 0.03f);
        _res2Alpha = fmax(0.f, _res2Alpha - 0.03f);
        _res3Alpha = fmax(0.f, _res3Alpha - 0.03f);
        _fullscreenAlpha = fmax(0.f, _fullscreenAlpha - 0.03f);
    }

    float fsGreen = (_fullscreen) ? 1.f : 0.f;
    float fsBlue = 1.f - fsGreen;

    _resumeAlpha = (_cursor == 0) ? fmin(_resumeAlpha + 0.03f, 1.f) : fmax(0.3f, _resumeAlpha - 0.03f);
    _resoAlpha = (_cursor >= 1) ? fmin(_resoAlpha + 0.03f, 1.f) : fmax(0.3f, _resoAlpha - 0.03f);

    _resumeBatch.flush();
    _resumeBatch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "Resume",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT / 2 - 500.f / 2}, {1.f, 0.f, 1.f, _resumeAlpha});
    _resumeBatch.send();

    _resolutionBatch.flush();
    _resolutionBatch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "Resolution",
                    {SCREEN_WIDTH / 2 - 200.f / 2, SCREEN_HEIGHT / 2 - 300.f / 2}, {1.f, 0.f, 1.f, _resoAlpha});
    _resolutionBatch.send();



    _res1Batch.flush();
    _res1Batch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "1280x800",
                {SCREEN_WIDTH / 2 - 1200.f / 2, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _res1Alpha});
    _res1Batch.send();

    _res2Batch.flush();
    _res2Batch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "1920x1080",
                {SCREEN_WIDTH / 2 - 260.f / 2, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _res2Alpha});
    _res2Batch.send();

    _res3Batch.flush();
    _res3Batch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "2560x1440",
                {SCREEN_WIDTH / 2 + 800.f / 2, SCREEN_HEIGHT / 2 - 100.f / 2}, {1.f, 0.f, 1.f, _res3Alpha});
    _res3Batch.send();

    _fullscreenBatch.flush();
    _fullscreenBatch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), "Fullscreen",
                    {SCREEN_WIDTH / 2 - 220.f / 2, SCREEN_HEIGHT / 2 + 100.f / 2}, {1.0, fsGreen, fsBlue, _fullscreenAlpha});
    _fullscreenBatch.send();

    if (_switchRes)
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
                break;
            default:
                break;
        }
        _switchRes = false;
    }


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
                    lm::Core::instance().stop();
                    break;
                case lm::Key::Down:
                    _cursor = (_cursor + 1) % 2;
                    break;
                case lm::Key::Up:
                    _cursor = (_cursor == 0) ? 1 : _cursor - 1;
                    break;
                case lm::Key::Return:
                    if (_cursor == 0)
                        remove();
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
                    _selectReso = false;
                    break;
                case lm::Key::Return:
                    _switchRes = true;
                    _selectReso = false;
                    break;
                case lm::Key::Right:
                    _resCursor = (_resCursor + 1) % 4;
                    break;
                case lm::Key::Left:
                    _resCursor = (_resCursor == 0) ? 3 : _resCursor - 1;
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
    auto& shader = lm::ShaderProvider::instance().get(Assets::Shader::Basic2D);
    shader.use();
    _proj.view = lm::Matrix4f::identity();
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);

    _resumeBatch.render();
    _resolutionBatch.render();
    _res1Batch.render();
    _res2Batch.render();
    _res3Batch.render();
    _fullscreenBatch.render();
}

SettingsMenu::~SettingsMenu()
{

}
