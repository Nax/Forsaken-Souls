#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "Map.hpp"

class Level
{
public:

	Level();
	Level(const Level&) = delete;
	Level&		operator=(const Level&) = delete;

	void		load(int n);
	const Map&	map() const;
	void		setCurrent(int map);

private:
	std::vector<Map>	_maps;
	int					_current;
	
};

#endif
