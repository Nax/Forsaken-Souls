#include "Settings.hpp"
#include <fstream>

static const std::string appDataPath = lm::userDataPath() + "Forsaken Souls/";
static const std::string settingsFile = appDataPath + "settings.conf";

Settings::Settings()
{
    lm::mkAppDataDir(appDataPath.c_str());

    _settings["resolution"] = "1280x800";
    _settings["lang"] = "en";
    _settings["fullscreen"] = "0";

    std::ifstream file(settingsFile);
    while (file.good())
    {
        std::string key, value;
        file >> key >> value;
        _settings[key] = value;
    }
}

void
Settings::save()
{
    std::ofstream file(settingsFile);
    for (auto it = _settings.begin(); it != _settings.end(); ++it)
        file << it->first << " " << it->second << std::endl;
}
