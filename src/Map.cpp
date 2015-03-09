
#include "Level.hpp"
#include "Map.hpp"

Map::Map()
	: _width(-1)
	, _height(-1)
	, _tiles(nullptr)
	, _level(nullptr)
{
}

Map::Map(const Level& lvl, const uint8_t *tiles, int width, int height)
	: _width(width)
	, _height(height)
	, _tiles(tiles)
	, _level(&lvl)
{
}

Map::Map(const Map& src)
{
	*this = src;
}

Map&	
Map::operator= (const Map& src)
{
	if (this != &src)
	{
		this->_width = src._width;
		this->_height = src._height;
		this->_tiles = src._tiles;
		this->_level = src._level;
	}
	return *this;
}

int		
Map::width(void) const
{
	return _width;
}

void	
Map::setWidth(int w)
{
	_width = w;
}


int			
Map::height(void) const
{
	return _height;
}

void			
Map::setHeight(int h)
{
	_height = h;
}


const uint8_t*	
Map::tiles(void) const
{
	return _tiles;
}


uint8_t		
Map::tileAt(int at) const
{
	return *(_tiles + at);
}

void		
Map::setTiles(uint8_t *tiles)
{
	_tiles = tiles;
}

const Level&
Map::level(void) const
{
	return *_level;
}

void	
Map::setLevel(const Level& lvl)
{
	_level = &lvl;
}

void
Map::draw()
{

}

Map::~Map()
{
}
