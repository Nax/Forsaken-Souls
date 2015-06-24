#include "Settings.hpp"
#include <fstream>

#include <iostream>

static const std::string        appDataPath = lm::userDataPath() + "Forsaken Souls/";
static const std::string        settingsFile = appDataPath + "settings.conf";

#define DEFAULT_SETTINGS       "GraphicsResolution : 2560 1440;\nGraphicsFullscreen : False;\n"

static void
dumpDefaults(bool& isBad)
{
    std::ofstream   file(settingsFile, std::ios_base::trunc | std::ios_base::out);


    if (!file.good())
    {
        isBad = true;
        std::cerr
            << "Failed to write default configuration  "
            << appDataPath << std::endl; 
        return;
    }

    // Temporary
    const std::string     defaults(DEFAULT_SETTINGS);
    file.write(defaults.c_str(), defaults.size());
    // TODO
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


static void
load(SettingsMap& sm, bool& isBad)
{
    std::ifstream   file(settingsFile);

    if (!file.good())
    {
        dumpDefaults(isBad);

        if (isBad)
            return;
        else
        {
            // Now retry
            file.open(appDataPath);
            if (!file.good())
            {
                isBad = true;
                std::cerr
                    << "Failed to write default configuration  "
                    << appDataPath << std::endl; 
                return;
            }
        }
    }
   
    while (!file.eof() && !file.fail() && !file.bad())
    {
        char     buf[1024];
        std::stringstream   ss;
        std::string         line, prop, val;
        std::istringstream  iss;
        lm::Vector2i        res;

        file.getline(buf, sizeof(buf) - 1);
        // std::cout << "Read line: " << buf << std::endl; 
        ss << buf;
        ss >> line;
        // std::cout << "Prop ? " << line << std::endl;
        ss.clear();
        iss.str(buf);
        iss.getline(buf, sizeof(buf) - 1, ':');
        // std::cout << "stuff A ? " << buf << std::endl;
        ss << buf;
        ss >> prop;
        ss.clear();
        iss.getline(buf, sizeof(buf) - 1, ';');
        ss.str(buf);
        // std::cout << "stuff B ? " << buf << std::endl;
        ss << buf;
        ss >> res;
        // std::cout << "Value ? " << res << std::endl;

        (void)sm;
        // TODO
    }
    isBad = !file.eof();
    if (isBad)
    {
        const std::string    reason = file.bad() ? "BAD" : "FAIL";

        // Then something bad happened.
        std::cerr << "Failed to read thoroughly : " << reason << std::endl; 
    }
}

Settings::Settings()
: _smap(*new SettingsMap)
, _bad(true)
{
	load(_smap, _bad);
}

void
Settings::store()
{
 // TODO
}

void
Settings::reload()
{
    load(_smap, _bad);
}

Settings::~Settings()
{
	delete &_smap;
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