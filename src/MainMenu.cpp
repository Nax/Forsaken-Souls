#include "MainMenu.hpp"
#include "Game.hpp"
#include "Screen.hpp"
#include "Assets.hpp"

#define MAX_CURSOR 2

MainMenu::MainMenu()
: _cursor(0)
{

}

void
MainMenu::load()
{
    auto& newGame = lm::TextureProvider::instance().get(Assets::Texture::NewGame);
    auto& quit = lm::TextureProvider::instance().get(Assets::Texture::Quit);
    auto& menuCursor = lm::TextureProvider::instance().get(Assets::Texture::MenuCursor);

    _newGameBatch.draw(newGame, 0, {SCREEN_WIDTH / 2 - newGame.width() / 2, SCREEN_HEIGHT / 3 - newGame.height() / 2});
    _newGameBatch.send();

    _quitBatch.draw(quit, 0, {SCREEN_WIDTH / 2 - quit.width() / 2, 2 * SCREEN_HEIGHT / 3 - quit.height() / 2});
    _quitBatch.send();

    _cursorBatch.draw(menuCursor, 0, {0, -menuCursor.height() / 2}, {1, 1}, {1, 1, 1, 1}, {true, false});
    _cursorBatch.send();

    _proj.projection = lm::ortho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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
    auto& shader = lm::ShaderProvider::instance().get(Assets::Shader::Basic2D);
    shader.use();
    _proj.view = lm::Matrix4f::identity();
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);
    _newGameBatch.render();
    _quitBatch.render();
    lm::translate(_proj.view, 300, (1 + _cursor) * SCREEN_HEIGHT / 3, 0);
    lm::uniform(shader, "view", _proj.view);
    _cursorBatch.render();
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
