#include "Entity.hpp"

Entity::Entity(int dataId, double x, double y, int level, double mult)
{
    _dataId = dataId;
    _x = x;
    _y = y;
    _level = level;
    _mult = mult;
}

Entity::~Entity()
{

}
