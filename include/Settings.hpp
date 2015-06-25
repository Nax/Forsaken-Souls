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

	template <> struct EntryType<SettingsEntry::GraphResolution> { typedef lm::Vector2i type; };

	template <> struct EntryType<SettingsEntry::GraphFullScreen> { typedef bool type; };
}

using DeserializerMap = std::map<std::string, SettingsEntry>;
using SerializerArray = std::array<std::string, static_cast<short>(SettingsEntry::Count)>;
using SettingsArray = std::array<std::string, static_cast<short>(SettingsEntry::Count)>;

class Settings
{

public:

	Settings();

	Settings(const Settings&) = delete;
	Settings&	operator=(const Settings&) = delete;


	template<SettingsEntry E>
	void
	set(typename EntryType<E>::type val)
	{
		std::stringstream ss;

		if (std::is_same<typename EntryType<E>::type, bool>::value)
			ss << ExplicitBool(val);
		else
			ss << val;
		_valA[static_cast<short>(E)] = ss.str();
	}

	template<SettingsEntry E>
	void get(typename EntryType<E>::type& outval) const
	{
		std::stringstream entryss(_valA[static_cast<short>(E)]);

		if (std::is_same<typename EntryType<E>::type, bool>::value)
		{
			ExplicitBool eb = true;

			entryss >> eb;
			outval = eb.b;
		}
		else
			entryss >> outval;
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

	const DeserializerMap&		_deserializerM;
	const SerializerArray&		_serializerA;
	SettingsArray&				_valA;
	bool						_bad;
};



// TODO?:  define in Lums
std::ostream&	
operator<<(std::ostream& lhs, const lm::Vector2i& rhs);

std::istream&	
operator>>(const lm::Vector2i& lhs, std::istream& rhs);

#endif