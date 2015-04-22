#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <string>
#include <Lums/Lums.hpp>
#include "ImageProvider.hpp"
#include "Camera.hpp"
#include "Map.hpp"

enum class KeyId
{
    Up,
    Down,
    Left,
    Right,
    Space
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
    lm::Rect2f          boundingBox[6];
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

extern const EntityData gEntityData[];

class IEntity
{
public:

    enum Stance
    {
        Stand,
        Run,
        Crouch,
        Jump,
        Fall,
        Dead
    };

	IEntity(int dataId, float x, float y);

    int                 hp() const          { return _hp; }
    int                 mp() const          { return _mp; }
    int                 hpMax() const       { return gEntityData[_dataId].hp; }
    int                 dataId() const      { return _dataId; }
    int                 level() const       { return _level; }
    float               mult() const        { return _mult; }
    Stance              stance() const      { return _stance; }
    Stance              oldStance() const   { return _oldStance; }
    bool                oldDir() const      { return _oldDir; }
    bool                direction() const   { return _direction; }
    bool                transition() const  { return _transition; }
    bool                animation() const   { return _animation; }
    bool                finished()          { return _sprite.finished(); }
    bool                key(KeyId id) const { return _keys[static_cast<int>(id)]; }
    const lm::Rect2f&   boundingBox() const { return gEntityData[_dataId].boundingBox[_stance]; }
    bool                dead() const        { return _dead; }

    void            setHp(int hp)                   { _hp = hp; }
    void            setMp(int mp)                   { _mp = mp; }
    void            setLevel(int level)             { _level = level; }
    void            setMult(float mult)             { _mult = mult; }
    void            setStance(Stance stance)        { _stance = stance; }
    void            setOldStance()                  { _oldStance = _stance; }
    void            setDirection(bool direction)    { _direction = direction; _sprite.flip.x = direction; }
    void            setOldDir()                     { _oldDir = _direction; }
    void            setTransition(bool transition)  { _transition = transition; }
    void            setAnimation(bool animation)    { _animation = animation; }
    void            setAnimation(int start, int end, int frames, bool loop = true);
    void            setKey(KeyId id, bool b)    { _keys[static_cast<int>(id)] = b; }

    void            render(lm::SpriteBatch& sb, const Camera& camera) const;
    virtual void    update(const Map& map);

    void            die();

	lm::Vector2f	     position;
    lm::Vector2f         speed;
    bool                 grounded;

protected:
    int                     _dataId;
    mutable lm::Sprite      _sprite;
    int                     _hp;
    int                     _mp;
    int                     _level;
    float                   _mult;
    Stance                  _oldStance;
    Stance                  _stance;
    bool                    _direction;
    bool                    _oldDir;
    bool                    _transition;
    bool                    _animation;
    bool                    _dead;
    std::array<bool, 5>     _keys;
};

#endif
