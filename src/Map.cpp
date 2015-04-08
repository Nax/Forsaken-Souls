#include <iostream>
#include "Map.hpp"
#include "ImageProvider.hpp"
#include "Screen.hpp"

Map::Map(std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&_width), sizeof(int32_t));
	file.read(reinterpret_cast<char*>(&_height), sizeof(int32_t));
	_tiles = new uint8_t[_width * _height];
	file.read(reinterpret_cast<char*>(_tiles), _width * _height);
}

Map::Map(Map&& rhs)
: _width(rhs._width)
, _height(rhs._height)
, _tiles(rhs._tiles)
{
	rhs._tiles = nullptr;
}

void
Map::setLinks(const std::vector<int32_t>& linkBuf, const int& mapNum)
{
	if (linkBuf.size() == 0)
		return;
	if (linkBuf.size() % 4 != 0)
	{
		std::cerr << "Invalid linkBuf size % 4 : " << linkBuf.size() % 4 << std::endl;
		return;
	}
	_links.clear();
	for (int i = 0; i < linkBuf.size(); i += 4)
	{
		if (linkBuf[i] == mapNum)
		{
			_links.push_back({{	
				linkBuf[i],
				linkBuf[i + 1],
				linkBuf[i + 2],
				linkBuf[i + 3]
				}});
		}
	}
}

uint32_t		
Map::width() const
{
	return _width;
}

uint32_t			
Map::height() const
{
	return _height;
}

const std::vector<Map::t_array4i>&
Map::links() const
{
	return _links;
}

const Tile&
Map::at(int at) const
{
	if (at < 0 || at >= _width * _height)
		return Tile::fromId(0);
	else
		return Tile::fromId(_tiles[at]);
}

const Tile&
Map::at(int x, int y) const
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return Tile::fromId(0);
	return Tile::fromId(_tiles[x + y * _width]);
}

void
Map::draw(lm::SpriteBatch& sb) const
{
	lm::Image& img = ImageProvider::get().image(ImageId::Tileset);

	for (int j = 0; j < _height; j++)
	{
		for (int i = 0; i < _width; i++)
		{
			sb.draw(img, _tiles[i + j * _width], {i * 32.f, SCREEN_HEIGHT - (j + 1) * 32.f});
		}
	}
}

Map::~Map()
{
	delete [] _tiles;
}
