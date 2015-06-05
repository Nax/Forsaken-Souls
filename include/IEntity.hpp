#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <string>
#include <Lums>
#include "ImageProvider.hpp"
#include "Camera.hpp"
#include "Map.hpp"
#include "EntitiesData.hpp"

class IEntity
{
public:
    enum Aim { Left, Right, None };

    enum class Key
    {
        Left,
        Down,
        Right,
        Space,
        A
    };

	IEntity(int dataId, float x, float y);

    int                 id() const                  { return _dataId; }
    int                 hp() const                  { return _hp; }
    int                 mp() const                  { return _mp; }
    int                 hpMax() const               { return gEntityData[_dataId].hp; }
    int                 dataId() const              { return _dataId; }
    bool                direction() const           { return _direction; }
    bool                finished() const            { return _sprite.finished(); }
    const lm::Rect2f&   boundingBox() const         { return gEntityData[_dataId].boundingBox[_state]; }
    lm::Rect2f          hitBox() const;
    lm::Vector2f        center() const;
    bool                dead() const                { return _dead; }
    void                die();
    int                 damage() const              { return gEntityData[_dataId].damage; }
    bool                invincible() const          { return _invFrames > 0; }

    void                setState(int stance);
    void                setDirection(bool direction){ _direction = direction; _sprite.flip.x = direction; }

    void                render(lm::SpriteBatch& sb, const Camera& camera) const;
    virtual void        update(const Map& map);
    void                aim(Aim aim);
    void                hurt(int damage);
    void                heal(int heal);

    void
    setKey(Key key, bool value)
    {
        _keys[int(key)] = value;
    }
    
    bool
    key(Key key) const
    {
        return _keys[int(key)];
    }

    virtual             ~IEntity();

	lm::Vector2f	     position;
    lm::Vector2f         speed;
    bool                 grounded;

protected:
    int                     _dataId;
    mutable lm::Sprite      _sprite;
    int                     _hp;
    int                     _mp;
    int                     _state;
    bool                    _direction;
    Aim                     _aim;
    bool                    _dead;
    int                     _invFrames;
    bool                    _hit;
    std::bitset<5>          _keys;
};

#endif
