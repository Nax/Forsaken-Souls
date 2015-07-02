#include "Settings.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>

#include <iostream>


// TODO :  Move to a file IO manager instance.
namespace
{
    const std::string        appDataPath = lm::userDataPath() + "Forsaken Souls/";
    const std::string        settingsFile = appDataPath + "settings.conf";
}
// ------------

const Settings::SettingToActionArray    Settings::_settingToActionA =
{{
    MappedActions::Left
    , MappedActions::Left
    , MappedActions::Left
    , MappedActions::Right
    , MappedActions::Jump
    , MappedActions::Crouch
    , MappedActions::Attack
}};


std::istream&   
operator>>(std::istream& in, lm::Vector2i& out)
{
    bool fail = false;
    char sep;

    in >> out.x;
    fail |= in.fail();
    in >> sep;
    fail |= in.fail() || (sep != '_');
    in >> out.y;
    fail |= in.fail();
    if (fail)
        in.setstate(std::ios::failbit);
    return in;
}

std::istream&
operator>>(std::istream& in, Settings::ExplicitBool& out)
{
    std::string     s, res;
    bool            logicalResult;
    auto            toLower = [](char c) { return static_cast<char>(std::tolower(c)); };

    in >> s;
    res.resize(s.size());
    std::transform(s.begin(), s.end(), res.begin(), toLower);
    logicalResult = (s == "true");
    out.b = logicalResult;
    if (!logicalResult && (s != "false"))
    {
        // Notify parse error through failbit
        in.setstate(std::ios::failbit);
    }
    return in;
}

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
    return (lhs << rhs.x << '_' << rhs.y);
}


// Load settings from file.
// load() assumes the Settings instance is already initialized
// with defaults.
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

        // Get the key part of the line.
        iss.getline(substr, sizeof(substr) - 1, ':');
        // Trim word from 'substr' buffer
        ss << substr;
        ss >> tok;

        mapIt = _deserializerM.find(tok);

        // Misshappen key ? skip to next.
        if (mapIt == _deserializerM.end())
            continue;
        
        tok.clear();
        ss.clear();
        ss.str(std::string());

        // Get the value part of the line.
        iss.getline(substr, sizeof(substr) - 1, ';');
        // Trim word from 'substr' buffer
        ss << substr;
        ss >> tok;

        // Reminder :
        // Map iterator points to type std::pair<std::string, SettingsEntry>
        
        // Keep default unless conversion is flawless.
        // TODO: validate values VS supported values (resolution, key bindings...).
        if (validate(mapIt->second, tok))
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




bool
Settings::validate(SettingsEntry e, std::string s)
{
    std::stringstream   ss(s);
    bool                result = false;

    switch (e)
    {
        // Boolean settings
        case SettingsEntry::GraphFullScreen:
        {
            bool stor;
            
            result = tryConvertToType<bool>(s, stor);
            break;
        }

        // lm::Vector2i settings
        case SettingsEntry::GraphResolution:
        {
            lm::Vector2i stor;
            
            result = tryConvertToType<lm::Vector2i>(s, stor);
            break;
        }

        // lm::Key || int settings
        case SettingsEntry::KeyLeft:
        case SettingsEntry::KeyRight:
        case SettingsEntry::KeyJump:
        case SettingsEntry::KeyCrouch:
        case SettingsEntry::KeyAttack:
        {
            lm::Key stor;
            
            result = tryConvertToType<lm::Key>(s, stor);
            break;
        }
        
        default:
            break;
    }

    return result;
}

