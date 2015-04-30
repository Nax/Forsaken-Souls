#ifndef MAP_HPP
#define MAP_HPP

#include <cstdint>
#include <fstream>
#include <vector>
#include <array>
#include <Lums/Lums.hpp>
#include "Tile.hpp"
#include "Camera.hpp"

#define MAP_DEPTH	5

/*
 * Instantiatied by a Level object and holding values and pointers,
 * class Map is a flyweight to a parcel of a Level object's data.
 */

class Entity;

class Map
{
	friend class Level;
	typedef std::array<int, 4>		t_array4i;
public:
	Map(std::ifstream& file);
	Map(const Map&) = delete;
	Map(Map&& rhs);
	Map&							operator=(const Map&) = delete;
	uint32_t						width() const;
	uint32_t						height() const;
    uint16_t                        indexAt(int x, int y, int z = 2) const;
	const Tile&						at(int x, int y, int z = 2) const;
	void							draw(lm::SpriteBatch& sb, const Camera& camera, int z) const;
	const std::vector<t_array4i>&	links() const;
    void                            spawn(std::vector<Entity*>& entities) const;
	~Map();

private:
    struct Spawn
    {
        uint32_t x;
        uint32_t y;
        uint32_t id;
    };

	uint32_t				_width;
	uint32_t				_height;
	uint16_t*				_tiles;
	std::vector<t_array4i>	_links;
    std::vector<Spawn>      _spawns;

	void					setLinks(const std::vector<int32_t>& linkBuf, const int& mapNum);
};

#endif
