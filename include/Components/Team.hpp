#ifndef COMPONENT_TEAM_HPP
#define COMPONENT_TEAM_HPP

#include <Lums>

namespace Component
{
    class Team : public lm::Component
    {
        LUMS_COMPONENT
    public:
        void    setTeam(const lm::BValue& value);

        size_t  team;
    };
}

#endif