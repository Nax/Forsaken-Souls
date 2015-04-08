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

    // correct player position/speed according to collisions
    checkCollisionY(p, map);
    checkCollisionX(p, map);
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
    p.speed = {p.speed.x, fmaxf((p.speed.y - 0.02f), -2.0f)};
    p.speed = {0.4f, p.speed.y};
}

void
Phys::checkCollisionY(Player& p, const Map& map)
{
    float w = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][0];
    float h = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][1];

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
                    // Collision
                    std::cout << "DOWN: " << by + bh << std::endl;
                    p.position.y = by + bh;
                    p.speed = {p.speed.x, 0.f};
                    p.grounded = true;
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
                    // Collision
                    std::cout << "UP: " << by - h << std::endl;
                    p.position.y = by - h;
                    p.speed = {p.speed.x, 0.f};
                }
            }
        }
    }
}

void
Phys::checkCollisionX(Player& p, const Map& map)
{
    float w = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][0];
    float h = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][1];

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
                    // Collision
                    std::cout << "LEFT: " << bx + bw << std::endl;
                    p.position.x = bx + bw;
                    p.speed = {0.f, p.speed.y};
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
                    // Collision
                    std::cout << "RIGHT: " << p.position.x + w << "     " << i << std::endl;
                    p.position.x = bx - w;
                    p.speed = {0.f, p.speed.y};
                }
            }
        }
    }
}
