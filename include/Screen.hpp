#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "Tile.hpp"

#define SCREEN_WIDTH	1920
#define SCREEN_HEIGHT	1080

#define SCREEN_TILES_W	(SCREEN_WIDTH  / float(TILE_SIZE))
#define SCREEN_TILES_H	(SCREEN_HEIGHT / float(TILE_SIZE))

#endif