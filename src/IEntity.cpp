#include "IEntity.hpp"

void
IEntity::setAnimation(int start, int end, int frames, bool once)
{
    // if (once)
        // _sprite.setAnimationOnce(start, end, frames);
    // else
        _sprite.setAnimation(start, end, frames);

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
