#include "Player.hpp"
#include "Level.hpp"
#include "Screen.hpp"
#include "Tile.hpp"


Player::Player()
: IEntity(0, 5, 5)
, _closeWeaponId(0)
, _farWeaponId(0)
, _xp(0)
{
    std::fill(_keys.begin(), _keys.end(), false);
}

void
Player::update(const Map& map)
{
	IEntity::update(map);
}

Player::~Player()
{

}
