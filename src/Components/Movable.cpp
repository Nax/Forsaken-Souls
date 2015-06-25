#include "Components/Movable.hpp"

LUMS_REGISTER_COMPONENT(Components::Movable, "movable");

using namespace Component;

Movable::Movable()
: _speed()
{

}

Movable::~Movable()
{
    
}