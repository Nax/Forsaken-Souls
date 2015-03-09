
#ifndef TILE_HPP
#define TILE_HPP

#include <Lums/Lums.hpp>

struct TileBoundingBox
{
	int			count;
	lm::Rect2f	boxes[8];
};

class Tile
{
public:

	Tile(int boundingType);

	const TileBoundingBox&		boundingBoxes() const;

private:

	int				_boundingType;

};

#endif
