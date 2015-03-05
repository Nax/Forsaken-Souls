#include "Player.hpp"
#include "Physics.hpp"

Player::Player()
: _closeWeaponId(0)
, _farWeaponId(0)
, _xp(0)
{
    _dataId = 0;
    _sprite.setImage(ImageProvider::get().image(gEntityData[0].image));
    _sprite.setScale(2);
    _sprite.setAnimation(32, 5, 10);
    _grounded = true;
    _transition = false;
    _animation = true;
    _oldStence = Stence::Stand;
    _stence = Stence::Stand;
    _oldDir= true;
    _direction = true;
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