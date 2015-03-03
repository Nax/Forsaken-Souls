#include "Player.hpp"

Player::Player()
: _closeWeaponId(0)
, _farWeaponId(0)
, _xp(0)
{
	_dataId = 0;
	_sprite.setImage(ImageProvider::get().image(gEntityData[0].image));
	_sprite.setScale(2);
	_sprite.setAnimation(0, 1, 7);
}

void
Player::update()
{

}

Player::~Player()
{

}