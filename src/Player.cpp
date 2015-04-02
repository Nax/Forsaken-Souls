#include "Player.hpp"
#include "Physics.hpp"
#include "Level.hpp"

Player::Player()
: _closeWeaponId(0)
, _farWeaponId(0)
, _xp(0)
{
    _x = 2;
    _y = 2;
    _dataId = 0;
    _sprite.setImage(ImageProvider::get().image(gEntityData[0].image));
    _sprite.setScale(2);
    _grounded = false;
    _transition = false;
    _animation = true;
    _sprite.setAnimation(38, 1, 10);
    _oldStence = Stence::Fall;
    _stence = Stence::Fall;
    _oldDir= true;
    _direction = true;
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