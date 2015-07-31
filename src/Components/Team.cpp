#include "Components/Team.hpp"

LUMS_REGISTER_COMPONENT(Component::Team, "team");

LUMS_BIND_SETTER("team", "team", &Component::Team::setTeam);

using namespace Component;

void
Team::setTeam(const lm::BValue& value)
{
    team = lm::sym(value.asString());
}