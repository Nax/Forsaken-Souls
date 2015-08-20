#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <unordered_map>
#include <Lums>

class Settings : public lm::Singleton<Settings>
{
public:
    Settings();
    const std::string&      get(const std::string& str) const { return _settings.at(str); }
    void                    set(const std::string& key, const std::string& value) { _settings[key] = value; }
    void                    save();

private:
    std::unordered_map<std::string, std::string>    _settings;
};
#endif
