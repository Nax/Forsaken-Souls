#include <iostream>
#include "Game.hpp"
#include "Screen.hpp"

using namespace lm;

Game::Game()
: _large(false)
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
