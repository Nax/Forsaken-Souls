#include "Game.hpp"

using namespace lm;

Game::Game()
{

}

void
Game::load()
{
    _level.load(0);
}

void
Game::update()
{
    _player.update();
}

void
Game::render() const
{
	lm::SpriteBatch sb;

	sb.begin();
	_level.map().draw(sb);
    _player.render(sb);
	sb.end();
}

void
Game::handleEvent(const Event& event)
{
    if (event.type == Event::Type::KeyDown
        || event.type == Event::Type::KeyUp)
    {
        bool down = (event.type == Event::Type::KeyDown);

        switch (event.key)
        {
            case Key::Escape:
                Core::get().stop();
                break;
            case Key::Right:
                _player.setKey(KeyId::Right, down);
                break;
            case Key::Left:
                _player.setKey(KeyId::Left, down);
                break;
            case Key::Up:
                _player.setKey(KeyId::Up, down);
                break;
            case Key::Down:
                _player.setKey(KeyId::Down, down);
                break;
            case Key::Space:
                _player.setKey(KeyId::Space, down);
                break;
            default:
                break;
        }
    }
}

void
Game::unload()
{

}

Game::~Game()
{

}
