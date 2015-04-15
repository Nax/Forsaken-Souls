#include "Player.hpp"
#include "Physics.hpp"
#include "Level.hpp"
#include "Screen.hpp"


Player::Player()
: IEntity()
, _closeWeaponId(0)
, _farWeaponId(0)
, _xp(0)
{
	position = {2.f, 2.f};
    _dataId = 0;
    _oldStance = Stance::Stand;
    _stance = Stance::Stand;
    _sprite.setImage(ImageProvider::get().image(gEntityData[0].image));
    _sprite.scale = {2.f, 2.f};
	_sprite.pos = {position.x * 32, SCREEN_HEIGHT - ((position.y + 1) * 32) - _sprite.height()};
    grounded = false;
    _transition = false;
    _animation = true;
    _sprite.setAnimation(38, 1, 10);
    _oldDir= true;
    setDirection(true);
    std::fill(_keys.begin(), _keys.end(), false);
}

void
Player::update(const Map& map)
{
    Phys::updatePlayer(*this, map);
	IEntity::update();
}

Player::~Player()
{

}
