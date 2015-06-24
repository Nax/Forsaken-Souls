#include "Settings.hpp"
#include <istream>

#include <iostream>

static const std::string        appDataPath = lm::userDataPath() + "Forsaken Souls";

static void
load(SettingsMap& sm, bool& isBad)
{
    std::ifstream   file(appDataPath, std::ios_base::in);

    if (!file.good())
    {
        isBad = true;
        std::cerr << "Failed to open  " << appDataPath << std::endl; 
        return;
    }
   
    while (!file.eof() && !file.fail() && !file.bad())
    {
        char     prop[128], value[128];

        file.getline(prop, sizeof(prop) - 1, ':');
        std::cout << "Got prop: " << prop << std::endl;
        file.getline(value, sizeof(value) - 1, ';');
        std::cout << "Got value: " << value << std::endl;
        (void)sm;
    }
    if (!file.eof())
    {
        const std::string    reason = file.bad() ? "BAD" : "FAIL";

        // Then something bad happened.
        isBad = true;
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
operator<<(std::ostream& lhs, const lm::Vector2i& rhs)
{
    std::string         ser;

    lhs << rhs.x << ' ' << rhs.y;
    return lhs;
}

std::istream&   
operator>>(std::istream& in, const lm::Vector2i& out)
{
    in >> out.x;
    in >> out.y;
    return in;
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