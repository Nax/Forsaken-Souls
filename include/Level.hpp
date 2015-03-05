

#ifndef LEVEL_HPP
# define LEVEL_HPP

# include <cstdint>
# include <string>

class Map;

class Level
{
	public:

		Level() = delete;
		Level(const Level&) = delete;
		Level&			operator=(const Level&) = delete;

		explicit Level(int levelNum);
		Level(Level&&);
		Level&			operator=(Level&&);

		size_t			dataSize(void) const;
		int				nMaps(void) const;
		int				currentMap(void) const;
		const Map&		map(void) const;
		void			setCurrentMap(int mapNum);
		const Map&		mapAt(int at) const;
		int				levelNum(void) const;

		~Level();

	private:

		uint8_t				*_data;
		size_t				_dataSize;
		int32_t				_levelNum;
		int32_t				_nmaps;
		int					_currentMap;
		Map					*_mapsArray;

		void				parseBinaryLevel(int levelNum);
};

#endif
