
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <Lums/Lums.hpp>
#include "Level.hpp"
#include "Map.hpp"

Level::Level(int levelnum) :
	_data(nullptr),
	_dataSize(0),
	_levelNum(-1),
	_nmaps(0),
	_currentMap(-1),
	_mapsArray(nullptr)
{
	std::ifstream		ifs;
	std::stringstream	sstr;
	uint8_t				*pdata;
   
	sstr << lm::resourcePath() << "levels/level" << std::setfill('0')
		<< std::setw(2) << levelnum << ".lvl";
	ifs.open(sstr.str(), std::ios_base::binary);
	ifs.seekg(0, std::ios_base::end);
	_dataSize = ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	_data = new uint8_t[_dataSize];
	ifs.read(reinterpret_cast<char *>(_data), _dataSize);
	ifs.close();

	pdata = _data;
	_nmaps = *reinterpret_cast<int32_t *>(pdata);
	_mapsArray = new Map[_nmaps];
	pdata += sizeof(int32_t);

	for (int i = 0; i < _nmaps; ++i)
	{
		Map		&map = _mapsArray[i];

		map.setWidth(*reinterpret_cast<int32_t *>(pdata));
		pdata += sizeof(int32_t);
		map.setHeight(*reinterpret_cast<int32_t *>(pdata));
		pdata += sizeof(int32_t);
		map.setTiles(pdata);
		pdata += map.width() * map.height();
	}
}

Level::Level(Level&& move_src) :
	_data(nullptr),
	_dataSize(0),
	_levelNum(-1),
	_nmaps(0),
	_currentMap(-1),
	_mapsArray(nullptr)
{
	*this = std::move(move_src);
}

Level&					Level::operator=(Level&& move_src)
{
	if (this != &move_src)
	{
		_data = std::move(move_src._data);
		_dataSize = std::move(move_src._dataSize);
		_levelNum = std::move(move_src._levelNum);
		_nmaps = std::move(move_src._nmaps);
		_currentMap = std::move(move_src._currentMap);
		_mapsArray = std::move(move_src._mapsArray);
	}
	return *this;
}

size_t					Level::dataSize(void) const
{
	return _dataSize;
}

int						Level::nMaps(void) const
{
	return _nmaps;
}

int						Level::currentMap(void) const
{
	return _currentMap;
}

void					Level::setCurrentMap(int mapNum)
{
	_currentMap = mapNum;
}

const Map&				Level::map(void) const
{
	return _mapsArray[_currentMap];
}

const Map&				Level::mapAt(int at) const
{
	return _mapsArray[at];
}

int						Level::levelNum(void) const
{
	return _levelNum;
}

Level::~Level()
{
	delete[] _data;
	delete[] _mapsArray;
}
