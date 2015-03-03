
#ifndef MAP_HPP
# define MAP_HPP

# include <cstdint>

// class Level instantiates class Map with the proper values
// including a pointer to the first tile offset in memory. 

class Map
{
	public:

	Map() = delete;

	explicit Map(const uint8_t *tiles, int width, int height);
	Map(const Map&);
	Map&			operator= (const Map&);

	int				width(void) const;
	int				height(void) const;
	const uint8_t*	tiles(void) const;
	uint8_t			tileAt(int at) const;

	~Map();

	private:

	int				_width;
	int				_height;
	const uint8_t	*_tiles;
};

#endif
