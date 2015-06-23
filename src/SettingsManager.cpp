#include "SettingsManager.hpp"

// const std::map<SettingsManager::Entry, std::vector<SettingsManager::DataType>>
// SettingsManager::_typeMapping = {
// 	{SettingsManager::Entry::GraphResolution, {SettingsManager::DataType::Integer, SettingsManager::DataType::Integer}}
// 	, {SettingsManager::Entry::GraphFullScreen, {SettingsManager::DataType::Boolean}}
// };

SettingsManager::SettingsManager()
: _smap(*new SettingsMap)
{
	
}

bool
SettingsManager::sync() const
{

}

~SettingsManager::SettingsManager()
{
	delete &_smap;
}