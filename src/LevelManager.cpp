
#include <fstream>
#include <sstream>
#include <string>
#include <Lums/Lums.hpp>
#include "LevelManager.hpp"

LevelManager
*LevelManager::_instance = nullptr;

LevelManager::LevelManager()
	: _currentLevel(nullptr)
	, _currentLevelNum(-1)
	, _nlinks(0)
	, _levelLinks(nullptr)
{
	bufferizeLinks();
}

LevelManager&		
LevelManager::instance(void)
{
	if (LevelManager::_instance == nullptr)
		LevelManager::_instance = new LevelManager;
	return *LevelManager::_instance;
}

Level&
LevelManager::currentLevel(void) const
{
	return *_currentLevel;
}

void			
LevelManager::bufferizeLinks(void)
{
	std::ifstream			ifs;
	std::stringstream		sstr;
	uint8_t					*pdata;
	uint8_t					*data_buffer;
	size_t					dataSize;
   
	sstr
		<< lm::resourcePath()
		<< "level_links.bin";
	ifs.open(sstr.str(), std::ios_base::binary);
	ifs.seekg(0, std::ios_base::end);
	dataSize = ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	data_buffer = new uint8_t[dataSize];
	pdata = data_buffer;
	ifs.read(reinterpret_cast<char *>(pdata), dataSize);
	ifs.close();
	
	_nlinks = *reinterpret_cast<int32_t *>(pdata);
	_levelLinks = new Link[_nlinks];
	pdata += sizeof(int32_t);
	
	for (int i = 0; i < _nlinks; ++i)
	{
		Link		&lnk = _levelLinks[i];

		lnk.start.level = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);
		lnk.start.map = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);
		lnk.start.chunk = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);
		lnk.end.level = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);
		lnk.end.map = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);
		lnk.end.chunk = *reinterpret_cast<int32_t *>(pdata);
		pdata += sizeof(int32_t);
	}

	delete[] data_buffer;
}

void			
LevelManager::setCurrentLevel(int levelNum)
{
	if (_currentLevel == nullptr)
		_currentLevel = new Level(levelNum);
	else
		*_currentLevel = Level::Level(levelNum);
	_currentLevelNum = levelNum;
}

int
LevelManager::currentLevelNum(void) const
{
	return _currentLevelNum;
}

int
LevelManager::nlinks(void) const
{
	return _nlinks;
}

const Link*
LevelManager::levelLinks(void) const
{
	return _levelLinks;
}

LevelManager::~LevelManager()
{
	delete _currentLevel;
	delete[] _levelLinks;
}
