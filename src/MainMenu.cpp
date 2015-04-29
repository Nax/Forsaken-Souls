#include "MainMenu.hpp"
#include "Game.hpp"
#include "Screen.hpp"

using namespace lm;

MainMenu::MainMenu()
: _cursor(0)
, _inhibitStik(0)
{

}

static void
setCursor(short& cursor, short modifier)
{
    cursor += modifier;
    if (cursor < MIN_CURSOR)
        cursor = MAX_CURSOR;
    else if (cursor > MAX_CURSOR)
        cursor = MIN_CURSOR;
}

void
MainMenu::handleEvent(const lm::Event& event)
{

    if (event.type == Event::Type::KeyDown)
    {
        switch (event.key)
        {
            case Key::Return:
                if (!_cursor)
                    lm::Core::get().push<Game>(); // TO DO TRANSITION
                else
                    Core::get().stop();
                // lm::Core::get().transition<Game>();
                break;
            case Key::Up:
                setCursor(_cursor, -1);
                break;
            case Key::Down:
                setCursor(_cursor, 1);
                break;
            default:
                break;
        }
    }
    if (event.type == Event::Type::ButtonDown)
    {
        switch (event.gamepad.button)
        {
            case 1:
                if (!_cursor)
                    lm::Core::get().push<Game>(); // TO DO TRANSITION
                else
                    Core::get().stop();
                // lm::Core::get().transition<Game>();
                break;
            default:
                break;
        }
    }
    if (_inhibitStik == 0 && event.type == lm::Event::Type::LeftStick)
    {
        if (event.gamepad.stick.y < -0.5f)
        {
            _inhibitStik = 25;
            setCursor(_cursor, 1);
        }
        else if (event.gamepad.stick.y > 0.5f)
        {
            _inhibitStik = 25;
            setCursor(_cursor, 1);
        }
    }
}

void
MainMenu::update()
{
    if (_inhibitStik > 0)
        --_inhibitStik;
}

void
MainMenu::render()
{
    lm::SpriteBatch sb;
    const lm::Image& ng = ImageProvider::get().image(ImageId::NewGame);
    const lm::Image& quit = ImageProvider::get().image(ImageId::Quit);
    const lm::Image& curs = ImageProvider::get().image(ImageId::MenuCursor);
    const Vector2f ngPos = { SCREEN_WIDTH / 2 - ng.width() / 2 * 0.5f, SCREEN_HEIGHT / 2 - ng.height() / 2 * 0.5f };
    const Vector2f qPos = { SCREEN_WIDTH / 2 - quit.width() / 2 * 0.5f, SCREEN_HEIGHT / 2 - quit.height() / 2 * 0.5f + ng.height() };

    sb.begin();
    sb.draw(ng, 0, ngPos, {0.5f, 0.5f});
    sb.draw(quit, 0, qPos, {0.5, 0.5f});
    if (!_cursor)
    {
        sb.draw(curs, 0, {ngPos.x - curs.width() * 0.5f, ngPos.y + ng.height() * 0.5f / 4}, {0.5f, 0.5f});
        sb.draw(curs, 0, {ngPos.x + ng.width() * 0.5f, ngPos.y + ng.height() * 0.5f / 4}, {0.5f, 0.5f}, {true, false});
    }
    else
    {
        sb.draw(curs, 0, {qPos.x - curs.width() * 0.5f, qPos.y + quit.height() * 0.5f / 4}, {0.5f, 0.5f});
        sb.draw(curs, 0, {qPos.x + quit.width() * 0.5f, qPos.y + quit.height() * 0.5f / 4}, {0.5f, 0.5f}, {true, false});
    }
    sb.end();
}

MainMenu::~MainMenu()
{

}