#include "Entity.hpp"

Entity::Entity(int dataId)
: IEntity(dataId)
{
	
}

Entity::Entity(int dataId, float x, float y, int level, float mult)
: IEntity(dataId)
{
	position.set(x, y);
    _level = level;
    _mult = mult;
}

Entity::~Entity()
{

}
