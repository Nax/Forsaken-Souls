#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <map>
#include <string>
#include <sstream>
#include <array>
#include <Lums>


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

// TODO?:  define in Lums
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
		getWithType<typename EntryType<E>::type>(E, outval, std::is_same<bool, typename EntryType<E>::type>());
	}


	bool						bad() const			{ return _bad; }
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

	template<lm::Key>
	void		setWithType(SettingsEntry e, const lm::Key& val);

	template<bool>
	void		setWithType(SettingsEntry e, bool val);

	template<typename T>
	void
	getWithType(SettingsEntry e, T& out, std::true_type)
	{
		std::stringstream entryss(_valA[static_cast<short>(e)]);
		ExplicitBool eb = true;

		entryss >> eb;
		out = eb.b;
	}

	template<typename T>
	void
	getWithType(SettingsEntry e, T& out, std::false_type)
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
};

template<>
inline void
Settings::setWithType<lm::Key>(SettingsEntry e, const lm::Key& val)
{
	std::stringstream ss;

	ss << static_cast<int>(val);
	_valA[static_cast<short>(e)] = ss.str();
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