#include "Game.hpp"

using namespace lm;

Game::Game()
{

}

void
Game::update()
{
    _player.update();
}

void
Game::render() const
{
    _player.render();
}

void
Game::handleEvent(const Event& event)
{
    if (event.type == Event::Type::KeyDown)
    {
        switch (event.key)
        {
            case Key::Escape:
                Core::get().stop();
                break;
            case Key::Right:
                _player.setKey(KeyId::Right, true);
                break;
            case Key::Left:
                _player.setKey(KeyId::Left, true);
                break;
            case Key::Up:
                _player.setKey(KeyId::Up, true);
                break;
            case Key::Down:
                _player.setKey(KeyId::Down, true);
                break;
            case Key::Space:
                _player.setKey(KeyId::Space, true);
                break;
            default:
                break;
        }
    }
    else if (event.type == Event::Type::KeyUp)
    {
        switch (event.key)
        {
            case Key::Escape:
                Core::get().stop();
                break;
            case Key::Right:
                _player.setKey(KeyId::Right, false);
                break;
            case Key::Left:
                _player.setKey(KeyId::Left, false);
                break;
            case Key::Up:
                _player.setKey(KeyId::Up, false);
                break;
            case Key::Down:
                _player.setKey(KeyId::Down, false);
                break;
            case Key::Space:
                _player.setKey(KeyId::Space, false);
                break;
            default:
                break;
        }
    }
}

Game::~Game()
{

}