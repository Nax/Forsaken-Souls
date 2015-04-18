#include <iostream>
#include "Map.hpp"
#include "ImageProvider.hpp"
#include "Screen.hpp"

Map::Map(std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&_width), sizeof(int32_t));
	file.read(reinterpret_cast<char*>(&_height), sizeof(int32_t));
	_tiles = new uint8_t[_width * _height * MAP_DEPTH];
	file.read(reinterpret_cast<char*>(_tiles), _width * _height * MAP_DEPTH);
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

// Maybe we should deprecate this.
// It's used 0 times.
const Tile&
Map::at(int at) const
{
	if (at < 0 || at >= _width * _height * MAP_DEPTH)
		return Tile::fromId(0);
	else
		return Tile::fromId(_tiles[at]);
}

const Tile&
Map::at(int x, int y, int z) const
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return Tile::fromId(0);
	return Tile::fromId(_tiles[x + y * _width + z * _width * _height]);
}

void
Map::draw(lm::SpriteBatch& sb, const Camera& camera) const
{
	lm::Image& img = ImageProvider::get().image(ImageId::Tileset);
	const lm::Vector2f& off = camera.offset();

	for (int z = 0; z < MAP_DEPTH; ++z)
	{	
		z = 2; // HACK
		for (int j = _height; j >= 0; --j)
		{
			for (int i = 0; i < _width; ++i)
			{
				const uint8_t tileId = _tiles[i + j * _width + z * _width * _height];
	
				if (tileId != 0) // HACK: no empty at #0
					sb.draw(img, tileId - 1, {(i - off.x) * 32.f, SCREEN_HEIGHT - ((j - off.y) + 1) * 32.f}, {0.25f, 0.25f});
			}
		}
		break ; //HACK
	}
}

Map::~Map()
{
	delete [] _tiles;
}
