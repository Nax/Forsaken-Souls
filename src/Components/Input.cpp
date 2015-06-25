#include "Components/Input.hpp"

LUMS_REGISTER_COMPONENT(Component::Input, "input");

using namespace Component;

Input::Input()
: left()
, right()
, jump()
, crouch()
, meleeAttack()
, rangeAttack()
{

}

Input::~Input()
{

}
