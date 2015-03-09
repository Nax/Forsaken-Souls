
#ifndef LEVELMANAGER_HPP
# define LEVELMANAGER_HPP

# include <cstdint>
# include "Link.hpp"

class Level;

class LevelManager
{
	public:

		static LevelManager&	instance(void);

		const Level&			currentLevel(void) const;
		int						currentLevelNum(void) const;
		void					setCurrentLevel(int levelNum);
		int						nlinks(void) const;
		const Link*				levelLinks(void) const;

		~LevelManager();
		
	private:

		static LevelManager		*_instance;
		Level					*_currentLevel;
		int						_currentLevelNum;
		int						_nlinks;
		Link					*_levelLinks;

		LevelManager();
		LevelManager(const LevelManager&) = delete;
		LevelManager&			operator=(const LevelManager&) = delete;

		void					bufferizeLinks(void);
};

#endif // !LEVELMANAGER_HPP
