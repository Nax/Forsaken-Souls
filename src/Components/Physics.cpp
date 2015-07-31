#include "Components/Physics.hpp"

LUMS_REGISTER_COMPONENT(Component::Physics, "physics");

using namespace Component;

void
Physics::init(lm::GameObject& object)
{
    grounded = false;
}