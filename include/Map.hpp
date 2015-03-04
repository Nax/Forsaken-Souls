
#ifndef MAP_HPP
# define MAP_HPP

# include <cstdint>

// class Level instantiates class Map with the proper values
// including a pointer to the first tile offset in memory. 

class Map
{
	public:

	Map();

	explicit Map(const uint8_t *tiles, int width, int height);
	Map(const Map&);
	Map&			operator= (const Map&);

	int				width(void) const;
	void			setWidth(int w);
	int				height(void) const;
	void			setHeight(int h);
	const uint8_t*	tiles(void) const;
	uint8_t			tileAt(int at) const;
	void			setTiles(uint8_t *tiles);

	~Map();

	private:

	int				_width;
	int				_height;
	const uint8_t	*_tiles;
};

#endif
