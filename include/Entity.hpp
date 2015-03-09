#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "IEntity.hpp"

class   Entity : public IEntity
{
public:
    Entity(int dataId, double x, double y, int level, double mult = 1);
    ~Entity();

private:
    // todo: AI   _ai
};

#endif