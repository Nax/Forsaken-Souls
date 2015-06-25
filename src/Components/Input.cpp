#include "Components/Input.hpp"

LUMS_REGISTER_COMPONENT(Component::Input, "input");

using namespace Component;

Input::Input()
: _left()
, _right()
, _jump()
, _crouch()
, _meleeAttack()
, _rangeAttack()
{

}

Input::~Input()
{

}
