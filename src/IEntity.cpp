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
	_sprite.draw(_x, 481);
}

void
IEntity::update()
{
	_sprite.update();
}
