#include "Entity.hpp"

Entity::Entity()
: IEntity()
{
	
}

Entity::Entity(int dataId, float x, float y, int level, float mult)
: IEntity()
{
    _dataId = dataId;
	position.set(x, y);
    _level = level;
    _mult = mult;
}

Entity::~Entity()
{

}
