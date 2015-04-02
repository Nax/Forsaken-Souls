#include "IEntity.hpp"
#include <iostream>

void
IEntity::setAnimation(int start, int end, int frames, bool loop)
{
	_sprite.setAnimation(start, end, frames, loop);
}

void
IEntity::render() const
{
	_sprite.draw(_x * 32, _y * 32 - _sprite.height());
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 255, 0);
	glVertex3i(_x * 32, _y * 32, 0);
	glVertex3i((_x + gEntityData[_dataId].boundingBox[static_cast<int>(_stence)][0]) * 32, _y * 32, 0);
	glVertex3i((_x + gEntityData[_dataId].boundingBox[static_cast<int>(_stence)][0])* 32, (_y - gEntityData[_dataId].boundingBox[static_cast<int>(_stence)][1]) * 32, 0);
	glVertex3i(_x * 32, (_y - gEntityData[_dataId].boundingBox[static_cast<int>(_stence)][1]) * 32, 0);
	glEnd();
	glColor3ub(255, 255, 255);
}

void
IEntity::update()
{
	_sprite.update();
}
