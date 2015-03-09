
#include "Level.hpp"
#include "Map.hpp"
#include "ImageProvider.hpp"

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
Map::width() const
{
	return _width;
}

void	
Map::setWidth(int w)
{
	_width = w;
}


int			
Map::height() const
{
	return _height;
}

void			
Map::setHeight(int h)
{
	_height = h;
}


const uint8_t*	
Map::tiles() const
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
Map::level() const
{
	return *_level;
}

void	
Map::setLevel(const Level& lvl)
{
	_level = &lvl;
}

void
Map::draw(lm::SpriteBatch& sb) const
{
	lm::Image&		img = ImageProvider::get().image(ImageId::Tileset);

	for (int j = 0; j < _height; j++)
	{
		for (int i = 0; i < _width; i++)
		{
			sb.draw(img, i * 32, j * 32, _tiles[i + j * _width]);
		}
	}
}

Map::~Map()
{
}
