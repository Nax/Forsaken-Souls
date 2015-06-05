#include <iostream>
#include "Map.hpp"
#include "ImageProvider.hpp"
#include "Screen.hpp"
#include "Entity.hpp"
#include "Assets.hpp"

Map::Map(std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&_width), sizeof(int32_t));
	file.read(reinterpret_cast<char*>(&_height), sizeof(int32_t));
	_tiles = new uint16_t[_width * _height * MAP_DEPTH];
	file.read(reinterpret_cast<char*>(_tiles), _width * _height * MAP_DEPTH * 2);

    uint32_t spawnCount;
    uint32_t lightCount;

    file.read(reinterpret_cast<char*>(&spawnCount), 4);
    for (uint32_t i = 0; i < spawnCount; ++i)
    {
        Spawn s;
        file.read(reinterpret_cast<char*>(&s.x), 4);
        file.read(reinterpret_cast<char*>(&s.y), 4);
        file.read(reinterpret_cast<char*>(&s.id), 4);
        _spawns.push_back(s);
    }

    file.read(reinterpret_cast<char*>(&lightCount), 4);
    for (uint32_t i = 0; i < lightCount; ++i)
    {
        float x;
        float y;

        file.read(reinterpret_cast<char*>(&x), 4);
        file.read(reinterpret_cast<char*>(&y), 4);
        x += 0.5;
        y -= 0.7;
        _lights.push_back(x);
        _lights.push_back(y);
    }
}

Map::Map(Map&& rhs)
: _width(rhs._width)
, _height(rhs._height)
, _tiles(rhs._tiles)
{
	rhs._tiles = nullptr;
}

void
Map::setLinks(const std::vector<int32_t>& linkBuf, const int& mapNum)
{
	if (linkBuf.size() == 0)
		return;
	if (linkBuf.size() % 4 != 0)
	{
		std::cerr << "Invalid linkBuf size % 4 : " << linkBuf.size() % 4 << std::endl;
		return;
	}
	_links.clear();
	for (int i = 0; i < linkBuf.size(); i += 4)
	{
		if (linkBuf[i] == mapNum)
		{
			_links.push_back({{	
				linkBuf[i],
				linkBuf[i + 1],
				linkBuf[i + 2],
				linkBuf[i + 3]
			}});
		}
	}
}

uint32_t		
Map::width() const
{
	return _width;
}

uint32_t			
Map::height() const
{
	return _height;
}

const std::vector<Map::t_array4i>&
Map::links() const
{
	return _links;
}

uint16_t
Map::indexAt(int x, int y, int z) const
{
    if (x < 0 || x >= _width || y < 0 || y >= _height)
        return 0;
    return _tiles[x + y * _width + z * _width * _height];
}

const Tile&
Map::at(int x, int y, int z) const
{
	return Tile::fromId(indexAt(x, y, z));
}

void
Map::drawBack(lm::StaticSpriteBatch& batch) const
{
	draw(batch, 4);
	draw(batch, 3);
	draw(batch, 2);
}

void
Map::drawFront(lm::StaticSpriteBatch& batch) const
{
	draw(batch, 1);
	draw(batch, 0);
}

void
Map::spawn(std::vector<Entity*>& entities) const
{
    for (auto s : _spawns)
        entities.push_back(new Entity(s.id, s.x, s.y));
}

void
Map::enlight(lm::ShaderProgram& sp, Camera& camera) const
{
    int loc = glGetUniformLocation(sp.program(), "lightCount");
    glUniform1i(loc, _lights.size() / 2);
    loc = glGetUniformLocation(sp.program(), "lights");
    glUniform2fv(loc, _lights.size() / 2, _lights.data());
    loc = glGetUniformLocation(sp.program(), "off");
    glUniform2f(loc, camera.offset().x, camera.offset().y);
}

Map::~Map()
{
	delete [] _tiles;
}

/* PRIVATE */

void
Map::draw(lm::StaticSpriteBatch& sb, int z) const
{
    auto& tileset = lm::TextureProvider::instance().get(Assets::Texture::Tileset);

    for (int j = 0; j < _height; ++j)
    {
    	for (int i = 0; i < _width; ++i)
    	{
    		const uint16_t tileId = _tiles[i + j * _width + z * _width * _height];

    		if (tileId != 0)
    			sb.draw(tileset, tileId - 1, {i * TILE_SIZE, (_height - j) * TILE_SIZE}, {0.5f, 0.5f});
    	}
    }
}