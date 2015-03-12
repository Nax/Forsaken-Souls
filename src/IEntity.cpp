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
	_sprite.draw(_x * 32, (_y - gEntityData[_dataId].boundingBox[static_cast<int>(_stence)][1]) * 32);
}

void
IEntity::update()
{
	_sprite.update();
}
