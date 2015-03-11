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
	_sprite.draw(_x * 32, _y * 32);
}

void
IEntity::update()
{
	_sprite.update();
}
