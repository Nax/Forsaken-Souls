#include <iostream>
#include "Level.hpp"
#include <Lums/Lums.hpp>

Level::Level()
: _current(-1)
{

}

void	
Level::load(int n)
{
	char filename[] = "levels/level  .lvl";
	uint32_t mapCount;

	filename[12] = (n / 10) + '0';
	filename[13] = (n % 10) + '0';

	std::ifstream stream(lm::resourcePath() + '/' + filename, std::ios::binary);
	if (!stream.good())
	{
		std::cerr << "Error opening " << filename << std::endl;
		return;
	}
	stream.read(reinterpret_cast<char*>(&mapCount), 4);
	_maps.clear();

	std::cout << mapCount << std::endl;
	for (uint32_t i = 0; i < mapCount; ++i)
		_maps.emplace_back(stream);
	_current = 0;
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
