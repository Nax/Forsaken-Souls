#include "Camera.hpp"
#include "Screen.hpp"
#include "Map.hpp"
#include "Components/Physics.hpp"
#include "Components/Collider.hpp"

#define CAMERA_MIN_SPEED  (0.01f)

Camera::Camera()
: _movingX(false)
, _movingY(false)
{

}

void
Camera::focus(lm::GameObject& go, const Map& map)
{
	_movingY = true;
	_movingX = true;
	_offset.x = go.position.x - SCREEN_TILES_W / 2.0f;
	_offset.y = go.position.y - SCREEN_TILES_H / 2.0f;
    _speed = {0, 0};
	update(go, map);
}

const lm::Vector2f&
Camera::offset() const
{
	return _offset;
}

static void
moveCamera(bool& moving, float screenPos, float screenTiles, int mapSize, float& speed, float entitySpeed, float& offset)
{
	if (!moving)
		return;
	if (screenPos >= (screenTiles * 2.4f) / 5.0f && screenPos <= (screenTiles * 2.6f) / 5.0f)
	{
		moving = false;
		return;
	}
	offset += speed * (1.f / 120.f);
	if ((speed > 0 && entitySpeed < 0) || (speed < 0 && entitySpeed > 0))
		entitySpeed = 0.f;
	speed = speed * 0.95f + entitySpeed * 0.05f;
	if (speed > 0.0f && speed < CAMERA_MIN_SPEED)
		speed = CAMERA_MIN_SPEED;
	else if (speed < 0.0f && speed > -CAMERA_MIN_SPEED)
		speed = -CAMERA_MIN_SPEED;
    if (speed == 0.0f)
        moving = false;
}

static void
checkCamera(bool& moving, float screenPos, float screenTiles, float& speed, float entitySpeed, float aperture)
{
	if (moving)
		return;
	if ((screenPos < screenTiles * 0.5f - aperture * 0.5f * screenTiles && entitySpeed < 0.0f)
		|| (screenPos > screenTiles * 0.5f + aperture * 0.5f * screenTiles && entitySpeed > 0.0f))
	{
		moving = true;
		speed = entitySpeed;
	}
}

static void
checkBounds(float& offset, bool& moving, float screenTiles, int mapSize)
{
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

void
Camera::update(lm::GameObject& go, const Map& map)
{
	lm::Vector2f screenPos = lm::Vector2f(go.position.x, go.position.y) - _offset;

    Component::Physics* physics = go.getComponent<Component::Physics>("physics");
	Component::Collider* collider = go.getComponent<Component::Collider>("collider");
	if (collider)
		screenPos += collider->boundingBox.pos + collider->boundingBox.size * 0.5f;

	lm::Vector2f speed = physics->speed;

	checkCamera(_movingX, screenPos.x, SCREEN_TILES_W, _speed.x, speed.x, 1.0f / 7.0f);
	checkCamera(_movingY, screenPos.y, SCREEN_TILES_H, _speed.y, speed.y, 1.0f / 7.0f);
	moveCamera(_movingX, screenPos.x, SCREEN_TILES_W, map.width(), _speed.x, speed.x, _offset.x);
	moveCamera(_movingY, screenPos.y, SCREEN_TILES_H, map.height(), _speed.y, speed.y, _offset.y);
	checkBounds(_offset.x, _movingX, SCREEN_TILES_W, map.width());
	checkBounds(_offset.y, _movingY, SCREEN_TILES_H, map.height());
}

Camera::~Camera()
{

}
