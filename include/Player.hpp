#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <bitset>
#include "IEntity.hpp"
#include "Map.hpp"


class Player : public IEntity
{
public:
    enum Key
    {
        Left,
        Down,
        Right,
        Space,
        A
    };

    Player();
    void    update(const Map& map);
    
    void
    setKey(Key key, bool value)
    {
        _keys[key] = value;
    }
    
    bool
    key(Key key) const
    {
        return _keys[key];
    }

    ~Player();

private:
    std::bitset<5>          _keys;
};

#endif
