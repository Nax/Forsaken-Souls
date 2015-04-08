#include "Player.hpp"
#include "Physics.hpp"
#include "Level.hpp"


Player::Player()
: IEntity()
, _closeWeaponId(0)
, _farWeaponId(0)
, _xp(0)
{
	position = {10, 10};
    _dataId = 0;
    _sprite.setImage(ImageProvider::get().image(gEntityData[0].image));
    _sprite.scale = {2, 2};
    grounded = false;
    _transition = false;
    _animation = true;
    _sprite.setAnimation(38, 1, 10);
    _oldStence = Stence::Fall;
    _stence = Stence::Fall;
    _oldDir= true;
    setDirection(true);
    std::fill(_keys.begin(), _keys.end(), false);
}

void
Player::update(const Map& map)
{
    Phys::updatePlayer(*this, map);
    _sprite.update();
}

Player::~Player()
{

}
