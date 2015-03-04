#include <Lums/Lums.hpp>
#include "Game.hpp"
#include "Level.hpp"
#include "Map.hpp"

#include <cstdio>
int
main()
{
    lm::Core core(1024, 576, "Forsaken Souls");

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 1024, 576, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Level		l0(0);
	const Map&	m00 = l0.mapAt(0);

	fprintf(stderr, "datsz: %zu\nnmaps:%i\ncurmap:%i\ncurmapobj:%p\nlvlnum:%i\n"
			, l0.dataSize()
			, l0.nMaps()
			, l0.currentMap()
			, &l0.map()
			, l0.levelNum()
			);
	fprintf(stderr, "w:%i\nh:%i\ntile0:%x\n", m00.width(), m00.height(), *m00.tiles());

    return 0;
}
