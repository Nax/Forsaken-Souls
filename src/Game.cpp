#include <iostream>
#include "Game.hpp"

using namespace lm;

Game::Game()
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
