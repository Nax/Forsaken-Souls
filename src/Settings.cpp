#include "Settings.hpp"
#include <fstream>

#include <iostream>


// TODO :  Move to a file IO manager instance.
static const std::string        appDataPath = lm::userDataPath() + "Forsaken Souls/";
static const std::string        settingsFile = appDataPath + "settings.conf";



static void
dumpConfiguration(const SerializerArray& serializer, const SettingsArray& settings, bool& isBad)
{
    std::ofstream   file(settingsFile, std::ios_base::trunc | std::ios_base::out);

    if (!file.good())
    {
        isBad = true;
        return;
    }

    for (short i = 0; i < static_cast<short>(SettingsEntry::Count) && file.good(); ++i)
    {
        std::stringstream     ssline;

        ssline << serializer[i] << " : " << settings[i] << " ;" << std::endl;
        file.write(ssline.str().c_str(), ssline.str().size());
    }

    isBad = !file.good();
}

std::ostream&
operator<<(std::ostream& lhs, const lm::Vector2i& rhs)
{
    std::string         ser;

    lhs << rhs.x << ' ' << rhs.y;
    return lhs;
}

std::istream&   
operator>>(std::istream& in, lm::Vector2i& out)
{
    in >> out.x;
    in >> out.y;
    return in;
}

// Load settings from file.
// If it does not exist, create it with defaults.
static void
load(const DeserializerMap& dsm, SettingsArray& settings, bool& isBad)
{
    std::ifstream   file(settingsFile);

    if (!file.good())
    {
        isBad = true;
        return;
    }
   
    while (!file.eof() && !file.fail() && !file.bad())
    {
        char                buf[1024], substr[128];
        std::stringstream   ss;
        std::string         tok;
        std::istringstream  iss;
        auto                mapIt = dsm.end();

        file.getline(buf, sizeof(buf) - 1);
        iss.str(buf);

        // Get key part
        iss.getline(substr, sizeof(substr) - 1, ':');
        // Trim !
        ss << substr;
        ss >> tok;

        mapIt = dsm.find(tok);

        // Misshappen line ? continue.
        if (mapIt == dsm.end())
            continue;
        
        tok.clear();
        ss.clear();

        // Get value part
        iss.getline(substr, sizeof(substr) - 1, ';');
        // Trim !
        ss << substr;
        ss >> tok;

        // Map iterator points to type std::pair<std::string, SettingsEntry>
        settings[static_cast<short>(mapIt->second)] = tok;
    }

    isBad = !file.eof();

    if (isBad)
    {
        const std::string    reason = file.bad() ? "BAD" : "FAIL";

        // Then something bad happened.
        std::cerr << "Failed to read thoroughly : "
            << reason  << "bit." << std::endl;
    }
}

// Set string key to enum mapping here.
// Set default values here.
static void
setDefaults(SettingsArray& settingsA, DeserializerMap& desrlzM, SerializerArray& srlzA)
{
    SettingsEntry   curEntry = static_cast<SettingsEntry>(0);

    // Relational initializations !

    curEntry = SettingsEntry::GraphResolution;
    srlzA[static_cast<short>(curEntry)] = "GraphResolution";
    desrlzM[srlzA[static_cast<short>(curEntry)]] = curEntry;
    settingsA[static_cast<short>(curEntry)] = "2560 1440";

    curEntry = SettingsEntry::GraphFullScreen;
    srlzA[static_cast<short>(curEntry)] = "GraphFullScreen";
    desrlzM[srlzA[static_cast<short>(curEntry)]] = curEntry;
    settingsA[static_cast<short>(curEntry)] = "false";
}

Settings::Settings()
: _deserializerM(*new DeserializerMap)
, _serializerA(*new SerializerArray)
, _valA(*new SettingsArray)
, _bad(true)
{
    setDefaults(_valA
        , const_cast<DeserializerMap&>(_deserializerM)
        , const_cast<SerializerArray&>(_serializerA)
    );
	load(_deserializerM, _valA, _bad);
    if (_bad)
    {
        std::cerr
            << __func__ << " : "
            << "Failed to read existing configuration at "
            << settingsFile << std::endl; 
        dumpConfiguration(_serializerA, _valA, _bad);
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
    dumpConfiguration(_serializerA, _valA, _bad);
    if (_bad)
    {
        std::cerr
            << "Failed to write configuration at "
            << settingsFile << std::endl;
    }
}

void
Settings::reload()
{
    load(_deserializerM, _valA, _bad);
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
operator<<(std::ostream& os, const Settings::ExplicitBool& v)
{
    os << (v.b ? "true" : "false");
    return os;
}

std::istream&
operator>>(std::istream& in, Settings::ExplicitBool& out)
{
    std::string     s;

    in >> s;
    out.b = (s == "true" || s == "True");
    return in;
}