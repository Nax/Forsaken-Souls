#include <cmath>
#include "Physics.hpp"
#include "Level.hpp"
#include "Screen.hpp"

#include <iostream>

void
Phys::updateEntity(IEntity &p, const Map& map)
{    
    p.position.x += p.speed.x * 0.15f;
    checkCollisionX(p, map);
    applyGravity(p);
    p.position.y += p.speed.y * 0.17f;
    checkCollisionY(p, map);
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
    redo:
    const lm::Rect2f& bounding = p.boundingBox();
    const float x = p.position.x + bounding.pos.x;
    const float y = p.position.y + bounding.pos.y;
    const float rangeX = std::ceil(x + bounding.size.x);
    const float rangeY = std::ceil(y + bounding.size.y);
    const bool faceRight = (p.speed.x >= 0.0f);

    for (int j = y; j < rangeY; ++j)
    {
        for (int i = x; i < rangeX; ++i)
        {
            const TileBoundingBox& bb = map.at(i, j).boundingBoxes();

            for (int b = 0; b < bb.count; ++b)
            {
                const float bx = i + bb.boxes[b].pos.x;
                const float by = j + bb.boxes[b].pos.y;
                const float bw = bb.boxes[b].size.x;
                const float bh = bb.boxes[b].size.y;
                float diff;

                if (bx + bw < x || bx > x + bounding.size.x || by + bh < y || by > y + bounding.size.y)
                    continue;
                if (faceRight)
                    diff = x + bounding.size.x - bx;
                else
                    diff = x - (bx + bw);
                p.position.x -= diff;
                p.speed.x = 0.0f;
                goto redo;
            }
        }
    }
}

void
Phys::checkCollisionY(IEntity& p, const Map& map)
{
    const lm::Rect2f& bounding = p.boundingBox();
    const float x = p.position.x + bounding.pos.x;
    const float y = p.position.y + bounding.pos.y;
    const float rangeX = std::ceil(x + bounding.size.x);
    const float rangeY = std::ceil(y + bounding.size.y);
    const bool faceUp = (p.speed.y > 0);

    float dy = 0.0f;

    for (int j = y; j < rangeY; ++j)
    {
        for (int i = x; i < rangeX; ++i)
        {
            const TileBoundingBox& bb = map.at(i, j).boundingBoxes();

            for (int b = 0; b < bb.count; ++b)
            {
                const float bx = i + bb.boxes[b].pos.x;
                const float by = j + bb.boxes[b].pos.y;
                const float bw = bb.boxes[b].size.x;
                const float bh = bb.boxes[b].size.y;
                float diff;

                if (bx + bw < x || bx > x + bounding.size.x || by + bh < y || by > y + bounding.size.y)
                    continue;
                if (faceUp)
                {
                    diff = y + bounding.size.y - by;
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


void
Phys::checkDamages(IEntity& attacker, IEntity& target)
{
    lm::Rect2f hitbox = attacker.hitBox();
    lm::Rect2f boundingBox = target.boundingBox();

    boundingBox.pos.x += target.position.x;
    boundingBox.pos.y += target.position.y;

    if (target.invincible())
        return;

    if (hitbox.pos.x + hitbox.size.x > boundingBox.pos.x
        && hitbox.pos.x < boundingBox.pos.x + boundingBox.size.x
        && hitbox.pos.y + hitbox.size.y > boundingBox.pos.y
        && hitbox.pos.y < boundingBox.pos.y + boundingBox.size.y)
    {
        target.hurt(attacker.damage());
    }
}




















