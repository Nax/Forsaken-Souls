
#ifndef LEVELMANAGER_HPP
# define LEVELMANAGER_HPP

# include <cstdint>
# include "Level.hpp"
# include "Link.hpp"

class LevelManager
{
	public:

		static LevelManager&	instance();

		Level&					currentLevel() const;
		int						currentLevelNum() const;
		void					setCurrentLevel(int levelNum);
		int						nlinks() const;
		const Link*				levelLinks() const;

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

		void					bufferizeLinks();
};

#endif // !LEVELMANAGER_HPP
