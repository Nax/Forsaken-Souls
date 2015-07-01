#include "Settings.hpp"
#include <fstream>

#include <iostream>


// TODO :  Move to a file IO manager instance.
static const std::string        appDataPath = lm::userDataPath() + "Forsaken Souls/";
static const std::string        settingsFile = appDataPath + "settings.conf";
// ------------

const Settings::SettingToActionArray    Settings::_settingToActionA =
{
    MappedActions::Left
    , MappedActions::Left
    , MappedActions::Left
    , MappedActions::Right
    , MappedActions::Jump
    , MappedActions::Crouch
    , MappedActions::Attack
};


void
Settings::storeConfiguration()
{
    const SettingsArray&    settings = const_cast<const SettingsArray&>(_valA);
    std::ofstream           file(settingsFile, std::ios_base::trunc | std::ios_base::out);

    if (!file.good())
    {
        _bad = true;
        return;
    }

    for (short i = 0; i < static_cast<short>(SettingsEntry::Count) && file.good(); ++i)
    {
        std::stringstream     ssline;

        ssline << _serializerA[i] << " : " << settings[i] << " ;" << std::endl;
        file.write(ssline.str().c_str(), ssline.str().size());
    }

    _bad = !file.good();
}

std::ostream&
operator<<(std::ostream& lhs, const lm::Vector2i& rhs)
{
    std::string         ser;

    lhs << rhs.x << '_' << rhs.y;
    return lhs;
}

std::istream&   
operator>>(std::istream& in, lm::Vector2i& out)
{
    char sep;

    in >> out.x;
    in >> sep;
    in >> out.y;
    return in;
}

// Load settings from file.
// If it does not exist, create it with defaults.
void
Settings::load()
{
    std::ifstream   file(settingsFile);

    if (!file.good())
    {
        _bad = true;
        return;
    }
   
    while (!file.eof() && !file.fail() && !file.bad())
    {
        char                buf[1024];
        char                substr[128];
        std::stringstream   ss;
        std::string         tok;
        std::istringstream  iss;
        auto                mapIt = _deserializerM.end();

        file.getline(buf, sizeof(buf) - 1);
        iss.str(buf);

        // Get key part
        iss.getline(substr, sizeof(substr) - 1, ':');
        // Trim word from substr
        ss << substr;
        ss >> tok;

        mapIt = _deserializerM.find(tok);

        // Misshappen line ? continue.
        if (mapIt == _deserializerM.end())
            continue;
        
        tok.clear();
        ss.clear();
        ss.str(std::string());


        // Get value part
        iss.getline(substr, sizeof(substr) - 1, ';');
        // Trim word from substr
        ss << substr;
        ss >> tok;

        // Map iterator points to type std::pair<std::string, SettingsEntry>
        _valA[static_cast<short>(mapIt->second)] = tok;
    }

    _bad = !file.eof();

    if (_bad)
    {
        const std::string    reason = file.bad() ? "BAD" : "FAIL";

        // Then something bad happened.
        std::cerr << "Failed to read thoroughly : "
            << reason  << "bit." << std::endl;
    }
    else
        _unsynced = false;

    // Loading MappedKeys instance with loaded settings.
    {
        const std::vector<SettingsEntry>    kSettings
        {
            SettingsEntry::KeyLeft
            , SettingsEntry::KeyRight
            , SettingsEntry::KeyJump
            , SettingsEntry::KeyCrouch
            , SettingsEntry::KeyAttack
        };

        for (short i = 0; i < kSettings.size(); ++i)
        {
            std::stringstream   ss;
            short               iSetting;
            MappedActions       action;
            int                 kcode;

            iSetting = static_cast<short>(kSettings[i]);
            action = _settingToActionA[iSetting];
            ss.str(_valA[iSetting]);
            ss >> kcode;
            _keyMapping.actionKey(action) = static_cast<lm::Key>(kcode);
        }
    }
    // --- --- --- --- --- --- --- --- --- --- --- --- --- --- 
}

