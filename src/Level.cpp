
#include <fstream>
#include <utility>
#include <sstream>
#include <iomanip>
#include <Lums/Lums.hpp>
#include "Level.hpp"
#include "Map.hpp"
#include "InnerLink.hpp"

Level::Level(int levelNum)
	: _data(nullptr)
	, _dataSize(0)
	, _levelNum(levelNum)
	, _nmaps(0)
	, _currentMap(-1)
	, _mapsArray(nullptr)
	, _nlinks(0)
	, _innerLinksByMap(nullptr)
{
	parseBinaryLevel(levelNum);
}

Level::Level(Level&& move_src)
	: _data(std::move(move_src._data))
	, _dataSize(std::move(move_src._dataSize))
	, _levelNum(std::move(move_src._levelNum))
	, _nmaps(std::move(move_src._nmaps))
	, _currentMap(std::move(move_src._currentMap))
	, _mapsArray(std::move(move_src._mapsArray))
	, _nlinks(std::move(move_src._nlinks))
	, _innerLinksByMap(std::move(move_src._innerLinksByMap))
{
}

Level&			
Level::operator=(Level&& move_src)
{
	if (this != &move_src)
	{
		std::swap(_data, move_src._data);
		std::swap(_dataSize, move_src._dataSize);
		std::swap(_levelNum, move_src._levelNum);
		std::swap(_nmaps, move_src._nmaps);
		std::swap(_currentMap, move_src._currentMap);
		std::swap(_mapsArray, move_src._mapsArray);
		std::swap(_nlinks, move_src._nlinks);
		std::swap(_innerLinksByMap, move_src._innerLinksByMap);
	}
	return *this;
}

size_t			
Level::dataSize(void) const
{
	return _dataSize;
}

int					
Level::nMaps(void) const
{
	return _nmaps;
}

int	
Level::currentMap(void) const
{
	return _currentMap;
}

void	
Level::setCurrentMap(int mapNum)
{
	_currentMap = mapNum;
}

const Map&				
Level::map(void) const
{
	return _mapsArray[_currentMap];
}

const Map&				
Level::mapAt(int at) const
{
	return _mapsArray[at];
}

int	
Level::levelNum(void) const
{
	return _levelNum;
}

int	
Level::nLinks(void) const
{
	return _nlinks;
}

void
Level::parseBinaryLevel(int levelNum)
{
	std::ifstream		ifs;
	std::stringstream	sstr;
	uint8_t				*pdata;
   
	sstr
		<< lm::resourcePath()
		<< "levels/level"
		<< std::setfill('0')
		<< std::setw(2)
		<< levelNum
		<< ".lvl";
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

		map.setLevel(*this);
	}

	_nlinks = *reinterpret_cast<int32_t *>(pdata);
	pdata += sizeof(int32_t);
	_innerLinksByMap = new std::list<InnerLink>[_nlinks];

	for (int i = 0; i < _nlinks; ++i)
	{
		InnerLink link;

		link.start.map = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);
		link.start.chunk = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);
		link.end.map = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);
		link.end.chunk = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);

		_innerLinksByMap[link.start.map].push_back(link);
	}
}

/**
 * Returns a reference to a list of the level's inner links,
 * corresponding to the provided map number.
 */
const std::list<InnerLink>&
Level::innerLinks(int mapnum) const
{
	return _innerLinksByMap[mapnum];
}

Level::~Level()
{
	delete[] _innerLinksByMap;
	delete[] _mapsArray;
	delete[] _data;
}

