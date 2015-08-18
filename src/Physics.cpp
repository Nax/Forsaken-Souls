#include <cmath>
#include <iostream>
#include "Physics.hpp"

bool
Physics::intersect(const Map& map, lm::Rect2f boundingBox)
{
    int x = boundingBox.pos.x;
    int y = boundingBox.pos.y;
    int w = std::ceil(boundingBox.pos.x + boundingBox.size.x);
    int h = std::ceil(boundingBox.pos.y + boundingBox.size.y);

    for (int j = y; j < h; ++j)
    {
        for (int i = x; i < w; ++i)
        {
            if (map.indexAt(i, j))
                return true;
        }
    }
    return false;
}

static void
solveCollisions(int axis, const Map& map, lm::Rect2f& bb, lm::Vector2f& speed, bool& grounded)
{
    if (axis == 1)
        grounded = false;
    redo:
    const lm::Vector2f range = { std::ceil(bb.pos.x + bb.size.x), std::ceil(bb.pos.y + bb.size.y) };
    const bool faceRight = (speed[axis] >= 0.0f);

    for (int j = bb.pos.y; j < range.y; ++j)
    {
        for (int i = bb.pos.x; i < range.x; ++i)
        {
            lm::Vector2i tileCoord = { i, j };
            if (!map.indexAt(i, j))
                continue;
            if (faceRight)
                bb.pos[axis] = tileCoord[axis] - bb.size[axis];
            else
                bb.pos[axis] = tileCoord[axis] + 1;
            speed[axis] = 0.f;
            if (axis == 1 && !faceRight)
                grounded = true;
            goto redo; // Is this still needed ?
        }
    }
}

void
Physics::computeNextFrame(const Map& map, lm::Rect2f& boundingBox, lm::Vector2f& speed, bool& grounded)
{
    speed.y -= Physics::gravity;
    boundingBox.pos.x += speed.x * (1.f / 120.f);
    solveCollisions(0, map, boundingBox, speed, grounded);
    boundingBox.pos.y += speed.y * (1.f / 120.f);
    solveCollisions(1, map, boundingBox, speed, grounded);
}

bool
Physics::computeFinalPosition(lm::Vector2f& output, int& frames, const Map& map, lm::Rect2f boundingBox, lm::Vector2f speed)
{
    static const int limit = 200;
    bool grounded = true;
    bool hadLeftGround = false;

    for (int i = 0; i < limit; ++i)
    {
        computeNextFrame(map, boundingBox, speed, grounded);
        if (!grounded && !hadLeftGround)
            hadLeftGround = true;
        else if (hadLeftGround && grounded)
        {
            output = boundingBox.pos;
            frames = i;
            return true;
        }
        if (grounded && speed.x == 0.f)
            return false;
        if (boundingBox.pos.y < 0)
            return false;
    }
    return false;
}
