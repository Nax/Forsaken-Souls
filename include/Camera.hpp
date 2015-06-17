#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Lums>

class Entity;
class Map;

class Camera
{
public:
	Camera();
	void					focus(Entity& entity, const Map& map);
	const lm::Vector2f&		offset() const;
	void					update(Entity& entity, const Map& map);
	~Camera();

private:
	lm::Vector2f	_offset;
	lm::Vector2f	_speed;
	bool			_movingX;
	bool			_movingY;

};

#endif