#include "IEntity.hpp"
#include "Screen.hpp"
#include "Tile.hpp"
#include "Physics.hpp"
#include <vector>
#include <iostream>

extern bool debugMode;

IEntity::IEntity(int dataId, float x, float y)
: position(x, y)
, grounded(false)
, _dataId(dataId)
, _hp(hpMax())
, _state(-1)
, _dead(false)
, _invFrames(0)
, _hit(false)
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
	const lm::Vector2f bpp = { boundingBox().pos.x + position.x - off.x, boundingBox().pos.y + position.y - off.y };
	lm::Rect2f hb = hitBox();
	bool hit = hb.size.x != 0.0f;

	hb.pos.x -= off.x;
	hb.pos.y -= off.y;

	_sprite.pos.x = p.x * TILE_SIZE;
	_sprite.pos.y = SCREEN_HEIGHT - (position.y - off.y) * TILE_SIZE - _sprite.height();

	sb.draw(_sprite);

	if (debugMode)
	{
		lm::VertexArray<12> bb;
		glColor3ub(0, 255, 0);
		bb.push(bpp.x * TILE_SIZE, SCREEN_HEIGHT - bpp.y * TILE_SIZE);
		bb.push((bpp.x + boundingBox().size.x) * TILE_SIZE, SCREEN_HEIGHT - bpp.y * TILE_SIZE);
		bb.push((bpp.x + boundingBox().size.x) * TILE_SIZE, SCREEN_HEIGHT - (bpp.y + boundingBox().size.y) * TILE_SIZE);
		bb.push(bpp.x * TILE_SIZE, SCREEN_HEIGHT - (bpp.y + boundingBox().size.y) * TILE_SIZE);
		bb.draw(GL_LINE_LOOP);

		lm::VertexArray<4>	va;
		glColor3ub(255, 0, 0);
		va.push(_sprite.pos.x, _sprite.pos.y);
		va.push(_sprite.pos.x + _sprite.width(), _sprite.pos.y);
		va.push(_sprite.pos.x + _sprite.width(), _sprite.pos.y + _sprite.height());
		va.push(_sprite.pos.x, _sprite.pos.y + _sprite.height());
		va.draw(GL_LINE_LOOP);

		if (hit)
		{
			lm::VertexArray<4>	va2;
			glColor3ub(255, 255, 0);
			va2.push(hb.pos.x * TILE_SIZE, SCREEN_HEIGHT - hb.pos.y * TILE_SIZE);
			va2.push((hb.pos.x + hb.size.x) * TILE_SIZE, SCREEN_HEIGHT - hb.pos.y * TILE_SIZE);
			va2.push((hb.pos.x + hb.size.x) * TILE_SIZE, SCREEN_HEIGHT - (hb.pos.y + hb.size.y) * TILE_SIZE);
			va2.push(hb.pos.x * TILE_SIZE, SCREEN_HEIGHT - (hb.pos.y + hb.size.y) * TILE_SIZE);
			va2.draw(GL_LINE_LOOP);
		}

		glColor3ub(255, 255, 255);
	}
}

void
IEntity::update(const Map& map)
{
	if (_invFrames)
		_invFrames--;
	int a = 0;
	const bool jump = key(Key::Space);
	const bool attack = key(Key::A);
	if (key(Key::Left))
		a--;
	if (key(Key::Right))
		a++;

	if (dead())
		a = 0;
	if (_state != 6)
	{
		switch (a)
		{
			case -1:
				aim(Aim::Left);
				break;
			case 0:
				aim(Aim::None);
				break;
			case 1:
				aim(Aim::Right);
				break;
		}
	}
	if (dead())
		setState(5);
	else
	{
		if (_hit)
		{
			setState(7);
		}
		else if (_state == 7)
		{
			if (_sprite.finished())
				setState(0);
		}
		else if (_state == 6)
		{
			if (_sprite.finished())
				setState(0);
		}
		else if (!grounded)
		{
			if (speed.y > 0)
				setState(3);
			else
				setState(4);
		}
		else
		{
			if (jump)
				setState(3);
			else if (attack)
				setState(6);
			else if (a)
				setState(1);
			else
				setState(0);
		}
	}

	Phys::updateEntity(*this, map);
	auto& bb = boundingBox();

	if (position.y + bb.pos.y + bb.size.y < -10)
		_hp -= ceil(hpMax() / 50.0f);
	if (_hp <= 0)
		die();
	_sprite.update();
	_sprite.pos.x = position.x * TILE_SIZE;
	_sprite.pos.y = SCREEN_HEIGHT - (position.y + 1) * TILE_SIZE - _sprite.height();
	_hit = false;
}

lm::Rect2f
IEntity::hitBox() const
{
	lm::Rect2f bb = boundingBox();
	auto boxState = gEntityData[_dataId].hitBox[_state];
    auto hitbox = boxState.box;
    int begin = boxState.begin;
    int len = boxState.len;

	if (hitbox.size.x == 0.0f)
		return {};
    if (_sprite.frame() < begin || _sprite.frame() >= begin + len)
        return {};

	lm::Vector2f center = position + bb.pos + lm::Vector2f(bb.size.x / 2.0f, 0);
	if (_direction)
	{
		return {{center.x + hitbox.pos.x, center.y + hitbox.pos.y}, {hitbox.size.x, hitbox.size.y}};
	}
	else
	{
		return {{center.x - hitbox.pos.x - hitbox.size.x, center.y + hitbox.pos.y}, {hitbox.size.x, hitbox.size.y}};
	}
}

lm::Vector2f
IEntity::center() const
{
    lm::Vector2f c = position;
    lm::Rect2f bb = boundingBox();

    c += bb.pos;
    c += bb.size / 2.0f;
    return c;
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
IEntity::hurt(int damage)
{
	_hp -= damage;
	_invFrames = 60;
	_hit = true;
	if (_hp <= 0)
		die();
}

void
IEntity::heal(int heal)
{
    if (_dead)
        return;
    _hp += heal;
    if (_hp > hpMax())
        _hp = hpMax();
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
