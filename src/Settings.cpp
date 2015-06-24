#include "Settings.hpp"


static void
load(SettingsMap& sm, bool& status)
{
 // TODO
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
operator<<(std::ostream& out, const ExplicitBool& v)
{
    ostream << (v.b ? "true" : "false");
    return ostream;
}

std::istream&
operator>>(std::istream& in, ExplicitBool& out)
{
    std::string     s;

    in >> s;
    out.b = (s == "true" || s == "True");
    return in;
}