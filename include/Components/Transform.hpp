#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <Lums>
#include "Component.hpp"

class TransformComponent : public Component
{
    LUMS_COMPONENT

public:
    TransformComponent();
    lm::Vector2f*   pos();
    lm::Vector2f*   scale();
    lm::Angle*      rot();
    ~TransformComponent();

private:
    lm::Vector2f    _pos;
    lm::Vector2f    _scale;
    lm::Angle       _rot;    
};

#endif