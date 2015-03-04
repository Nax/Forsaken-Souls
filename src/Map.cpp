
#include "Map.hpp"

Map::Map() :
	_width(-1),
	_height(-1),
	_tiles(nullptr)
{

}

Map::Map(const uint8_t *tiles, int width, int height) :
	_width(width),
	_height(height),
	_tiles(tiles)
{
		// Todo : check 4-aligned map size, supplied values, else throw
}

Map::Map(const Map& src)
{
	*this = src;
}

Map&				Map::operator= (const Map& src)
{
	if (this != &src)
	{
		this->_width = src.width();
		this->_height = src.height();
		this->_tiles = src.tiles();
		// Todo : check 4-aligned map size, supplied values, else throw
	}
	return *this;
}

int					Map::width(void) const
{
	return (_width);
}

void				Map::setWidth(int w)
{
	_width = w;
}


int					Map::height(void) const
{
	return (_height);
}

void				Map::setHeight(int h)
{
	_height = h;
}


const uint8_t*		Map::tiles(void) const
{
	return (this->_tiles);
}


uint8_t				Map::tileAt(int at) const
{
	if (at < 0 || at >= _width * _height)
		// Todo : throw or something if out-of-bounds
		return (0);
	else
		return (*(_tiles + at));
}

void				Map::setTiles(uint8_t *tiles)
{
	_tiles = tiles;
}


Map::~Map()
{
}
