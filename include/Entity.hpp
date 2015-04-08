#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "IEntity.hpp"

class   Entity : public IEntity
{
public:
	Entity();
    Entity(int dataId, float x, float y, int level, float mult = 1);
    ~Entity();

private:
    // todo: AI   _ai
};

#endif
