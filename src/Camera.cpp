#include "Camera.hpp"
#include "Screen.hpp"
#include "IEntity.hpp"
#include "Map.hpp"

#define CAMERA_MIN_SPEED  (0.20f)

Camera::Camera()
: _movingX(false)
, _movingY(false)
{

}

const lm::Vector2f&
Camera::offset() const
{
	return _offset;
}

static void
moveCamera(bool& moving, int screenPos, int screenTiles, int mapSize, float& speed, float entitySpeed, float& offset)
{
	if (!moving)
		return;
	if (screenPos >= (screenTiles * 2.4f) / 5.0f && screenPos <= (screenTiles * 2.6f) / 5.0f)
	{
		moving = false;
		return;
	}
	offset += speed * 0.15f;
	speed = speed * 0.95f + entitySpeed * 0.05f;
	if (speed > 0.0f && speed < CAMERA_MIN_SPEED)
		speed = CAMERA_MIN_SPEED;
	else if (speed < 0.0f && speed > -CAMERA_MIN_SPEED)
		speed = -CAMERA_MIN_SPEED;
	if (offset < 0.0f)
	{
		offset = 0.0f;
		moving = false;
	}
	else if (offset + screenTiles >= mapSize)
	{
		offset = mapSize - screenTiles;
		moving = false;
	}
}

static void
checkCamera(bool& moving, int screenPos, int screenTiles, float& speed, float entitySpeed)
{
	if (moving)
		return;
	if ((screenPos < screenTiles / 3.0f && entitySpeed < 0.0f)
		|| (screenPos > (screenTiles * 2.0f) / 3.0f && entitySpeed > 0.0f))
	{
		moving = true;
		speed = entitySpeed;
	}
}

void
Camera::update(IEntity& entity, const Map& map)
{
	const auto& bb = entity.boundingBox();
	const lm::Vector2f screenPos = entity.position - _offset + lm::Vector2f(bb.pos.x, bb.pos.y) + lm::Vector2f(bb.size.x / 2, bb.size.y / 2);

	checkCamera(_movingX, screenPos.x, SCREEN_TILES_W, _speed.x, entity.speed.x);
	checkCamera(_movingY, screenPos.y, SCREEN_TILES_H, _speed.y, entity.speed.y);
	moveCamera(_movingX, screenPos.x, SCREEN_TILES_W, map.width(), _speed.x, entity.speed.x, _offset.x);
	moveCamera(_movingY, screenPos.y, SCREEN_TILES_H, map.height(), _speed.y, entity.speed.y, _offset.y);
}

Camera::~Camera()
{

}
