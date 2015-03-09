
#include "Tile.hpp"

static const TileBoundingBox boxes[] = {
	{0},
	{1, {{0, 0, 1, 1}}}
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

