#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "IEntity.hpp"

class Entity : public IEntity
{
public:
	Entity(int dataId, float x, float y);
	AI::function	ai() const { return gEntityData[_dataId].ai; }
    ~Entity();
};

#endif
