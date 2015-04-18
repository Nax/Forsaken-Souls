
#include "Tile.hpp"

static const TileBoundingBox boxes[] = {
	{0},
	{1, {{0, 0, 1, 1}}}
};

static const Tile tiles[] = {
    {0},
	{0},
	{0},
	{0},
	{1},
	{1},
	{1},
	{1},
	{1},
	{1}
};

Tile::Tile(int boundingType)
: _boundingType(boundingType)
{

}

const TileBoundingBox&
Tile::boundingBoxes() const
{
	return boxes[_boundingType];	
}

const Tile&		
Tile::fromId(uint8_t id)
{
	return tiles[id];
}
