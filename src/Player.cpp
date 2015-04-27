#include "Player.hpp"
#include "Level.hpp"
#include "Screen.hpp"
#include "Tile.hpp"


Player::Player()
: IEntity(0, 20, 20)
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
