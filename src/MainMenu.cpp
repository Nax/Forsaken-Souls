#include "MainMenu.hpp"
#include "Game.hpp"
#include "Screen.hpp"

#define MAX_CURSOR 2

MainMenu::MainMenu()
: _cursor(0)
{

}

void
MainMenu::load()
{
    _proj.projection = lm::ortho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
}

void
MainMenu::handleEvent(const lm::Event& event)
{
    if (event.type == lm::Event::Type::KeyDown)
    {
        switch (event.key)
        {
            case lm::Key::Return:
                if (!_cursor)
                    lm::Core::instance().transition<Game>();
                else
                    lm::Core::instance().stop();
                break;
            case lm::Key::Up:
                moveCursor(-1);
                break;
            case lm::Key::Down:
                moveCursor(1);
                break;
            default:
                break;
        }
    }
    else if (event.type == lm::Event::Type::ButtonDown)
    {
        switch (event.gamepad.button)
        {
            case 1:
                if (!_cursor)
                    lm::Core::instance().transition<Game>();
                else
                    lm::Core::instance().stop();
                break;
            default:
                break;
        }
    }
}

void
MainMenu::update()
{

}

void
MainMenu::render()
{
    auto& shader = lm::ShaderProvider::instance().get("basic2d");
    auto& font = lm::FontProvider::instance().get("roboto200");
    shader.use();
    _proj.view = lm::Matrix4f::identity();
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);
    _batch.begin();
    _batch.draw(font, "New Game", {500.f, 3 * SCREEN_HEIGHT / 4, 0.f});
    _batch.draw(font, "Settings", {500.f, 2 * SCREEN_HEIGHT / 4, 0.f});
    _batch.draw(font, "Quit", {500.f, SCREEN_HEIGHT / 4, 0.f});
    _batch.end();
}

void
MainMenu::unload()
{

}

MainMenu::~MainMenu()
{

}

/* PRIVATE */

void
MainMenu::moveCursor(int dir)
{
    _cursor += dir;
    if (_cursor < 0)
        _cursor = MAX_CURSOR - 1;
    else if (_cursor >= MAX_CURSOR)
        _cursor = 0;
}
