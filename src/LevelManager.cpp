
#include <fstream>
#include <sstream>
#include <string>
#include <Lums/Lums.hpp>
#include "LevelManager.hpp"
#include "Level.hpp"
#include "Link.hpp"

LevelManager				*LevelManager::_instance = nullptr;

LevelManager::LevelManager()
	: _currentLevel(nullptr)
	, _linksData(nullptr)
	, _dataSize(0)
{
	bufferizeLinks();
}

LevelManager&				LevelManager::instance(void)
{
	if (LevelManager::_instance == nullptr)
		LevelManager::_instance = new LevelManager;
	return *LevelManager::_instance;
}

Level*						LevelManager::currentLevel(void) const
{
	return _currentLevel;
}

LevelManager::~LevelManager()
{
	if (_currentLevel)
		delete _currentLevel;
	if (_linksData)
		delete[] _linksData;
}

void						LevelManager::bufferizeLinks(void)
{
	std::ifstream			ifs;
	std::stringstream		sstr;
   
	sstr
		<< lm::resourcePath()
		<< "level_links.bin";
	ifs.open(sstr.str(), std::ios_base::binary);
	ifs.seekg(0, std::ios_base::end);
	_dataSize = ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	_linksData = new uint8_t[size];
	ifs.read(reinterpret_cast<char *>(_linksData), size);
	ifs.close();
}

void						LevelManager::setCurrentLevel(int levelNum)
{
	if (_currentLevel == nullptr)
		_currentLevel = new Level(levelNum);
	else
		*_currentLevel = Level::Level(levelNum);
}
