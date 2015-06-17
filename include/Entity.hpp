#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <Lums>
#include "Components/Component.hpp"

class Entity : public lm::GameObject<Entity, Component>
{
public:
	Entity();
    lm::Vector2f    center();
    ~Entity();
};

#endif
