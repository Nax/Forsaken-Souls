#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>
#include "IEntity.hpp"

enum class KeyId
{
    Up,
    Down,
    Left,
    Right,
    Space
};

class Player : public IEntity
{
public:
    Player();
    int     closeWeaponId() const   { return _closeWeaponId; }
    int     farWeaponId() const     { return _farWeaponId; }
    double  xp() const              { return _xp; }
    bool    key(KeyId id) const     { return _keys[static_cast<int>(id)]; }

    void    setCloseWeaponId(int id)    { _closeWeaponId = id; }
    void    setFarWeaponId(int id)      { _farWeaponId = id; }
    void    setXp(int xp)               { _xp = xp; }
    void    setKey(KeyId id, bool b)    { _keys[static_cast<int>(id)] = b; }
    void    update();
    ~Player();

private:
    int                 _closeWeaponId;
    int                 _farWeaponId;
    int                 _xp;
    std::array<bool, 5> _keys;
};

#endif
