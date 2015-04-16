#include <cmath>
#include "Physics.hpp"
#include "Level.hpp"
#include "Screen.hpp"

void
Phys::updateEntity(IEntity &p, const Map& map)
{
    p.setOldStance();
    p.setOldDir();
    
    updateSpeed(p);
    updateStance(p);
    p.position.x += p.speed.x * 0.15f;
    checkCollisionX(p, map);
    applyGravity(p);
    p.position.y += p.speed.y * 0.17f;
    checkCollisionY(p, map);
}

void
Phys::updateSpeed(IEntity& p)
{
    if (p.grounded)
    {
        if (p.key(KeyId::Space) && !p.key(KeyId::Down))
            p.speed.y = 1.2f;
        if (p.key(KeyId::Right) && !p.key(KeyId::Left))
            p.speed.x = 0.7f;
        if (p.key(KeyId::Left) && !p.key(KeyId::Right))
            p.speed.x = -0.7f;
        if (p.key(KeyId::Down))
            p.speed.x = 0.f;
    }
    else
    {
        if (p.key(KeyId::Right) && !p.key(KeyId::Left))
            p.speed.x = 0.5f;
        if (p.key(KeyId::Left) && !p.key(KeyId::Right))
            p.speed.x = -0.5f;
    }
    if (p.speed.x != 0.f && !p.key(KeyId::Right) && !p.key(KeyId::Left))
        p.speed.x = 0.f;
}
void
Phys::updateStance(IEntity& p)
{
    if (p.speed.x < 0)
        p.setDirection(false);
    else if (p.speed.x > 0)
        p.setDirection(true);

    if (p.grounded)
    {
        if (p.key(KeyId::Down))
        {
            p.speed.x = 0.f;
            p.setStance(Stance::Crouch);
        }
        else if (p.speed.x != 0.f)
            p.setStance(Stance::Run);
        else
            p.setStance(Stance::Stand);
    }
    else
    {
        if (p.speed.y > 0.f)
            p.setStance(Stance::Jump);
        else
            p.setStance(Stance::Fall);
    }

    p.setAnimation(true);
    p.setTransition(false);
    int begin = gEntityData[p.dataId()].animations[static_cast<int>(p.stance())].begin;
    int length = gEntityData[p.dataId()].animations[static_cast<int>(p.stance())].length;
    int frames = gEntityData[p.dataId()].animations[static_cast<int>(p.stance())].frames;

    if (p.oldStance() != p.stance())
        p.setAnimation(begin, length, frames);
}


void
Phys::applyGravity(IEntity& p)
{
    p.grounded = false;
    p.speed = {p.speed.x, fmaxf((p.speed.y - 0.015f), -1.5f)};
}


void
Phys::checkCollisionX(IEntity& p, const Map& map)
{
    const lm::Rect2f& bounding = p.boundingBox();
    const float x = p.position.x + bounding.x;
    const float y = p.position.y + bounding.y;
    const float rangeX = std::ceil(x + bounding.w);
    const float rangeY = std::ceil(y + bounding.h);
    const bool faceRight = (p.speed.x >= 0.0f);

    float dx = 0.0f;

    for (int j = y; j < rangeY; ++j)
    {
        for (int i = x; i < rangeX; ++i)
        {
            const TileBoundingBox& bb = map.at(i, j).boundingBoxes();

            for (int b = 0; b < bb.count; ++b)
            {
                const float bx = i + bb.boxes[b].x;
                const float by = j + bb.boxes[b].y;
                const float bw = bb.boxes[b].w;
                const float bh = bb.boxes[b].h;
                float diff;

                if (bx + bw < x || bx > x + bounding.w || by + bh < y || by > y + bounding.h)
                    continue;
                if (faceRight)
                {
                    diff = x + bounding.w - bx;
                    if (diff > dx)
                        dx = diff;
                }
                else
                {
                    diff = x - (bx + bw);
                    if (diff < dx)
                        dx = diff;
                }
            }
        }
    }
    if (dx != 0.0f)
    {
        p.position.x -= dx;
        p.speed.x = 0.0f;
    }
}

void
Phys::checkCollisionY(IEntity& p, const Map& map)
{
    const lm::Rect2f& bounding = p.boundingBox();
    const float x = p.position.x + bounding.x;
    const float y = p.position.y + bounding.y;
    const float rangeX = std::ceil(x + bounding.w);
    const float rangeY = std::ceil(y + bounding.h);
    const bool faceUp = (p.speed.y > 0);

    float dy = 0.0f;

    for (int j = y; j < rangeY; ++j)
    {
        for (int i = x; i < rangeX; ++i)
        {
            const TileBoundingBox& bb = map.at(i, j).boundingBoxes();

            for (int b = 0; b < bb.count; ++b)
            {
                const float bx = i + bb.boxes[b].x;
                const float by = j + bb.boxes[b].y;
                const float bw = bb.boxes[b].w;
                const float bh = bb.boxes[b].h;
                float diff;

                if (bx + bw < x || bx > x + bounding.w || by + bh < y || by > y + bounding.h)
                    continue;
                if (faceUp)
                {
                    diff = y + bounding.h - by;
                    if (diff > dy)
                        dy = diff;
                }
                else
                {
                    diff = y - (by + bh);
                    if (diff < dy)
                        dy = diff;
                }
            }
        }
    }
    if (dy != 0.0f)
    {
        p.position.y -= dy;
        p.speed.y = 0.0f;
        if (!faceUp)
            p.grounded = true;
    }
}























