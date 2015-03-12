#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include "Map.hpp"

class Level
{
	friend class Game;
	typedef std::array<int, 6>	t_array6i;
public:

	Level();
	Level(const Level&) = delete;
	Level&		operator=(const Level&) = delete;

	void		load(int n);
	const Map&	map() const;
	void		setCurrent(int map);

private:
	std::vector<Map>						_maps;
	int										_current;
	std::vector<const t_array6i*>			_links;

	static std::vector<t_array6i>			_totalLinks;
};

#endif
