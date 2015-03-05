#include "IEntity.hpp"

void
IEntity::setAnimation(int start, int end, int frames, bool once)
{
	_sprite.setAnimation(start, end, frames, once);
    _transition = once;
    _animation = !once;
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
