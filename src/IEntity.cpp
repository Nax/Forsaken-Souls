#include "IEntity.hpp"

void
IEntity::render() const
{
	_sprite.draw(0, 0);
}

void
IEntity::update()
{
	_sprite.update();
}