#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Lums>

class Map;

class Camera
{
public:
	Camera();
	void					focus(lm::GameObject& go, const Map& map);
	const lm::Vector2f&		offset() const;
	void					update(lm::GameObject& go, const Map& map);
	~Camera();

private:
	lm::Vector2f	_offset;
	lm::Vector2f	_speed;
	bool			_movingX;
	bool			_movingY;

};

#endif