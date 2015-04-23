#include "IEntity.hpp"
#include "Screen.hpp"
#include "Tile.hpp"
#include "Physics.hpp"
#include <vector>

extern bool debugMode;

IEntity::IEntity(int dataId, float x, float y)
: position(x, y)
, grounded(false)
, _dataId(dataId)
, _hp(hpMax())
, _state(-1)
, _dead(false)
{
	_sprite.setImage(ImageProvider::get().image(gEntityData[_dataId].image));
	_sprite.pos = {position.x * TILE_SIZE, SCREEN_HEIGHT - ((position.y + 1) * TILE_SIZE) - _sprite.height()};
    _sprite.setScale(0.5f);
    setState(0);
    aim(Aim::None);
    setDirection(true);
}

void
IEntity::render(lm::SpriteBatch& sb, const Camera& camera) const
{
	const lm::Vector2f& off = camera.offset();
	const lm::Vector2f p = position - off;
	const lm::Vector2f bpp = { boundingBox().x + position.x - off.x, boundingBox().y + position.y - off.y };

	_sprite.pos.x = p.x * TILE_SIZE;
	_sprite.pos.y = SCREEN_HEIGHT - (position.y - off.y) * TILE_SIZE - _sprite.height();

	sb.draw(_sprite);

	if (debugMode)
	{
		glDisable(GL_TEXTURE_2D);
		lm::VertexArray<4>	bb;
		glColor3ub(0, 255, 0);
		bb.push(bpp.x * TILE_SIZE, SCREEN_HEIGHT - bpp.y * TILE_SIZE);
		bb.push((bpp.x + boundingBox().w) * TILE_SIZE, SCREEN_HEIGHT - bpp.y * TILE_SIZE);
		bb.push((bpp.x + boundingBox().w) * TILE_SIZE, SCREEN_HEIGHT - (bpp.y + boundingBox().h) * TILE_SIZE);
		bb.push(bpp.x * TILE_SIZE, SCREEN_HEIGHT - (bpp.y + boundingBox().h) * TILE_SIZE);
		bb.draw(GL_LINE_LOOP);

		lm::VertexArray<4>	va;
		glColor3ub(255, 0, 0);
		va.push(_sprite.pos.x, _sprite.pos.y);
		va.push(_sprite.pos.x + _sprite.width(), _sprite.pos.y);
		va.push(_sprite.pos.x + _sprite.width(), _sprite.pos.y + _sprite.height());
		va.push(_sprite.pos.x, _sprite.pos.y + _sprite.height());
		va.draw(GL_LINE_LOOP);
		glColor3ub(255, 255, 255);
	}
}

void
IEntity::update(const Map& map)
{
	Phys::updateEntity(*this, map);
	auto& bb = boundingBox();

	if (position.y + bb.y + bb.h < -10)
		_hp -= ceil(hpMax() / 50.0f);
	if (_hp <= 0)
		die();
	_sprite.update();
	_sprite.pos.x = position.x * TILE_SIZE;
	_sprite.pos.y = SCREEN_HEIGHT - (position.y + 1) * TILE_SIZE - _sprite.height();
}

void
IEntity::aim(Aim aim)
{
	_aim = aim;
	if (aim == Aim::Left)
	{
		setDirection(false);
		speed.x = -gEntityData[_dataId].speed[_state].x;
	}
	else if (aim == Aim::Right)
	{
		setDirection(true);
		speed.x = gEntityData[_dataId].speed[_state].x;
	}
	else
		speed.x = 0;
}

void
IEntity::die()
{
	_hp = 0;
	_dead = true;
}

void
IEntity::setState(int state)
{
	if (_state == state)
		return;
	_state = state;
	auto& anim = gEntityData[_dataId].animations[state];
	_sprite.setAnimation(anim.begin, anim.length, anim.speed, anim.repeat);
	aim(_aim);
	speed.y = gEntityData[_dataId].speed[state].y;
}

IEntity::~IEntity()
{

}
