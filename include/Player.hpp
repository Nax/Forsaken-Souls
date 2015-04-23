#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <bitset>
#include "IEntity.hpp"
#include "Map.hpp"


class Player : public IEntity
{
public:
    Player();
    void    update(const Map& map);
    ~Player();
};

#endif
