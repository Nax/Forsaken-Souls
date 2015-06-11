#ifndef ENTITIES_DATA_HPP
#define ENTITIES_DATA_HPP

#define MAX_STATES 256

#include "AI.hpp"

struct  EntityData
{
    const char*         name;
    int                 image;
    int                 hp;
    int                 mp;
    int                 damage;
    lm::Rect2f          boundingBox[MAX_STATES];
    struct
    {
        lm::Rect2f		box;
        int             begin;
        int             len;
    }                   hitBox[MAX_STATES];
    struct
    {
        int             begin;
        int             length;
        int             speed;
        bool			repeat;
    }                   animations[MAX_STATES];
    lm::Vector2f		speed[MAX_STATES];
    AI::function		ai;
};

extern const EntityData gEntityData[];

#endif