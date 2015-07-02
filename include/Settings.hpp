#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <map>
#include <string>
#include <sstream>
#include <array>
#include <Lums>
#include "MappedKeys.hpp"

// As of 279e0653d196b
//
// Settings is a lm::Singleton (i.e.: lazily constructed)
// Upon construction, the Settings instance initializes
// itself from the existing config file (loads defaults otherwise.)
// 
// Settings caches current settings and will not write to file
// unless a store() call is issued. Thus, calling get<E> / set<E>
// will not trigger disk IO by themselves.
//
// Settings manages internally an instance of the MappedKeys class.
// Any key-binding-related call to get<E> / set<E> will update the
// MappedKeys instance.
// Settings provides access to a const reference to the instance of
// MappedKeys to specifically query the actual key bindings.
//
// Settings provides a bad() accessor to enquire about a possible IO error.
// Settings provides a reload() method to reload settings from the config
// file (thus, destroying unsynced changes).

enum struct SettingsEntry : short
{
    GraphResolution = 0,
    GraphFullScreen,
    KeyLeft,
    KeyRight,
    KeyJump,
    KeyCrouch,
    KeyAttack,
    Count
};

namespace
{
    // Defining type mapping to Settings::Entry values.
    // Impossible in class scope.

    template <SettingsEntry E>
    struct EntryType
    {
        static_assert(E < SettingsEntry::Count, "Invalid Settings::Entry template value.");
        typedef void type;
    };

    template <> struct EntryType<SettingsEntry::GraphResolution>    { typedef lm::Vector2i type; };
    template <> struct EntryType<SettingsEntry::GraphFullScreen>    { typedef bool type; };
    template <> struct EntryType<SettingsEntry::KeyLeft>            { typedef lm::Key type; };
    template <> struct EntryType<SettingsEntry::KeyRight>           { typedef lm::Key type; };
    template <> struct EntryType<SettingsEntry::KeyJump>            { typedef lm::Key type; };
    template <> struct EntryType<SettingsEntry::KeyCrouch>          { typedef lm::Key type; };
    template <> struct EntryType<SettingsEntry::KeyAttack>          { typedef lm::Key type; };
}

using DeserializerMap = std::map<std::string, SettingsEntry>;
using SerializerArray = std::array<std::string, static_cast<short>(SettingsEntry::Count)>;
using SettingsArray = std::array<std::string, static_cast<short>(SettingsEntry::Count)>;

std::ostream&    
operator<<(std::ostream& lhs, const lm::Vector2i& rhs);

std::istream&    
operator>>(const lm::Vector2i& lhs, std::istream& rhs);


class Settings : public lm::Singleton<Settings>
{

public:

    Settings();

    Settings(const Settings&) = delete;
    Settings&    operator=(const Settings&) = delete;


    template<SettingsEntry E>
    void
    set(typename EntryType<E>::type val)
    {
        _unsynced = true;
        setWithType<typename EntryType<E>::type>(E, val);
    }


    template<SettingsEntry E>
    void
    get(typename EntryType<E>::type& outval) const
    {
        tryConvertToType<typename EntryType<E>::type>(_valA[static_cast<short>(E)], outval);
    }


    bool                        bad() const            { return _bad; }
    const MappedKeys&           keyMapping() const     { return _keyMapping; }
    void                        store();
    void                        reload();

    ~Settings();


private:

    struct ExplicitBool
    {
        ExplicitBool() : b(false) {}
        ExplicitBool(bool state) : b(state) {}
        bool b;
    };
    friend std::ostream& operator<<(std::ostream& out, const ExplicitBool& v);
    friend std::istream& operator>>(std::istream& in, ExplicitBool& out);

    template<typename T>
    void
    setWithType(SettingsEntry e, const T& val)
    {
        std::stringstream ss;

        ss << val;
        _valA[static_cast<short>(e)] = ss.str();
    }


    template<typename T>
    static bool
    tryConvertToType(const std::string& sdata, T& out);

    void                          setDefaults();
    void                          load();
    void                          storeConfiguration();

    static bool                   validate(SettingsEntry e, std::string s);

    const DeserializerMap&        _deserializerM;
    const SerializerArray&        _serializerA;
    SettingsArray&                _valA;
    bool                          _bad;
    bool                          _unsynced;

    MappedKeys                    _keyMapping;

    using SettingToActionArray = std::array<MappedActions, static_cast<short>(SettingsEntry::Count)>;
    static const SettingToActionArray    _settingToActionA;

};


std::istream&
operator>>(std::istream& in, Settings::ExplicitBool& out);

std::istream&   
operator>>(std::istream& in, lm::Vector2i& out);

// Settings::tryConvertToType<T> definition needs istream overload declarations.

template<typename T>
inline bool
Settings::tryConvertToType(const std::string& sdata, T& out)
{
    std::stringstream entryss(sdata);

    entryss >> out;
    return !entryss.fail();
}

template<>
inline bool
Settings::tryConvertToType<bool>(const std::string& sdata, bool& out)
{
    std::stringstream entryss(sdata);
    ExplicitBool eb = true;

    entryss >> eb;
    out = eb.b;
    return !entryss.fail();
}

template<>
inline bool
Settings::tryConvertToType<lm::Key>(const std::string& sdata, lm::Key& out)
{
    std::stringstream entryss(sdata);
    int code;

    entryss >> code;
    out = static_cast<lm::Key>(code);
    return !entryss.fail();
}


// get / set helper specializations.

template<>
inline void
Settings::setWithType<lm::Key>(SettingsEntry e, const lm::Key& val)
{
    std::stringstream ss;

    ss << static_cast<int>(val);
    _valA[static_cast<short>(e)] = ss.str();
    _keyMapping.actionKey(_settingToActionA[static_cast<short>(e)]) = val;
}

template<>
inline void
Settings::setWithType<bool>(SettingsEntry e, const bool& val)
{
    std::stringstream ss;

    ss << ExplicitBool(val);
    _valA[static_cast<short>(e)] = ss.str();
}





#endif
