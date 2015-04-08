#include "Player.hpp"
#include "Physics.hpp"


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
    _sprite.setAnimation(0, 6, 13);
    grounded = true;
    _transition = false;
    _animation = true;
    _oldStence = Stence::Stand;
    _stence = Stence::Stand;
    _oldDir= true;
    setDirection(true);
    std::fill(_keys.begin(), _keys.end(), false);
}

void
Player::update()
{
    Phys::updatePlayer(*this);
    _sprite.update();
}

Player::~Player()
{

}
