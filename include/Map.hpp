
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
	friend class Level;

	public:

	Map();

	Map(const Map&) = delete;
	Map&			operator= (const Map&) = delete;

	int				width() const;
	int				height() const;
	uint8_t			at(int at) const;
	uint8_t			at(int x, int y) const;

	void			draw(lm::SpriteBatch &) const;

	~Map();

	private:

	int				_width;
	int				_height;
	const uint8_t	*_tiles;
};

#endif
