#include <Lums/Lums.hpp>
#include "Game.hpp"
#include "Level.hpp"
#include "Map.hpp"

#include <cstdio>
#include <iostream>
int
main()
{
    lm::Core core(1024, 576, "Forsaken Souls");

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 1024, 576, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Level		lvl(0);
	const Map*	pmap;
	pmap = &lvl.mapAt(0);

	lvl = Level(1);
	pmap = &lvl.mapAt(1);

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

    return 0;
}
