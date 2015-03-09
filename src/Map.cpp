
#include "Level.hpp"
#include "Map.hpp"
#include "ImageProvider.hpp"

Map::Map()
: _width(-1)
, _height(-1)
, _tiles(nullptr)
{

}

int		
Map::width() const
{
	return _width;
}

int			
Map::height() const
{
	return _height;
}

uint8_t		
Map::at(int at) const
{
	if (at < 0 || at >= _width * _height)
		return 0;
	else
		return _tiles[at];
}

uint8_t
Map::at(int x, int y) const
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return 0;
	return _tiles[x + y * _width];
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
