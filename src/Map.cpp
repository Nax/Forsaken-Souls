#include <iostream>
#include "Map.hpp"
#include "ImageProvider.hpp"
#include "Screen.hpp"

Map::Map(std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&_width), sizeof(int32_t));
	file.read(reinterpret_cast<char*>(&_height), sizeof(int32_t));
	_tiles = new uint16_t[_width * _height * MAP_DEPTH];
	file.read(reinterpret_cast<char*>(_tiles), _width * _height * MAP_DEPTH * 2);
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

uint16_t
Map::indexAt(int x, int y, int z) const
{
    if (x < 0 || x >= _width || y < 0 || y >= _height)
        return 0;
    return _tiles[x + y * _width + z * _width * _height];
}

const Tile&
Map::at(int x, int y, int z) const
{
	return Tile::fromId(indexAt(x, y, z));
}

void
Map::draw(lm::SpriteBatch& sb, const Camera& camera, int z) const
{
	lm::Image& img = ImageProvider::get().image(ImageId::Tileset);
	const lm::Vector2f& off = camera.offset();
    const int minX = off.x;
    const int maxX = std::min<int>(ceil(off.x + SCREEN_TILES_W), _width);
    const int minY = off.y;
    const int maxY = std::min<int>(ceil(off.y + SCREEN_TILES_H), _height);

    for (int j = minY; j < maxY; ++j)
	{
		for (int i = minX; i < maxX; ++i)
		{
			const uint16_t tileId = _tiles[i + j * _width + z * _width * _height];

			if (tileId != 0)
				sb.draw(img, tileId - 1, {(i - off.x) * TILE_SIZE, SCREEN_HEIGHT - ((j - off.y) + 1) * TILE_SIZE}, {0.5, 0.5});
		}
	}
}

Map::~Map()
{
	delete [] _tiles;
}
