#include "Map.hpp"
#include "ImageProvider.hpp"

Map::Map(std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&_width), 4);
	file.read(reinterpret_cast<char*>(&_height), 4);
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
			sb.draw(img, _tiles[i + j * _width], lm::Vector2f(i * 32, j * 32));
		}
	}
}

Map::~Map()
{
	delete [] _tiles;
}
