#include "Game.hpp"

using namespace lm;

Game::Game()
: _right(false)
, _left(false)
, _up(false)
, _down(false)
, _space(false)
{

}

void
Game::update()
{
    bool moving;

    moving = (_left && !_right) || (_right && !_left);

    if (moving)
        (_left) ? _player.setDirection(false) : _player.setDirection(true);
 
    // TO DO stence and old stence update


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
                _right = true;
                break;
            case Key::Left:
                _left = true;
                break;
            case Key::Up:
                _up = true;
                break;
            case Key::Down:
                _down = true;
                break;
            case Key::Space:
                _space = true;
                break;           
            default:
                break;
        }
    }
    else if (event.type == Event::Type::KeyUp)
    {
        switch (event.key)
        {
            case Key::Right:
                _right = false;
                break;
            case Key::Left:
                _left = false;
                break;
            case Key::Up:
                _up = false;
                break;
            case Key::Down:
                _down = false;
                break;
            case Key::Space:
                _space = false;
                break;           
            default:
                break;
        }
    }
}

Game::~Game()
{

}