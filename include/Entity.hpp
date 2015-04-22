#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "IEntity.hpp"

class Entity : public IEntity
{
public:
	Entity(int dataId, float x, float y);
    ~Entity();

private:
    // todo: AI   _ai
};

#endif
