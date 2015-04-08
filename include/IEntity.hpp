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
    Fall,
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
    float               speed;
    float               width;  
    float               height;
    int                 xp;
    int                 damage;
    int                 armor;
    float               boundingBox[6][2];
    struct
    {
        int             begin;
        int             length;
        int             frames;
    }                   transitions[6][6];
    struct
    {
        int             begin;
        int             length;
        int             frames;
    }                   animations[6];
};

class   IEntity
{
public:

	IEntity();

    int             hp() const          { return _hp; }
    int             mp() const          { return _mp; }
    int             dataId() const      { return _dataId; }
    int             level() const       { return _level; }
    float           mult() const        { return _mult; }
    Stence          stence() const      { return _stence; }
    Stence          oldStence() const   { return _oldStence; }
    HitState        hitState() const    { return _hitState; }
    bool            oldDir() const      { return _oldDir; }
    bool            direction() const   { return _direction; }
    bool            transition() const  { return _transition; }
    bool            animation() const   { return _animation; }
    bool            finished()          { return _sprite.finished(); }

    void        setHp(int hp)                   { _hp = hp; }
    void        setMp(int mp)                   { _mp = mp; }
    void        setLevel(int level)             { _level = level; }
    void        setMult(float mult)            { _mult = mult; }
    void        setStence(Stence stence)        { _stence = stence; }
    void        setOldStence()                  { _oldStence = _stence; }
    void        setHitState(HitState hitState)  { _hitState = hitState; }
    void        setDirection(bool direction)    { _direction = direction; _sprite.flip.x = direction; }
    void        setOldDir()                     { _oldDir = _direction; }
    void        setTransition(bool transition)  { _transition = transition; }
    void        setAnimation(bool animation)    { _animation = animation; }
    void        setAnimation(int start, int end, int frames, bool loop = true);

    void        render(lm::SpriteBatch& sb) const;
    void        update();

	lm::Vector2f	position;
    lm::Vector2f    speed;
    bool            grounded;

protected:
    lm::Sprite      _sprite;
    int             _hp;
    int             _mp;
    int             _dataId;
    int             _level;
    float           _mult;
    Stence          _oldStence;
    Stence          _stence;
    HitState        _hitState;
    bool            _direction;
    bool            _oldDir;
    bool            _transition;
    bool            _animation;
};

extern const EntityData gEntityData[];

#endif
