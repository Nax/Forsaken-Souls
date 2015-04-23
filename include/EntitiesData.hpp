#ifndef ENTITIES_DATA_HPP
#define ENTITIES_DATA_HPP

#define MAX_STATES 256

struct  EntityData
{
    const char*         name;
    ImageId             image;
    int                 hp;
    int                 mp;
    int                 damage;
    lm::Rect2f          boundingBox[MAX_STATES];
    struct
    {
        int             begin;
        int             length;
        int             speed;
        bool			repeat;
    }                   animations[MAX_STATES];
    lm::Rect2f			speed[MAX_STATES];
};

extern const EntityData gEntityData[];

#endif