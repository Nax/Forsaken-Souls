#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>
#include "IEntity.hpp"
#include "Map.hpp"


class Player : public IEntity
{
public:
    Player();
    int     closeWeaponId() const   { return _closeWeaponId; }
    int     farWeaponId() const     { return _farWeaponId; }
    double  xp() const              { return _xp; }

    void    setCloseWeaponId(int id)    { _closeWeaponId = id; }
    void    setFarWeaponId(int id)      { _farWeaponId = id; }
    void    setXp(int xp)               { _xp = xp; }
    void    update(const Map& map);
    ~Player();

private:
    int                 _closeWeaponId;
    int                 _farWeaponId;
    int                 _xp;
};

#endif
