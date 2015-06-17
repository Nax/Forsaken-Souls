#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "Entity.hpp"
#include "Components/Component.hpp"

class MovableComponent : public Component
{
    LUMS_COMPONENT

public:
    MovableComponent();
    void    update(Entity& e);

    lm::Vector2f*   speed();
    void            setSpeed(lm::Vector2f speed);
    ~MovableComponent();

private:
    lm::Vector2f    _speed;    
};

#endif