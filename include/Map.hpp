
#ifndef MAP_HPP
# define MAP_HPP

# include <cstdint>

/**
 * Instantiatied by a Level object and holding values and pointers,
 * class Map is a flyweight to a parcel of a Level object's data.
 */

class Level;

class Map
{
	public:

	Map();

	explicit Map(const Level& lvl, const uint8_t *tiles, int width, int height);
	Map(const Map&);
	Map&			operator= (const Map&);

	int				width(void) const;
	void			setWidth(int w);
	int				height(void) const;
	void			setHeight(int h);
	const uint8_t*	tiles(void) const;
	void			setTiles(uint8_t *ptr);
	uint8_t			tileAt(int at) const;
	const Level&	level(void) const;
	void			setLevel(const Level&);

	~Map();

	private:

	int				_width;
	int				_height;
	const uint8_t	*_tiles;
	const Level		*_level;
};

#endif
