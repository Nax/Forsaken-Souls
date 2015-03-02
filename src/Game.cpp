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
            default:
                break;
        }
    }
}

Game::~Game()
{

}