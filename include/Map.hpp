
#ifndef MAP_HPP
# define MAP_HPP

# include <cstdint>
# include <Lums/SpriteBatch.hpp>

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

	int				width() const;
	void			setWidth(int w);
	int				height() const;
	void			setHeight(int h);
	const uint8_t*	tiles() const;
	void			setTiles(uint8_t *ptr);
	uint8_t			tileAt(int at) const;
	const Level&	level() const;
	void			setLevel(const Level&);

	void			draw(lm::SpriteBatch &) const;

	~Map();

	private:

	int				_width;
	int				_height;
	const uint8_t	*_tiles;
	const Level		*_level;
};

#endif
