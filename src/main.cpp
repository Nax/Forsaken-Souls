#include <Lums/Lums.hpp>
#include "Game.hpp"
#include "Level.hpp"
#include "LevelManager.hpp"
#include "Map.hpp"

#include <cstdio>
#include <iostream>

namespace
{
	void			test_level_n_map(int levelnum, int mapnum)
	{
		LevelManager	&lman = LevelManager::instance();

		lman.setCurrentLevel(levelnum);

		const Level&	lvl = lman.currentLevel();
		const Map*	pmap;
		pmap = &lvl.mapAt(mapnum);

		fprintf(stderr, "datsz: %zu\nnmaps:%i\ncurmap:%i\ncurmapobj:%p\nlvlnum:%i\n"
				, lvl.dataSize()
				, lvl.nMaps()
				, lvl.currentMap()
				, &lvl.map()
				, lvl.levelNum()
			   );
		fprintf(stderr, "w:%i\nh:%i\ntile0:%x\n", pmap->width(), pmap->height(), *pmap->tiles());


		for (int i = 0; i < lvl.nMaps(); ++i)
		{
			const std::list<InnerLink>&	lnks = lvl.innerLinks(i);

			std::cerr << "lvl " << lvl.levelNum() << ", map: " << i << std::endl;

			for (const InnerLink& lk : lnks)
			{
				std::cerr
					<< "\t from map " << lk.start.map << " chunk " << lk.start.chunk
					<< " to map " << lk.end.map << " chunk " << lk.end.chunk
					<< std::endl;
			}
		}
	}

	void			test_inter_level_linkage(void)
	{
		LevelManager	&lman = LevelManager::instance();
		const Link		*links = lman.levelLinks();

		std::cerr << "Inter-level links : " << std::endl;
		for (int i = 0; i < lman.nlinks(); ++i)
		{
			const Link&	lk = links[i];

				std::cerr
					<< "\t from level/map/chunk " 
					<< lk.start.level << '/' << lk.start.map <<	'/' << lk.start.chunk
					<< std::endl
					<< " to level/map/chunk "
					<< lk.end.level << '/' << lk.end.map <<	'/' << lk.end.chunk
					<< std::endl
					;
		}
	}
}

int
main()
{
	lm::Core core(1024, 576, "Forsaken Souls");

	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 1024, 576, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Testing Level / Map  related stuff
	test_level_n_map(0,0);
	test_level_n_map(0,1);
	test_level_n_map(1,1);
	test_level_n_map(1,2);

	std::cerr << std::endl;
	test_inter_level_linkage();

	return 0;
}
