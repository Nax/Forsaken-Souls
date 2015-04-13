#include <cmath>
#include <iostream>
#include "Physics.hpp"
#include "Level.hpp"

void
Phys::updatePlayer(Player &p, const Map& map)
{
    p.setOldStence();
    p.setOldDir();

    // update player position
    applyGravity(p);
    updatePosition(p);

    // set player position/speed according to collisions
    float dx = 0.0;
    float dy = 0.0;
    checkCollisionX(p, map, &dx);
    checkCollisionY(p, map, &dy);

    if (fabs(dy) < fabs(dx) && dy != 0.f)
    {
        p.position.y += dy;
        if (dy != 0.f)
            p.speed = {p.speed.x, 0.f};
        if (dy > 0.f)
            p.grounded = true;

        checkCollisionX(p, map, &dx);
        p.position.x += dx;
        if (dx != 0.f)
            p.speed = {0.f, p.speed.y};
    }
    else if (dx != 0.f)
    {
        p.position.x += dx;
        if (dx != 0.f)
            p.speed = {0.f, p.speed.y};

        checkCollisionY(p, map, &dy);
        p.position.y += dy;
        if (dy != 0.f)
            p.speed = {p.speed.x, 0.f};
        if (dy > 0.f)
            p.grounded = true;
    }
}

void
Phys::updatePosition(Player& p)
{
    p.position.x = p.position.x + p.speed.x * 0.1f;
    p.position.y = p.position.y + p.speed.y * 0.1f;
}

void
Phys::applyGravity(Player& p)
{
    p.grounded = false;
    p.speed = {p.speed.x, fmaxf((p.speed.y - 0.02f), -2.f)};
    p.speed = {1.0f, p.speed.y};
}

void
Phys::checkCollisionY(Player& p, const Map& map, float* dy)
{
    float w = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][0];
    float h = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][1];

    *dy = 0.f;

    // check for downward collisions
    if (p.speed.y <= 0.f)
    {
        for (int i = p.position.x; i < floor(p.position.x + w); i++)
        {
            const TileBoundingBox& box = map.at(i, p.position.y).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = i + box.boxes[j].x;
                float   by = floor(p.position.y) + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.position.x + w > bx && p.position.x < bx + bw && p.position.y + h > by && p.position.y < by + bh)
                {
                    if (fabs((by + bh) - p.position.y) > fabs(*dy))
                        *dy = (by + bh) - p.position.y;
                }
            }
        }
    }
    // check for upward collisions
    else
    {
        for (int i = p.position.x; i < floor(p.position.x + w); i++)
        {
            const TileBoundingBox& box = map.at(i, p.position.y + h).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = i + box.boxes[j].x;
                float   by = floor(p.position.y + h) + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.position.x + w > bx && p.position.x < bx + bw && p.position.y + h > by && p.position.y < by + bh)
                {
                    if (fabs((by - h) - p.position.y) > fabs(*dy))
                        *dy = (by - h) - p.position.y;
                }
            }
        }
    }
}

void
Phys::checkCollisionX(Player& p, const Map& map, float* dx)
{
    float w = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][0];
    float h = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][1];

    *dx = 0.f;

    // check for left collisions
    if (p.speed.x <= 0.f)
    {
        for (int i = p.position.y; i < ceil(p.position.y + h); i++)
        {
            const TileBoundingBox& box = map.at(p.position.x, i).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = floor(p.position.x) + box.boxes[j].x;
                float   by = i + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.position.y + h > by && p.position.y < by + bh && p.position.x + w > bx && p.position.x < bx + bw)
                {
                    if (fabs((bx + bw) - p.position.x) > fabs(*dx))
                        *dx = (bx + bw) - p.position.x;
                }
            }
        }
    }
    // check for right collisions
    else
    {
        for (int i = p.position.y; i < ceil(p.position.y + h); i++)
        {
            const TileBoundingBox& box = map.at(p.position.x + w, i).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = floor(p.position.x + w) + box.boxes[j].x;
                float   by = i + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.position.y + h > by && p.position.y < by + bh && p.position.x + w > bx && p.position.x < bx + bw)
                {
                    if (fabs((bx - w) - p.position.x) > fabs(*dx))
                        *dx = (bx - w) - p.position.x;
                }
            }
        }
    }
}
