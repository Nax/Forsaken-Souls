#ifndef MAP_HPP
#define MAP_HPP

#include <cstdint>
#include <fstream>
#include <Lums/Lums.hpp>
#include <Tile.hpp>

/*
 * Instantiatied by a Level object and holding values and pointers,
 * class Map is a flyweight to a parcel of a Level object's data.
 */

class Map
{
public:
	Map(std::ifstream& file);
	Map(const Map&) = delete;
	Map(Map&& rhs);
	Map&	operator=(const Map&) = delete;
	uint32_t		width() const;
	uint32_t		height() const;
	const Tile&		at(int at) const;
	const Tile&		at(int x, int y) const;
	void			draw(lm::SpriteBatch& sb) const;
	~Map();

private:
	uint32_t		_width;
	uint32_t		_height;
	uint8_t*		_tiles;
};

#endif
