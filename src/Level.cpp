#include <iostream>
#include <Lums>
#include "Level.hpp"

std::vector<Level::t_array6i>		
Level::_totalLinks(0);

Level::Level()
: _current(-1)
{

}

void	
Level::load(int n)
{
	char filename[] = "levels/level  .lvl";
	uint32_t mapCount, mapLinkCount;
	std::vector<int32_t> mapLinkBuf(0);

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

	for (uint32_t i = 0; i < mapCount; ++i)
		_maps.emplace_back(stream);
	_current = 0;

	stream.read(reinterpret_cast<char*>(&mapLinkCount), sizeof(mapLinkCount));
	mapLinkBuf.resize(mapLinkCount * 4);
	for (uint32_t i = 0; i < mapLinkBuf.size(); ++i)
		stream.read(reinterpret_cast<char*>(&mapLinkBuf[i]), sizeof(int32_t));
	for (uint32_t i = 0; i < mapCount; ++i)
		_maps[i].setLinks(mapLinkBuf, i);

	_links.clear();
	for (const t_array6i& ar : _totalLinks)
	{
		if (ar[0] == n)	
			_links.push_back(&ar);
	}
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
