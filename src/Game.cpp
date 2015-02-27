#include "Game.hpp"

using namespace lm;

Game::Game()
{

}
	
void
Game::update()
{

}

void
Game::render() const
{

}

void
Game::unload()
{

}

void
Game::load()
{

}

void
Game::handleEvent(const Event& event)
{
	if (event.type == Event::Type::KeyUp && event.key == Key::Escape)
		Core::get().stop();
}

Game::~Game()
{

}