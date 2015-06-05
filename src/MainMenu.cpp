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

    _newGameBatch.draw(newGame);
    _newGameBatch.send();

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
        }
    }
    else if (event.type == lm::Event::Type::ButtonDown)
    {
        switch (event.gamepad.button)
        {
            case 1:
                if (!_cursor)
                    lm::Core::instance().push<Game>();
                else
                    lm::Core::instance().stop();
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
    // lm::SpriteBatch sb;
    // const lm::Image& ng = ImageProvider::get().image(ImageId::NewGame);
    // const lm::Image& quit = ImageProvider::get().image(ImageId::Quit);
    // const lm::Image& curs = ImageProvider::get().image(ImageId::MenuCursor);
    // const Vector2f ngPos = { SCREEN_WIDTH / 2 - ng.width() / 2 * 0.5f, SCREEN_HEIGHT / 2 - ng.height() / 2 * 0.5f };
    // const Vector2f qPos = { SCREEN_WIDTH / 2 - quit.width() / 2 * 0.5f, SCREEN_HEIGHT / 2 - quit.height() / 2 * 0.5f + ng.height() };

    // sb.begin();
    // sb.draw(ng, 0, ngPos, {0.5f, 0.5f});
    // sb.draw(quit, 0, qPos, {0.5, 0.5f});
    // if (!_cursor)
    // {
    //     sb.draw(curs, 0, {ngPos.x - curs.width() * 0.5f, ngPos.y + ng.height() * 0.5f / 4}, {0.5f, 0.5f}, {true, false});
    //     sb.draw(curs, 0, {ngPos.x + ng.width() * 0.5f, ngPos.y + ng.height() * 0.5f / 4}, {0.5f, 0.5f});
    // }
    // else
    // {
    //     sb.draw(curs, 0, {qPos.x - curs.width() * 0.5f, qPos.y + quit.height() * 0.5f / 4}, {0.5f, 0.5f}, {true, false});
    //     sb.draw(curs, 0, {qPos.x + quit.width() * 0.5f, qPos.y + quit.height() * 0.5f / 4}, {0.5f, 0.5f});
    // }
    // sb.end();

    auto& shader = lm::ShaderProvider::instance().get(Assets::Shader::MainMenu);
    shader.use();
    lm::uniform(shader, "projection", _proj.projection);
    _newGameBatch.render();
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
