#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <map>
#include <string>
#include <sstream>
#include <array>
#include <Lums>
#include "MappedKeys.hpp"

// As of 279e0653d196b
// Settings is a lm::Singleton (i.e.: lazily constructed)
// Upon construction, the Settings instances initializes
// itself from the existing config file (load defaults otherwise.)
// 
// Settings caches current settings and will not write to file
// unless a store() call is issued. Thus, calling get<E> / set<E>
// will not trigger disk IO by themselves.
//
// Settings manages internally an instance of the MappedKeys class.
// Any key-binding-related call to get<E> / set<E> will update the
// MappedKeys instance.
// Settings provides access to a const reference to the instance of
// MappedKeys for specific queries (such as reading actual key bindings).
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

	template <> struct EntryType<SettingsEntry::GraphResolution>	{ typedef lm::Vector2i type; };
	template <> struct EntryType<SettingsEntry::GraphFullScreen>	{ typedef bool type; };
	template <> struct EntryType<SettingsEntry::KeyLeft>			{ typedef lm::Key type; };
	template <> struct EntryType<SettingsEntry::KeyRight>			{ typedef lm::Key type; };
	template <> struct EntryType<SettingsEntry::KeyJump>			{ typedef lm::Key type; };
	template <> struct EntryType<SettingsEntry::KeyCrouch>			{ typedef lm::Key type; };
	template <> struct EntryType<SettingsEntry::KeyAttack>			{ typedef lm::Key type; };
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
	Settings&	operator=(const Settings&) = delete;


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
		getWithType<typename EntryType<E>::type>(E, outval);
	}


	bool						bad() const			{ return _bad; }
	const MappedKeys&			keyMapping() const	{ return _keyMapping; }
	void						store();
	void						reload();

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
	void
	getWithType(SettingsEntry e, T& out) const
	{
		std::stringstream entryss(_valA[static_cast<short>(e)]);

		entryss >> out;
	}

	void						setDefaults();
	void						load();
	void						storeConfiguration();

	const DeserializerMap&		_deserializerM;
	const SerializerArray&		_serializerA;
	SettingsArray&				_valA;
	bool						_bad;
	bool						_unsynced;

	MappedKeys					_keyMapping;

	using SettingToActionArray = std::array<MappedActions, static_cast<short>(SettingsEntry::Count)>;
	static const SettingToActionArray	_settingToActionA;

};

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

template<>
inline void
Settings::getWithType<bool>(SettingsEntry e, bool& out) const
{
	std::stringstream entryss(_valA[static_cast<short>(e)]);
	ExplicitBool eb = true;

	entryss >> eb;
	out = eb.b;
}

template<>
inline void
Settings::getWithType<lm::Key>(SettingsEntry e, lm::Key& out) const
{
	std::stringstream entryss(_valA[static_cast<short>(e)]);
	int	code;

	entryss >> code;
	out = static_cast<lm::Key>(code);
}


#endif