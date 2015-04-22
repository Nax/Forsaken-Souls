#include "Player.hpp"
#include "Physics.hpp"
#include "Level.hpp"
#include "Screen.hpp"
#include "Tile.hpp"


Player::Player()
: IEntity(0)
, _closeWeaponId(0)
, _farWeaponId(0)
, _xp(0)
{
	position = {5, 5};
    _oldStance = Stance::Stand;
    _stance = Stance::Stand;
    _sprite.setImage(ImageProvider::get().image(gEntityData[0].image));
	_sprite.pos = {position.x * TILE_SIZE, SCREEN_HEIGHT - ((position.y + 1) * TILE_SIZE) - _sprite.height()};
    _sprite.setScale(0.5f);
    grounded = false;
    _transition = false;
    _animation = true;
    _sprite.setAnimation(38, 1, 10);
    _oldDir = true;
    setDirection(true);
    std::fill(_keys.begin(), _keys.end(), false);
}

void
Player::update(const Map& map)
{
    Phys::updateEntity(*this, map);
	IEntity::update(map);
}

Player::~Player()
{

}