// Set string key to enum mapping here.
// Set default values here.
void
Settings::setDefaults()
{
    DeserializerMap&    desrlzM = const_cast<DeserializerMap&>(_deserializerM);
    SerializerArray&    srlzA = const_cast<SerializerArray&>(_serializerA);
    SettingsEntry       curEntry = static_cast<SettingsEntry>(0);
    std::stringstream   ss;

    // Relational initializations !

    ss.clear();
    ss.str(std::string());
    curEntry = SettingsEntry::GraphResolution;
    srlzA[static_cast<short>(curEntry)] = "GraphResolution";
    desrlzM[srlzA[static_cast<short>(curEntry)]] = curEntry;
    ss << lm::Vector2i{1280, 800};
    _valA[static_cast<short>(curEntry)] = ss.str();

    ss.clear();
    ss.str(std::string());
    curEntry = SettingsEntry::GraphFullScreen;
    srlzA[static_cast<short>(curEntry)] = "GraphFullScreen";
    desrlzM[srlzA[static_cast<short>(curEntry)]] = curEntry;
    ss << ExplicitBool(false);
    _valA[static_cast<short>(curEntry)] = ss.str();

    // Key mapping --- --- --- --- 
    {
        const std::vector<MappedActions>      mappedActions
        {
            MappedActions::Left
            , MappedActions::Right
            , MappedActions::Jump
            , MappedActions::Crouch
            , MappedActions::Attack
        };
        const std::vector<SettingsEntry>      keySettings
        {
            SettingsEntry::KeyLeft
            , SettingsEntry::KeyRight
            , SettingsEntry::KeyJump
            , SettingsEntry::KeyCrouch
            , SettingsEntry::KeyAttack
        };
        // These will be the serialized keymapping Settings Keys.
        const std::vector<std::string>        settingStrs
        {
            "KeyLeft"
            , "KeyRight"
            , "KeyJump"
            , "KeyCrouch"
            , "KeyAttack"
        };
    
        for (int i = 0; i < keySettings.size(); ++i)
        {
            ss.clear();
            ss.str(std::string());
            curEntry = keySettings[i];
            srlzA[static_cast<short>(curEntry)] = settingStrs[i];
            desrlzM[srlzA[static_cast<short>(curEntry)]] = curEntry;
            ss << static_cast<int>(_keyMapping.actionKey(mappedActions[i]));
            _valA[static_cast<short>(curEntry)] = ss.str();
        }

    }
    // --- --- --- --- --- 

    // More ...
}

Settings::Settings()
: _deserializerM(*new DeserializerMap)
, _serializerA(*new SerializerArray)
, _valA(*new SettingsArray)
, _bad(true)
, _unsynced(false)
{
    setDefaults();
	load();
    if (_bad)
    {
        std::cerr
            << __func__ << " : "
            << "Failed to read existing configuration at "
            << settingsFile << std::endl
            << "Writing defaults... " << std::endl; 
        storeConfiguration();
        if (_bad)
        {
            std::cerr
                << "Failed to write default configuration at "
                << settingsFile << std::endl; 
        }
    }
}

void
Settings::store()
{
    if (!_unsynced)
        return;
    storeConfiguration();
    if (_bad)
    {
        std::cerr
            << "Failed to write configuration at "
            << settingsFile << std::endl;
    }
    else
        _unsynced = false;
}

void
Settings::reload()
{
    if (!_unsynced)
        return;
    load();
    if (_bad)
    {
        std::cerr
            << __func__ << " : "
            << "Failed to read existing configuration at "
            << settingsFile << std::endl; 
    }
}

Settings::~Settings()
{
	delete &_deserializerM;
    delete &_serializerA;
    delete &_valA;
}



std::ostream&
operator<<(std::ostream& o, const Settings::ExplicitBool& v)
{
    o << (v.b ? "true" : "false");
    return o;
}

std::istream&
operator>>(std::istream& in, Settings::ExplicitBool& out)
{
    std::string     s;

    in >> s;
    out.b = (s == "true" || s == "True");
    return in;
}