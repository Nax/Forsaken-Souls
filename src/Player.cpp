#include "Player.hpp"
#include "Level.hpp"
#include "Screen.hpp"
#include "Tile.hpp"


Player::Player()
: IEntity(0, 5, 8)
{

}

void
Player::update(const Map& map)
{
	IEntity::update(map);
}

Player::~Player()
{

}
