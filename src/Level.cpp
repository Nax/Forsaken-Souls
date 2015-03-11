#include <fstream>
#include <Lums/Lums.hpp>
#include "Level.hpp"

Level::Level()
: _current(-1)
{

}

void	
Level::load(int n)
{
	char filename[] = "levels/level  .lvl";
	uint32_t mapCount, linkCount, link;
	std::vector<int32_t> linkBuf(0);

	filename[12] = (n / 10) + '0';
	filename[13] = (n % 10) + '0';

	std::ifstream stream(lm::resourcePath() + '/' + filename, std::ios::binary);
	if (!stream.good())
	{
		std::cerr << "Error opening " << filename << std::endl;
		return;
	}
	stream.read(reinterpret_cast<char*>(&mapCount), sizeof(mapCount));
	_maps.clear();

	std::cout << mapCount << std::endl;
	for (uint32_t i = 0; i < mapCount; ++i)
		_maps.emplace_back(stream);
	_current = 0;

	stream.read(reinterpret_cast<char*>(&linkCount), sizeof(linkCount));
	linkBuf = std::vector<int32_t>(linkCount * 4);
	for (uint32_t i = 0; i < linkBuf.size(); ++i)
	{
		stream.read(reinterpret_cast<char*>(&link), sizeof(link));
		linkBuf[i] = link;
	}
	for (uint32_t i = 0; i < mapCount; ++i)
		_maps[i].setLinks(linkBuf, i);
}

const Map&				
Level::map() const
{
	return _maps[_current];
}

void
Level::setCurrent(int map)
{
	_current = map;
}
