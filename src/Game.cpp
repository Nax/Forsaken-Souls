#include <iostream>
#include "Game.hpp"
#include "Screen.hpp"
#include "Hud.hpp"
#include "GameOver.hpp"

using namespace lm;

bool debugMode = true;

Game::Game()
: _gameOverTicks(0)
{
	char const*				file = "level_links.bin";
	int32_t					linkCount;
	std::ifstream			stream(lm::resourcePath() + '/' + file, std::ios::binary);

	if (!stream.good())
	{
		std::cerr << "Error opening " << file << std::endl;
		return;
	}
	stream.read(reinterpret_cast<char*>(&linkCount), sizeof(linkCount));

	Level::_totalLinks.resize(linkCount);
	for (t_array6i& lnkAr : Level::_totalLinks)
	{
		for (int& linkPart : lnkAr)
		{
			int32_t linkDWord;

			stream.read(reinterpret_cast<char*>(&linkDWord), sizeof(linkDWord));
			linkPart = static_cast<int>(linkDWord);
		}
	}
}

void
Game::load()
{
    _level.load(0);
}

void
Game::update()
{
    _player.update(_level.map());
    _camera.update(_player, _level.map());
    if (_player.dead())
        _gameOverTicks++;
    if (_gameOverTicks > 500)
        Core::get().transition<GameOver>();
}

void
Game::render() const
{
	lm::SpriteBatch sb;
    const Map& m = _level.map();

	sb.begin();
	m.draw(sb, _camera, 0);
    m.draw(sb, _camera, 1);
    m.draw(sb, _camera, 2);
    _player.render(sb, _camera);
    m.draw(sb, _camera, 3);
    m.draw(sb, _camera, 4);
	sb.end();
    hud::draw(_player);
    if (_gameOverTicks > 240)
    {
        const float alpha = 0.005f * (_gameOverTicks - 240);
        glColor4f(0, 0, 0, alpha);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(SCREEN_WIDTH, 0);
        glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
        glVertex2f(0, SCREEN_HEIGHT);
        glEnd();
    }
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
            case Key::D:
                if (down)
                    debugMode = !debugMode;
                break;
            case Key::X:
                _player.die();
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
