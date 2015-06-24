#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <map>
#include <string>
#include <sstream>
#include <Lums>

using SettingsMap = std::map<Settings::Entry, std::string>;

class Settings
{
public:
	enum struct Entry : short
	{
		GraphResolution = 0,
		GraphFullScreen,
		Count
	};

	template <Entry E>
	struct EntryType
	{
		static_assert(E < Count, "Invalid Settings::Entry template value.");
		typedef void type;
	};
	template <> struct EntryType<GraphResolution> { typedef lm::Vector2i type; };
	template <> struct EntryType<GraphFullScreen> { typedef bool type; };

	Settings() = default;

	Settings(const Settings&) = delete;
	Settings&	operator=(const Settings&) = delete;
 
	template<Entry E>
	void
	set(EntryType<E>::type val)
	{
		std::stringstream ss;

		if (std::is_same<EntryType<E>::type, bool>)
			ss << ExplicitBool(val);
		else
			ss << val;
		_smap[E] = ss.str();
	}

	template<Entry E>
	void get(EntryType<E>::type& outval) const
	{
		std::stringstream entryss(_smap[E]);

		if (std::is_same<EntryType<E>::type, bool>)
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
		ExplicitBool() {}
		ExplicitBool(bool state) : b(state) {}
		bool b;
	};
	friend std::ostream& operator<<(std::ostream& out, const ExplicitBool& v);
	friend std::istream& operator>>(std::istream& in, ExplicitBool& out);

	SettingsMap&				_smap;
	bool						_bad;
};

// TODO?:  define in Lums
std::ostream&	
operator<<(std::ostream& lhs, const lm::Vector2i& rhs);

std::istream&	
operator>>(const lm::Vector2i& lhs, std::istream& rhs);

#endif