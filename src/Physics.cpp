#include <cmath>
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
    p.setX(p.x() + p.speed().x * 0.1);
    p.setY(p.y() + p.speed().y * 0.1);
}

void
Phys::applyGravity(Player& p)
{
    p.setGrounded(false);
    p.setSpeed(p.speed().x, fmax((p.speed().y - 0.02), -2.0));
    p.setSpeed(0.4, p.speed().y);
}

void
Phys::checkCollisionY(Player& p, const Map& map)
{
    float w = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][0];
    float h = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][1];

    // check for downward collisions
    if (p.speed().y <= 0.0)
    {
        for (int i = p.x(); i < floor(p.x() + w); i++)
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
                    std::cout << "DOWN: " << by + bh << std::endl;
                    p.setY(by + bh);
                    p.setSpeed(p.speed().x, 0);
                    p.setGrounded(true);
                }
            }
        }
    }
    // check for upward collisions
    else
    {
        for (int i = p.x(); i < floor(p.x() + w); i++)
        {
            const TileBoundingBox& box = map.at(i, p.y() + h).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = i + box.boxes[j].x;
                float   by = floor(p.y() + h) + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.x() + w > bx && p.x() < bx + bw && p.y() + h > by && p.y() < by + bh)
                {
                    // Collision
                    std::cout << "UP: " << by - h << std::endl;
                    p.setY(by - h);
                    p.setSpeed(p.speed().x, 0);
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
    if (p.speed().x <= 0.0)
    {
        for (int i = p.y(); i < ceil(p.y() + h); i++)
        {
            const TileBoundingBox& box = map.at(p.x(), i).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = floor(p.x()) + box.boxes[j].x;
                float   by = i + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.y() + h > by && p.y() < by + bh && p.x() + w > bx && p.x() < bx + bw)
                {
                    // Collision
                    std::cout << "LEFT: " << bx + bw << std::endl;
                    p.setX(bx + bw);
                    p.setSpeed(0, p.speed().y);
                }
            }
        }
    }
    // check for right collisions
    else
    {
        for (int i = p.y(); i < ceil(p.y() + h); i++)
        {
            const TileBoundingBox& box = map.at(p.x() + w, i).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = floor(p.x() + w) + box.boxes[j].x;
                float   by = i + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.y() + h > by && p.y() < by + bh && p.x() + w > bx && p.x() < bx + bw)
                {
                    // Collision
                    std::cout << "RIGHT: " << p.x() + w << "     " << i << std::endl;
                    p.setX(bx - w);
                    p.setSpeed(0, p.speed().y);
                }
            }
        }
    }
}
