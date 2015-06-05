#ifndef TILE_HPP
#define TILE_HPP

#include <Lums>

#define TILE_SIZE	64

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

	static const Tile&			fromId(uint16_t id);

private:

	int							_boundingType;

};

#endif
