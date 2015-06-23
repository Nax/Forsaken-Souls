#ifndef SETTINGS_MANAGER_HPP
#define SETTINGS_MANAGER_HPP

#include <map>
#include <string>
#include <stringstream>
#include <Lums>

using SettingsMap = std::map<SettingsManager::Entry, std::vector<std::string> >;

class SettingsManager
{
public:
	enum struct Entry : short
	{
		GraphResolution = 0,
		GraphFullScreen,
		Count
	};

	SettingsManager() = default;

	SettingsManager(const SettingsManager&) = delete;
	SettingsManager&	operator=(const SettingsManager&) = delete;

	bool							sync() const;

	template<Entry E, typename First, typename... Others>
	void set(First first, Others... others);
	
	
	// Too many specializations eventually! 
	template<GraphResolution, int, int>
	void set(int x, int y)
	{
		std::stringstream	ss;
		std::string			fst;

		ss << x;
		fst = ss.str();
		ss.str("");
		ss << y;
		_smap[GraphResolution] = {
			fst
			, ss.str()
		};
	}

	template<DataType First, DataType... Others>
	bool
	get(Entry which, DataType& firstOut, DataType& ...othersOut)
	{

	}

	~SettingsManager();

private:
	// enum struct DataType : short
	// {
	// 	Boolean = 0,
	// 	String,
	// 	Integer,
	// 	Float,
	// 	Count
	// };

	// static const std::map<Entry, std::vector<DataType>>
	// _typeMapping;

	SettingsMap&				_smap;
};

#endif