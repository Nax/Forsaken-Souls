#include "Camera.hpp"
#include "Screen.hpp"
#include "IEntity.hpp"

#define CAMERA_MIN_SPEED  (0.25f)

Camera::Camera()
: _zoom(1.0f)
, _movingX(false)
, _movingY(false)
{

}

const lm::Vector2f&
Camera::offset() const
{
	return _offset;
}

void
Camera::update(IEntity& entity)
{
	const lm::Vector2f screenPos = entity.position - _offset;

	if (!_movingX
		&& ((screenPos.x < SCREEN_TILES_W / 3.0f && entity.speed.x < 0)
		|| (screenPos.x > (SCREEN_TILES_W * 2.0f) / 3.0f && entity.speed.x > 0)))
	{
		_movingX = true;
		_speed.x = entity.speed.x;
	}
	if (!_movingY
		&& ((screenPos.y < SCREEN_TILES_H / 3.0f && entity.speed.y < 0)
		|| (screenPos.y > (SCREEN_TILES_H * 2.0f) / 3.0f && entity.speed.y > 0)))
	{
		_movingY = true;
		_speed.y = entity.speed.y;
	}

	if (_movingX)
	{
		if (screenPos.x >= (SCREEN_TILES_W * 2.4f) / 5.0f && screenPos.x <= (SCREEN_TILES_W * 2.6f) / 5.0f)
			_movingX = false;
		else
		{
			_offset.x += _speed.x * 0.15f;
			_speed.x = _speed.x * 0.95f + entity.speed.x * 0.05f;
			if (_speed.x > 0.0f && _speed.x < CAMERA_MIN_SPEED)
				_speed.x = CAMERA_MIN_SPEED;
			else if (_speed.x < 0.0f && _speed.x > -CAMERA_MIN_SPEED)
				_speed.x = -CAMERA_MIN_SPEED;
			if (_offset.x < 0.0f)
			{
				_offset.x = 0.0f;
				_movingX = false;
			}
		}
	}
	if (_movingY)
	{
		if (screenPos.y >= (SCREEN_TILES_H * 2.0f) / 5.0f && screenPos.y <= (SCREEN_TILES_H * 3.0f) / 5.0f)
			_movingY = false;
		else
		{
			_offset.y += _speed.y * 0.15f;
			_speed.y = _speed.y * 0.95f + entity.speed.y * 0.05f;
			if (_speed.y > 0.0f && _speed.y < CAMERA_MIN_SPEED)
				_speed.y = CAMERA_MIN_SPEED;
			else if (_speed.y < 0.0f && _speed.y > -CAMERA_MIN_SPEED)
				_speed.y = -CAMERA_MIN_SPEED;
			if (_offset.y < 0.0f)
			{
				_offset.y = 0.0f;
				_movingY = false;
			}
		}
	}
}

Camera::~Camera()
{

}
