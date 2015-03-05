#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <string>
#include <Lums/Lums.hpp>
#include "ImageProvider.hpp"

enum class Stence
{
    Stand,
    Run,
    Crouch,
    Jump,
    Secret
};

enum class HitState
{
    None,
    Attack,
    Hurt
};


struct  EntityData
{
    const char*         name;
    ImageId             image;
    int                 hp;
    int                 mp;
    double              speed;
    double              width;  
    double              height;
    int                 xp;
    int                 damage;
    int                 armor;
    int                 boundingBox[5][2];
    struct
    {
        int             begin;
        int             length;
    }                   transitions[5][5];
    struct
    {
        int             begin;
        int             length;
    }                   animations[5];
};

class   IEntity
{
public:
    int             id() const          { return _id; }
    double          x() const           { return _x; }
    double          y() const           { return _y; }
    lm::Vector2d&   speed()             { return _speed; }
    int             hp() const          { return _hp; }
    int             mp() const          { return _mp; }
    int             dataId() const      { return _dataId; }
    int             level() const       { return _level; }
    double          mult() const        { return _mult; }
    Stence          stence() const      { return _stence; }
    Stence          oldStence() const   { return _oldStence; }
    HitState        hitState() const    { return _hitState; }
    bool            oldDir() const      { return _oldDir; }
    bool            direction() const   { return _direction; }
    bool            grounded() const    { return _grounded; }
    bool            transition() const  { return _transition; }
    bool            animation() const   { return _animation; }
    bool            finished()          { _transition = !_sprite.finished(); return _transition; }

    void        setX(double x)                  { _x = x; }
    void        setY(double y)                  { _y = y; }
    void        setSpeed(double vx, double vy)  { _speed.set(vx, vy); }
    void        setHp(int hp)                   { _hp = hp; }
    void        setMp(int mp)                   { _mp = mp; }
    void        setLevel(int level)             { _level = level; }
    void        setMult(double mult)            { _mult = mult; }
    void        setStence(Stence stence)        { _stence = stence; }
    void        setOldStence()                  { _oldStence = _stence; }
    void        setHitState(HitState hitState)  { _hitState = hitState; }
    void        setDirection(bool direction)    { _direction = direction; }
    void        setOldDir()                     { _oldDir = _direction; }
    void        setGrounded(bool grounded)      { _grounded = grounded; }
    void        setTransition(bool transition)  { _transition = transition; }
    void        setAnimation(int start, int end, int frames, bool once = true);

    void        render() const;
    void        update();

protected:
    int             _id;
    double          _x;
    double          _y;
    lm::Vector2d    _force;
    lm::Vector2d    _speed;
    lm::Sprite      _sprite;
    int             _hp;
    int             _mp;
    int             _dataId;
    int             _level;
    double          _mult;
    Stence          _oldStence;
    Stence          _stence;
    HitState        _hitState;
    bool            _direction;
    bool            _oldDir;
    bool            _transition;
    bool            _animation;
    bool            _grounded;
};

extern const EntityData gEntityData[];

#endif