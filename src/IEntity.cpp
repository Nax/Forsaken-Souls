#include "IEntity.hpp"

void
IEntity::render() const
{
	_sprite.draw(50, 0);
}

void
IEntity::update()
{
	_sprite.update();
}