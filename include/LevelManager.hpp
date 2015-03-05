
#ifndef LEVELMANAGER_HPP
# define LEVELMANAGER_HPP

# include <cstdint>

class Level;
struct Link;

class LevelManager
{
	public:

		static LevelManager&	instance(void);

		Level*					currentLevel(void) const;
		void					setCurrentLevel(int levelNum);

		~LevelManager();
		
	private:

		static LevelManager		*_instance;
		Level					*_currentLevel;
		uint8_t					*_linksData;
		size_t					_dataSize;

		LevelManager();
		LevelManager(const LevelManager&) = delete;
		LevelManager&			operator=(const LevelManager&) = delete;

		void					bufferizeLinks(void);
};

#endif // !LEVELMANAGER_HPP
