#include <cmath>
#include "Physics.hpp"
#include "Level.hpp"

void
Phys::updatePlayerStence(Player &p)
{
    switch (p.oldStence())
    {
        case Stence::Stand:
        {
            if (p.key(KeyId::Space))
                p.setStence(Stence::Jump);
            else if (p.key(KeyId::Left) || p.key(KeyId::Right))
                p.setStence(Stence::Run);
            else if (p.key(KeyId::Down))
                p.setStence(Stence::Crouch);
            else
                p.setStence(Stence::Stand);
            break;
        }
        case Stence::Run:
        {
            if (p.key(KeyId::Space))
                p.setStence(Stence::Jump);
            else if ((p.oldDir() == false && p.key(KeyId::Left) == false) || (p.oldDir() == true && p.key(KeyId::Right) == false))
                p.setStence(Stence::Stand);
            else if (p.key(KeyId::Down))
                p.setStence(Stence::Crouch);
            else
                p.setStence(Stence::Run);
            break;
        }
        case Stence::Crouch:
        {
            if (p.key(KeyId::Space))
                p.setStence(Stence::Jump);
            if (p.key(KeyId::Down) == false)
                p.setStence(Stence::Stand);
            else
                p.setStence(Stence::Crouch);
            break;
        }
        case Stence::Jump:
        {
            //
            p.setGrounded(false);
            //
            if (p.speed().y < 0.0)
                p.setStence(Stence::Fall);
            else
                p.setStence(Stence::Jump);
            break;
        }
        case Stence::Fall:
        {
            if (p.grounded())
                p.setStence(Stence::Stand);
            else
                p.setStence(Stence::Fall);
            break;
        }
        case Stence::Secret:
            break;
        default:
            break;
    }
    if (!p.grounded())
    {
        if (p.speed().y > 0)
            p.setStence(Stence::Jump);
        else
            p.setStence(Stence::Fall);
    }
}

void
Phys::setPlayerTransition(Player &p)
{
    p.setAnimation(false);
    p.setTransition(true);
    int begin = gEntityData[p.dataId()].transitions[static_cast<int>(p.oldStence())][static_cast<int>(p.stence())].begin;
    int length = gEntityData[p.dataId()].transitions[static_cast<int>(p.oldStence())][static_cast<int>(p.stence())].length;
    int frames = gEntityData[p.dataId()].transitions[static_cast<int>(p.oldStence())][static_cast<int>(p.stence())].frames;
    p.setAnimation(begin, length, frames, false);
}

void
Phys::setPlayerAnimation(Player &p)
{
    p.setAnimation(true);
    p.setTransition(false);
    int begin = gEntityData[p.dataId()].animations[static_cast<int>(p.stence())].begin;
    int length = gEntityData[p.dataId()].animations[static_cast<int>(p.stence())].length;
    int frames = gEntityData[p.dataId()].animations[static_cast<int>(p.stence())].frames;
    p.setAnimation(begin, length, frames);
}

void
Phys::updatePlayerSpeed(Player &p, bool moving)
{
    double      factor = (p.direction()) ? 1.0 : -1.0;
    Stence      stence = p.stence();

    // y speed
    if (p.grounded())
    {
        if (stence == Stence::Jump)
            p.setSpeed(p.speed().x, 1.0);
        else
            p.setSpeed(p.speed().x, 0.0);
    }
    else
        p.setSpeed(p.speed().x, fmax((p.speed().y - 0.02), -2.0));

    // x speed
    if (p.grounded())
    {
        if (stence == Stence::Stand || stence == Stence::Crouch)
            p.setSpeed(0.0, 0.0);
        else if (stence == Stence::Run)
            p.setSpeed(factor * 1.0, 0.0);
        else
            p.setSpeed(factor * 0.7, p.speed().y);
    }
    else
    {
        if (moving)
            p.setSpeed(factor * 0.7, p.speed().y);
        else
            p.setSpeed(0.0, p.speed().y);
    }
}

void
Phys::updatePlayerPosition(Player &p, const Map& map)
{   
    p.setX(p.x() + p.speed().x * 0.1);
    p.setY(p.y() + p.speed().y * 0.1);

    float w = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][0];
    float h = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][1];

    int x1 = ceil(p.x() + gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][0]);
    int y1 = ceil(p.y() + gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][1]);

    //Check y collision
    if (p.speed().y < 0.0)
    {
        for (int i = p.x(); i < x1; i++)
        {
            const TileBoundingBox& box = map.at(i, p.y()).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = i + box.boxes[j].x;
                float   by = floor(p.y()) + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.x() + w > bx && p.x() < bx + bw && p.y() + h > by && p.y() < by + bh)
                {
                    // Collision
                    p.setY(by + bh);
                    p.setSpeed(p.speed().x, 0);
                    p.setGrounded(true);
                }
            }
        }    
    }
}

void
Phys::updatePlayer(Player &p, const Map& map)
{
    bool    moving;
    bool    turning;

    p.setOldDir();
    p.setOldStence();

    // update direction
    moving = (p.key(KeyId::Left) && !p.key(KeyId::Right)) || (p.key(KeyId::Right) && !p.key(KeyId::Left));
    if (moving)
        p.key(KeyId::Left) ? p.setDirection(false) : p.setDirection(true);
    p.flipX(!p.direction());

    // update stence
    updatePlayerStence(p);
    if (p.oldStence() != p.stence())
        setPlayerTransition(p);
    if (p.finished() && !p.animation())
        setPlayerAnimation(p);

    updatePlayerSpeed(p, moving);
    updatePlayerPosition(p, map);

    // Final goal :
    //      Set new direction
    //      Set new stence
    //      Set new animation/transition if needed according to stence and direction
    //      Set new speed vector
    //      Set player position according to speed vector

    // All new parameters can be the same as before.
}
