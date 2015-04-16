#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Lums/Lums.hpp>

class IEntity;
class Map;

class Camera
{
public:
	Camera();
	const lm::Vector2f&		offset() const;
	void					update(IEntity& entity, const Map& map);
	~Camera();

private:
	lm::Vector2f	_offset;
	lm::Vector2f	_speed;
	bool			_movingX;
	bool			_movingY;

};

#endif