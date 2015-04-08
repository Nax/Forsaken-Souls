#include "IEntity.hpp"
#include <iostream>

IEntity::IEntity()
: _mult(1.0f)
{

}

void
IEntity::setAnimation(int start, int end, int frames, bool loop)
{
	_sprite.setAnimation(start, end, frames, loop);
}

void
IEntity::render(lm::SpriteBatch& sb) const
{
	sb.draw(_sprite);
}

void
IEntity::update()
{
	_sprite.update();
}
