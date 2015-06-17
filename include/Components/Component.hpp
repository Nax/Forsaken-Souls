#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <Lums>

class Entity;

class Component : public lm::Component
{
    LUMS_COMPONENT

public:
    virtual void    update(Entity& e); 
    virtual void    render(Entity& e, lm::SpriteBatch& sb);
    virtual void    handleEvent(Entity& e, const lm::Event& event);
};

#endif