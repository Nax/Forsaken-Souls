#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Lums/Lums.hpp>

class IEntity;

class Camera
{
public:
	Camera();
	const lm::Vector2f&		offset() const;
	void					update(IEntity& entity);
	~Camera();

private:
	lm::Vector2f	_offset;
	lm::Vector2f	_speed;
	float			_zoom;
	bool			_movingX;
	bool			_movingY;

};

#endif