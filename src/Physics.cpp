#include <cmath>
#include "Physics.hpp"
#include "Level.hpp"
#include "Screen.hpp"

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























